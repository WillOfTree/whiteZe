/**
 * @file tray_extension.h
 * @brief 定义 TTrayExtension 类，用于在 Godot 中管理 Windows 托盘图标和菜单。
 *
 * @author 叙白
 * @date 2025-07-12
 *
 * 该类提供创建和管理系统托盘图标、处理鼠标事件、管理上下文菜单的功能，适用于运行在 Windows 平台上的 Godot 应用。
 * 使用 Windows API 与系统托盘和菜单交互，并在各种用户交互时向 Godot 脚本发射信号。
 *
 * 主要功能：
 * - 单例模式，便于全局访问。
 * - 托盘图标的创建、初始化和提示文本管理。
 * - 鼠标事件处理（悬停、移动、离开、左右键点击、双击）。
 * - 上下文菜单的创建、显示和菜单项管理。
 * - 向 Godot 脚本发射托盘图标和菜单相关信号。
 *
 * 使用方法：
 * - 调用 gdscript_init_trayicon 初始化自定义图标和提示文本的托盘图标。
 * - 使用 add_menu_item 和 remove_menu_item 管理菜单项。
 * - 在 Godot 脚本中连接信号（"trayicon_left_clicked"、"trayicon_right_clicked"、"menu_item_selected"）。
 *
 * @note 本类仅适用于 Godot C++ 扩展 API 和 Windows 平台。
 */
#ifndef __TTrayExtension_CPP_H__
#define __TTrayExtension_CPP_H__

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <windows.h>
#include <string>
#include <unordered_map>


// namespace godot
// {
//     class String;
// }


class TTrayExtension : public godot::Object
{
    GDCLASS(TTrayExtension, godot::Object);

public:
    static TTrayExtension * get_singleton();
    
    void draw_menu_item(LPDRAWITEMSTRUCT lpDrawItem); // 绘制菜单项
protected:
    static void _bind_methods();

private:
    static TTrayExtension * singleton; // 单例模式-对象
    static HWND hWnd; // 菜单句柄
    static NOTIFYICONDATAW nid;
    static HMENU hMenu; // 子菜单项

    const wchar_t * m_unique_class = nullptr;  // 注册的类名，要求唯一
    const char * m_window_title_name = "Godot Tray"; // windows窗体标题
    std::wstring m_icon_path; // 托盘图标位置
    std::wstring m_tooltip; // 托盘图标悬停显示信息

    int m_tray_icon_size_x = 32; // 托盘图标大小
    int m_tray_icon_size_y = 32; // 托盘图标大小


    /**
     * 托盘图标的回调函数，包括移入，单击，左击操作
     * 
     * 移入移出方法
     * - WM_MOUSEHOVER - 当鼠标在窗口客户区悬停一段时间后触发
     * - WM_MOUSEMOVE - 当鼠标首次进入窗口客户区时也会触发（通常配合TrackMouseEvent使用）
     * - WM_MOUSELEAVE - 当鼠标离开窗口客户区时触发（需要先调用TrackMouseEvent注册跟踪）
     * 鼠标点击
     * - 左键按下：WM_LBUTTONDOWN
     * - 左键释放：WM_LBUTTONUP
     * - 左键双击：WM_LBUTTONDBLCLK
     * 鼠标右击
     * - 右键按下：WM_RBUTTONDOWN
     * - 右键释放：WM_RBUTTONUP
     * - 右键双击：WM_RBUTTONDBLCLK
     */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
    {
        LRESULT result = 0;
        bool handled = true; // 是否返回给windows处理标识，默认交给windows处理

        switch (msg)
        {
            case WM_USER + 1: // 托盘消息,移动到托盘图标上
            {
                TTrayExtension * p = TTrayExtension::get_singleton(); // 获取单例
                handled = false; // 不交给windows处理标识

                switch (lParam)
                {
                    case WM_LBUTTONDOWN: // 左击
                        p->emit_signal("trayicon_left_clicked");
                        break;

                    case WM_RBUTTONDOWN: // 右击
                        p->emit_signal("trayicon_right_clicked");
                        break;

                    default:
                        // UtilityFunctions::print("AAA");
                        break;
                }
                // godot::UtilityFunctions::print("1");
                break;
            }

            case WM_COMMAND: // 菜单事件， 菜单事件通过 msg == WM_COMMAND，不是 lParam == WM_COMMAND。
            {
                // 处理菜单项点击
                TTrayExtension * p = TTrayExtension::get_singleton();
                handled = false; // 不交给windows处理标识

                if (HIWORD(wParam) == 0) 
                {
                    p->emit_signal("menu_item_selected", LOWORD(wParam));
                }
                break;
            }

            // 添加菜单测量消息处理
            case WM_MEASUREITEM:
            {
                
                LPMEASUREITEMSTRUCT lpMeasureItem = (LPMEASUREITEMSTRUCT)lParam;
                if (lpMeasureItem->CtlType == ODT_MENU) 
                {
                    handled = false; // 不交给windows处理标识
                    result = TRUE;

                    // 设置菜单项高度（图标高度+边距）
                    lpMeasureItem->itemHeight = 22;  // 24像素高度
                    lpMeasureItem->itemWidth = 100;   // 最小宽度
                }
                // godot::UtilityFunctions::print("3");
                break;
            }
            
            // 创建了带有 OWNERDRAW 标志的控件或菜单时,需要使用
            case WM_DRAWITEM:
            {
                LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
                if (lpDrawItem->CtlType == ODT_MENU) 
                {
                    handled = false; // 不交给windows处理标识
                    result = TRUE;

                    TTrayExtension * p = TTrayExtension::get_singleton(); // 获取单例
                    p->draw_menu_item(lpDrawItem);
                }
                // godot::UtilityFunctions::print("4");
                break;
            }

            default: 
                break;
        }


        if (handled)
        {
            // godot::UtilityFunctions::print("55");
            // 其他消息，我不处理，交给windows处理
            return DefWindowProcW(hWnd, msg, wParam, lParam); 
        }
        else
        {
            // godot::UtilityFunctions::print("66");
            return result;
        }
        
    }

    HWND godot_hwnd = nullptr; // godot的界面的指针

    // 通过pid查询hwnd对象的结构体
    struct WindowSearchData 
    {
        DWORD pid;
        HWND result;
    };

    enum class MenuItemType {WITH_ICON, NO_ICON};

    // 存储菜单项额外信息的结构体
    struct MenuItemInfo 
    {
        int id;
        std::wstring text;
        TTrayExtension::MenuItemType type; // 菜单项类型
        HICON hIcon;
    };
    std::unordered_map<int, MenuItemInfo> m_menu_items; // 存储菜单项额外信息的映射

    // 添加菜单项的类型枚举,可选的是添加（添加只能在最后），插入（需要提供位置）
    // enum class AddMenuItemType { INSERT, ADD};

    /**
     * 初始化图标方法
     */
    void init_register_class(); // 注册类
    void init_create_window(); // 创建窗口
    void init_tray_icon(); // 初始化图标

    void conversion_wstring(const godot::String a, std::wstring & aim_string); // 转换字符
    bool verify_menuitem_has_id(int id); // 验证menu item变量有没有指定id
    HICON load_icon(const godot::String & icon_path); // 加载图标

    void create_default_menu(); // 创建菜单
    
    HWND FindTopWindowByProcessId(DWORD pid); // 通过ID查找HWND

    // 供GDScript调用方法
    void gd_init_trayicon(const godot::String & icon_path, const godot::String & tooltip);
    void gd_show_menu_item(); // 显示菜单
    void gd_add_menu_item(const godot::String & text, int id); // 添加菜单项
    void gd_add_menu_item_with_icon(const godot::String & text, int id, const godot::String & icon_path);
    void gd_insert_menu_item(const godot::String& text, int id, int position); // 插入菜单项
    void gd_insert_menu_item_with_icon(const godot::String& text, int id, int position, const godot::String& icon_path); // 插入菜单项
    void gd_set_tray_icon_size(int x, int y); // 设置托盘图标大小

    void gd_remove_menu_item(int id); // 删除菜单项
    void gd_clear_menu(); // 清空菜单项
    // void gd_insert_menu_item(); // 插入菜单项

    void gd_hide_godot_window(); // 隐藏godot窗体
    void gd_show_godot_window(); // 显示godot窗体
};
#endif