/**
 * @file tray_extension.cpp
 * @brief 实现 Windows 系统托盘图标功能，集成 Godot。
 *
 * 主要功能方法及说明：
 * - _bind_methods：绑定 Godot 方法和信号，供 GDScript 调用。
 * - gd_init_trayicon：供GDScript调用的初始化托盘图标，注册窗口类、创建窗口、加载图标、添加到托盘。
 * - init_register_class：注册唯一窗口类（Unicode），设置窗口过程函数。
 * - init_create_window：创建隐藏窗口，用于接收托盘和菜单消息。
 * - init_tray_icon：加载图标文件，设置提示文本，添加到系统托盘。
 * - conversion_wstring：Godot String 转换为 std::wstring（UTF-16）。
 * - create_default_menu：创建默认菜单项（Open、Exit、分隔线）。
 * - get_singleton：获取单例对象，确保只创建一个实例。
 * 
 * - gd_show_menu_item：弹出菜单，获取鼠标位置，设置窗口前台，解决菜单滞留。
 * - gd_add_menu_item：添加菜单项或分隔线，支持 Unicode，错误日志输出。
 * - gd_remove_menu_item：根据菜单项 ID 删除菜单项。
 * - gd_clear_menu：清空菜单项。
 * - gd_show_menu_item：弹出菜单，获取鼠标位置，设置窗口前台，解决菜单滞留。
 * - gd_show_godot_window：显示 Godot 窗口。
 * - gd_hide_godot_window：隐藏 Godot 窗口。
 *
 *
 *
 * 主要说明：
 * - 所有 WinAPI 调用均使用 Unicode（W）版本，避免编码问题。
 * - 错误处理通过弹窗或 Godot 日志输出，便于调试。
 * - tooltip 最长 127 字符，icon_path 必须为绝对路径。
 * - 仅支持 Windows 平台。
 *
 *
 * @author 叙白
 * @date 2025
 */
#include "objects/tray_extension.h"

using namespace godot;


// 静态成员初始化
TTrayExtension * TTrayExtension::singleton = nullptr;
HWND TTrayExtension::hWnd = nullptr;
HMENU TTrayExtension::hMenu = nullptr;
NOTIFYICONDATAW TTrayExtension::nid = { sizeof(NOTIFYICONDATAW) };


void TTrayExtension::_bind_methods() 
{
    // 单例
    ClassDB::bind_static_method("TTrayExtension", D_METHOD("get_singleton"), &TTrayExtension::get_singleton);

    // 供GDScript调用方法
    ClassDB::bind_method(D_METHOD("init_tray_icon", "icon_path", "tooltip"), &TTrayExtension::gd_init_trayicon);
    ClassDB::bind_method(D_METHOD("set_icon_size", "x", "y"), &TTrayExtension::gd_set_tray_icon_size);

    ClassDB::bind_method(D_METHOD("add_menu_item", "text", "id"), &TTrayExtension::gd_add_menu_item);
    ClassDB::bind_method(D_METHOD("add_icon_menu_item", "text", "id", "icon_path"), &TTrayExtension::gd_add_menu_item_with_icon);
    ClassDB::bind_method(D_METHOD("insert_menu_item", "text", "id", "position"), &TTrayExtension::gd_insert_menu_item);
    ClassDB::bind_method(D_METHOD("insert_icon_menu_item", "text", "id", "position", "icon_path"), &TTrayExtension::gd_insert_menu_item_with_icon);

    ClassDB::bind_method(D_METHOD("remove_menu_item", "id"), &TTrayExtension::gd_remove_menu_item);
    ClassDB::bind_method(D_METHOD("clear_menu"), &TTrayExtension::gd_clear_menu);

    ClassDB::bind_method(D_METHOD("show_menu_item"), &TTrayExtension::gd_show_menu_item);
    ClassDB::bind_method(D_METHOD("show_window"), &TTrayExtension::gd_show_godot_window);
    ClassDB::bind_method(D_METHOD("hide_window"), &TTrayExtension::gd_hide_godot_window);

    
    // 信号
    ADD_SIGNAL(MethodInfo("trayicon_right_clicked")); // 左击
    ADD_SIGNAL(MethodInfo("trayicon_left_clicked")); // 右击
    ADD_SIGNAL(MethodInfo( // 菜单点击
        "menu_item_selected", 
        PropertyInfo(Variant::INT, "id")
    ));
}


/**
 * 单例模式
 */
TTrayExtension * TTrayExtension::get_singleton()
{
    if (singleton == nullptr) {
        singleton = memnew(TTrayExtension); // Godot 内存分配
    }

    return singleton;
};


/**
 * 任务栏程序创建-供GDScript调用方法
 * const String &icon_path：任务托盘图标
 * const String &tooltip：悬停显示信息
 */
void TTrayExtension::gd_init_trayicon(const godot::String & icon_path, const godot::String & tooltip) 
{
    bool t = icon_path.begins_with("res://");
    if (t)
    {
        ERR_FAIL_MSG("ICON path error, please not use 'res://' path");
        return;
    }

    // 类名，使用的是C中的方法
    std::wstring unique_class = L"GodotTray_" + std::to_wstring(GetCurrentProcessId());
    m_unique_class = unique_class.c_str();

    // 转换字符串
    conversion_wstring(icon_path, m_icon_path);
    conversion_wstring(tooltip, m_tooltip);

    // 初始化
    init_register_class(); // 注册窗口
    init_create_window(); // 创建窗口
    // 创建菜单窗口
    hMenu = CreatePopupMenu(); 


    // 初始化托盘图标
    init_tray_icon(); 

    // 通过pid获取当前程序的 hwnd对象
    DWORD current_pid = GetCurrentProcessId();
    this->godot_hwnd = FindTopWindowByProcessId(current_pid);
}


/**
 * ======================= 注册隐藏窗口类 ================
 * 
 * 1.要使用WNDCLASSW、RegisterClassW、CreateWindowW带w的版本（Unicode）
 * 2.不带W的版本是ANSI版本，不应该使用
 */ 
void TTrayExtension::init_register_class()
{
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc; // 设置窗口过程函数（处理窗口消息）
    wc.hInstance = GetModuleHandle(NULL); // 设置当前程序实例句柄
    wc.lpszClassName = m_unique_class;
    
    // 注册
    ATOM t = RegisterClassW(&wc);

    // 检测注册信息
    if (!t) 
    {
        DWORD err = GetLastError();
        wchar_t msg[256];
        swprintf_s(msg, L"窗口类注册失败 (错误代码: 0x%X)", err);
        MessageBoxW(NULL, msg, L"错误", MB_ICONERROR);
        return;
    }
};


/** 
 * ====================== 创建隐藏窗口 =========================
 */
void TTrayExtension::init_create_window()
{
    hWnd = CreateWindowW(
        reinterpret_cast<LPCWSTR>(m_unique_class), // 注册的类名
        reinterpret_cast<LPCWSTR>(m_window_title_name),// 窗口标题（不会显示）
        0,  // 窗口样式（0表示最简单样式）
        0, 0, 0, 0, // 位置和大小
        NULL,  // 父窗口
        NULL, // 菜单
        GetModuleHandle(NULL), // 实例句柄
        NULL// 额外数据
    );

    // 验证窗口句柄是否创建成功
    if (!IsWindow(hWnd)) {
        MessageBoxW(NULL, L"窗口句柄无效!", L"错误", MB_ICONERROR);
        return;
    }
};


/**
 * ===================== 初始化托盘图标===========================
 */
void TTrayExtension::init_tray_icon()
{
    nid.hWnd = hWnd;// 有效的窗口句柄
    nid.uID = 1;// 唯一图标ID
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;// 必须包含这些标志
    nid.uCallbackMessage = WM_USER + 1; // 自定义消息ID

    nid.hIcon = (HICON)LoadImageW(
        NULL, 
        m_icon_path.c_str(),
        // L"D:/A_CodeItems/A_Taskbar_program/demo/assets/192-fish.ico",
        IMAGE_ICON,
        0, 0,
        // LR_SHARED  // 标志仅适用于系统资源
        LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
    );

    // 验证图标是否加载成功
    if (!nid.hIcon) {
        DWORD err = GetLastError();
        wchar_t msg[256];
        swprintf(msg, 256, L"托盘图标添加失败(错误代码: 0x%X)", err);
        MessageBoxW(NULL, msg, L"错误", MB_ICONERROR);
        return;
    }

    // 设置悬停提示文本（限制127个字符）
    // 由参数：tooltip设置
    wcscpy_s(
        nid.szTip, 
        m_tooltip.c_str()
    );

    // 添加到托盘
    BOOL t = Shell_NotifyIconW(NIM_ADD, &nid);
    // 检验
    if (!t) 
    {
        DWORD err = GetLastError();
        wchar_t msg[256];
        swprintf(msg, 256, L"shell_notifyIconW错误(错误代码: 0x%X)", err);
        MessageBoxW(NULL, msg, L"错误", MB_ICONERROR);
        return ;
    }
}; 


// 设置托盘图标大小
void TTrayExtension::gd_set_tray_icon_size(int x, int y)
{
    m_tray_icon_size_x = x;
    m_tray_icon_size_y = y;
    // 设置图标大小
}; 


/**
 * godot 转换为wstring类型
 */
void TTrayExtension::conversion_wstring(const String a, std::wstring & aim_string)
{
    // 获取 UTF-16 数据
    auto utf16_data = a.utf16();

    // 转换为 wchar_t* (Windows 兼容)
    const wchar_t* win_path = reinterpret_cast<const wchar_t*>(utf16_data.ptr());

    // 构造 std::wstring（需计算实际字符数，不包括null终止符）
    aim_string = std::wstring(win_path, utf16_data.size());
};


/**
 * 创建默认菜单菜单
 */
void TTrayExtension::create_default_menu() 
{
    // 如果没有菜单对象，就创建菜单对象
    if (!hMenu) 
    {
        hMenu = CreatePopupMenu();
    }
    
    // 添加默认菜单项（示例）
    AppendMenuW(hMenu, MF_STRING, 1001, L"Open");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL); // 分隔线
    AppendMenuW(hMenu, MF_STRING, 1002, L"Exit");

    // 验证，是否成功添加菜单项
    int count = GetMenuItemCount(hMenu);
    if (count <= 0) {
        UtilityFunctions::print("No Set Menu");
    }

}


/**
 * 显示菜单
 */
void TTrayExtension::gd_show_menu_item()
{
    if (!hMenu) {
        // 错误输出
        UtilityFunctions::printerr("hMenu is NULL, cannot add menu item!");
        UtilityFunctions::printerr("Maybe you need first use 'init_tray_icon()' then use 'add_menu_item()'");
        return;
    }

    // 检查菜单项数量，如果为0或-1则表示没有菜单项
    int itemCount = GetMenuItemCount(hMenu);
    if (itemCount == 0 || itemCount == -1) 
    {
        UtilityFunctions::printerr("Menu has no items! Count: ", String::num_int64(itemCount));
        return;
    }

    POINT pt; // 声明一个 POINT 结构体变量，用于存储鼠标坐标（x,y）
    GetCursorPos(&pt); // 获取当前鼠标指针的屏幕坐标（相对于屏幕左上角）

    // 将指定窗口设为前台窗口（关键步骤）
    // - 确保菜单能获得焦点并响应键盘操作
    // - 如果不调用，菜单可能无法正常消失或无法接收快捷键
    // 参数：hWnd 是窗口句柄（我们创建的隐藏消息窗口）
    SetForegroundWindow(hWnd); 

    // 在指定位置显示弹出菜单
    BOOL t = TrackPopupMenu(
        hMenu, // 菜单句柄（之前创建的 HMENU）
        TPM_RIGHTBUTTON, // 标志，表示这是右键触发的菜单
        pt.x, pt.y, // 菜单显示的屏幕坐标（从GetCursorPos获取）
        0, // 保留标志位
        hWnd, // 接收菜单命令消息的窗口（我们的消息窗口）
        NULL // 不使用特殊区域矩形
    );

    if (!t)
    {
        DWORD err = GetLastError();
        UtilityFunctions::printerr("TrackPopupMenu failed! Error: 0x", String::num(err));
        ERR_FAIL_MSG("popup menu ERRor");
    }

    // 发送空消息到窗口队列（关键清理步骤）
    // - 解决菜单可能残留的问题（Windows 消息队列的特殊要求）
    // - 确保菜单能正确销毁并释放资源
    // 参数：
    // hWnd - 目标窗口
    // WM_NULL - 空消息类型
    // 0, 0 - 未使用的消息参数
    PostMessage(hWnd, WM_NULL, 0, 0); // 解决菜单滞留问题
}; 


/**
 * 添加菜单项
 */
void TTrayExtension::gd_add_menu_item(const String & text, int id) 
{
    
    if (!hMenu) {
        // 错误输出
        UtilityFunctions::printerr("hMenu is NULL, cannot add menu item!");
        UtilityFunctions::printerr("Maybe you need first use 'init_tray_icon()' then use 'add_menu_item()'");
        return;
    }

    bool a = verify_menuitem_has_id(id);
    if (a)
    {
        UtilityFunctions::printerr("menu item id already exists, please use another id!");
        return;
    }

    if (text == "-")
    {
        // 添加分割线
        AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL); 
    }
    else
    {
        // 添加菜单
        std::wstring wtext;
        conversion_wstring(text, wtext);
        // 添加菜单项
        AppendMenuW(hMenu, MF_STRING, id, wtext.c_str());
        // 保存数据,对于普通添加没有什么用，主要是和带图标item相匹配
        m_menu_items[id] = MenuItemInfo{id, wtext.c_str(), MenuItemType::NO_ICON, nullptr};
    }
    
    // 测试，检查
    // int count = GetMenuItemCount(hMenu);
    // UtilityFunctions::print(vformat("当前菜单项数量: %d", count));
}


/**
 * 添加带有图标的item
 */
void TTrayExtension::gd_add_menu_item_with_icon(const godot::String & text, int id, const String & icon_path)
{
    if (!hMenu) {
        UtilityFunctions::printerr("hMenu is NULL, cannot add menu item!");
        return;
    }

    bool a = verify_menuitem_has_id(id); // 验证id是否已经存在
    if (a)
    {
        UtilityFunctions::print("menu item id already exists, please use another id!");
        return;
    }

    HICON hIcon = load_icon(icon_path);
    
    // 如果图标加载失败
    if (!hIcon) 
    {
        DWORD err = GetLastError();
        UtilityFunctions::printerr("Failed to load icon for menu item (ID: ", id, ", Error: 0x", String::num_uint64(err), ")");
        UtilityFunctions::printerr("0x2 means path is invalic");
        // 降级为普通菜单项
        // gd_add_menu_item(text, id);
        return;
    }

    // 转换文本
    std::wstring wtext;
    conversion_wstring(text, wtext);
    
    // 存储菜单项信息
    m_menu_items[id] = MenuItemInfo {id, wtext, MenuItemType::WITH_ICON, hIcon};
    
    // 创建菜单项（使用 MF_OWNERDRAW 标志）
    MENUITEMINFOW mii = { sizeof(MENUITEMINFOW) };
    mii.fMask = MIIM_FTYPE | MIIM_ID | MIIM_DATA;
    mii.fType = MFT_OWNERDRAW;  // 所有者绘制
    mii.wID = id;
    mii.dwItemData = id;  // 存储ID以便在绘制时获取
    
    // 必须使用InsertMenuItemW来插入菜单项,因为要传入更多参数
    InsertMenuItemW(hMenu, GetMenuItemCount(hMenu), TRUE, &mii);
};


/**
 * 移除菜单项
 */
void TTrayExtension::gd_remove_menu_item(int id) 
{
    MenuItemInfo item = m_menu_items[id];
    if (item.type == MenuItemType::WITH_ICON) 
    {
        // 带图标的item
        DestroyIcon(item.hIcon);
    }
    else
    {
        // 删除菜单项, 不带图标的item
        // DeleteMenu(hMenu, id, MF_BYCOMMAND); // 这个方法会删除菜单项，但不会释放图标资源
        // 使用InsertMenuItemW来删除菜单项，这样可以释放图标资源
        DeleteMenu(hMenu, id, MF_BYCOMMAND);
    }

    m_menu_items.erase(id); // 删除key    
}


// 隐藏godot项目
void TTrayExtension::gd_hide_godot_window()
{
    if (!this->godot_hwnd) 
    {
        UtilityFunctions::printerr("error, first use 'init_tray_icon()' function");
        return;
    }
    
    // 不显示在任务栏中
    // SetWindowLongPtr(this->godot_hwnd, GWL_EXSTYLE, GetWindowLongPtr(godot_hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
    ShowWindow(this->godot_hwnd, SW_HIDE);
}; 


// 显示godot窗体
void TTrayExtension::gd_show_godot_window()
{
    if (!this->godot_hwnd) 
    {
        UtilityFunctions::printerr("error, first use 'init_tray_icon()' function");
        return;
    }
  
    
    // 不显示在任务栏中
    ShowWindow(this->godot_hwnd, SW_SHOW);
    SetForegroundWindow(this->godot_hwnd);
}; 


/**
 * 函数：根据进程ID（PID）查找该进程的主窗口
 * 参数：pid - 要查找的进程ID
 * 返回值：找到的窗口句柄，如果没找到则返回nullptr
 */
HWND TTrayExtension::FindTopWindowByProcessId(DWORD pid) 
{
    // HWND g_hwnd = nullptr; // 初始化返回的窗口句柄为nullptr
    WindowSearchData data = {pid, nullptr};

    // 这个Lambda函数是EnumWindows的回调函数
    // 参数说明：
    //   hwnd  - 当前枚举到的窗口句柄，由windows自动填充
    //   lParam - 我们传入的用户数据（这里是我们定义的hwnd变量的地址）
    EnumWindows([](HWND t_hwnd, LPARAM lParam) -> BOOL 
    {
        WindowSearchData* data = (WindowSearchData *) lParam;

        DWORD windowPid; // 用于存储当前窗口所属的进程ID
        GetWindowThreadProcessId(t_hwnd, &windowPid); // 获取创建当前窗口的线程的进程ID

        // 检查条件：
        // 1. 当前窗口的进程ID是否等于我们要查找的进程ID
        // 2. 当前窗口是否可见（IsWindowVisible(hwnd)返回true）
        if (windowPid == data->pid && IsWindowVisible(t_hwnd)) 
        {
            data->result = t_hwnd; // 找到窗口，通过lParam传回
            return FALSE; // 停止枚举
        }
        return TRUE; // 继续枚举

    }, (LPARAM) & data);

    return data.result;
}


/**
 * 绘制item
 */
void TTrayExtension::draw_menu_item(LPDRAWITEMSTRUCT lpDrawItem)
{
    int id = (int)lpDrawItem->itemData; // 菜单项id
    
    // 获取菜单项信息
    auto it = m_menu_items.find(id);
    if (it == m_menu_items.end()) 
    {
        return;
    }
    
    const MenuItemInfo & info = it->second;
    
    // 获取DC和矩形区域
    HDC hDC = lpDrawItem->hDC; // 画板
    RECT rect = lpDrawItem->rcItem; // 画在哪
    
    
    // 设置背景颜色（根据选中状态）
    COLORREF bgColor;
    COLORREF textColor;
    
    // 1. 绘制背景（根据是否选中改变颜色）
    if (lpDrawItem->itemState & ODS_SELECTED) 
    {
        bgColor = RGB(0, 120, 215);  // 高亮蓝色
        textColor = RGB(255, 255, 255);  // 白色文字
    } 
    else 
    {
        bgColor = GetSysColor(COLOR_MENU);
        textColor = GetSysColor(COLOR_MENUTEXT);
    }
    
    // 填充背景
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(hDC, &rect, hBrush);
    DeleteObject(hBrush);
    
    // 绘制图标（16x16，留出边距）
    int iconX = rect.left + 2;
    int iconY = rect.top + (rect.bottom - rect.top - 16) / 2;
    
    if (info.hIcon) 
    {
        DrawIconEx(hDC, iconX, iconY, info.hIcon, 16, 16, 0, NULL, DI_NORMAL);
    }
    
    // 绘制文本
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, textColor);
    
    // 文本位置（图标右侧）
    RECT textRect = rect;
    textRect.left = iconX + 20;  // 图标宽度+间距
    
    // ✅ 获取系统菜单字体（而不是默认GUI字体）
    NONCLIENTMETRICSW ncm = { sizeof(NONCLIENTMETRICSW) };
    SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
    
    HFONT hFont = CreateFontIndirectW(&ncm.lfMenuFont);  // 菜单字体
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
    
    // 绘制文字
    DrawTextW(
        hDC, 
        info.text.c_str(),
        (int)info.text.length(),
        &textRect, 
        DT_SINGLELINE | DT_VCENTER | DT_LEFT
    );
    
    SelectObject(hDC, hOldFont);
    
    // 绘制焦点矩形（如果需要）
    if (lpDrawItem->itemState & ODS_FOCUS) 
    {
        DrawFocusRect(hDC, &rect);
    }
}; 


/**
 * 清空菜单项
 * */ 
void TTrayExtension::gd_clear_menu()
{
    if (!hMenu) 
    {
        return;
    }
    
    // 获取菜单项数量
    int count = GetMenuItemCount(hMenu);
    
    // 清理所有存储的图标资源
    for (auto& pair : m_menu_items) 
    {
        if (pair.second.type == MenuItemType::WITH_ICON)
        {
            DestroyIcon(pair.second.hIcon);
        }
        else
        {
            // MF_BYCOMMAND 通过ID获取菜单项位置
            DeleteMenu(hMenu, pair.second.id, MF_BYCOMMAND);
        }

    }

    m_menu_items.clear();
    
    UtilityFunctions::print("All menu items cleared");
};


/**
 * // 验证menu item变量有没有指定id
 */
bool TTrayExtension::verify_menuitem_has_id(int id)
{
    int n = m_menu_items.count(id);
    if (n > 0)
    {
        return 1;
    }

    return 0;
}; 


/**
 * 插入菜单项
 * 
 */
void TTrayExtension::gd_insert_menu_item(const String & text, int id, int position)
{
    if (!hMenu) 
    {
        UtilityFunctions::printerr("hMenu is NULL, cannot insert menu item!");
        return;
    }
    
    if (text == "-") 
    {
        // 插入分隔线
        InsertMenuW(hMenu, position, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    }
    else
    {
        bool a = verify_menuitem_has_id(id); // 验证id是否已经存在
        if (a)
        {
            UtilityFunctions::print("menu item id already exists, please use another id!");
            return;
        }

        // 转换文本
        std::wstring wtext;
        conversion_wstring(text, wtext);
        
        // 插入菜单项
        BOOL result = InsertMenuW(hMenu, position, MF_BYPOSITION | MF_STRING, id, wtext.c_str());

        if (result) 
        {
            // 存储菜单项信息
            m_menu_items[id] = MenuItemInfo {id, wtext, MenuItemType::NO_ICON, nullptr};
        }
        else 
        {
            DWORD err = GetLastError();
            UtilityFunctions::printerr("InsertMenu failed: 0x", String::num(err));
        }
    }
    
    
}; 


/**
 * 插入菜单项
 */
void TTrayExtension::gd_insert_menu_item_with_icon(const String& text, int id, int position, const String& icon_path)
{
    if (!hMenu) {
        UtilityFunctions::printerr("hMenu is NULL, cannot insert menu item!");
        return;
    }

    bool a = verify_menuitem_has_id(id); // 验证id是否已经存在
    if (a)
    {
        UtilityFunctions::print("menu item id already exists, please use another id!");
        return;
    }
    
    HICON hIcon = load_icon(icon_path); // 加载图标
    
    if (!hIcon) {
        DWORD err = GetLastError();
        UtilityFunctions::printerr("Failed to load icon for menu item ID ", id, ", error: 0x", String::num(err));
        return;
    }

    // 转换文本和图标路径
    std::wstring wtext;
    conversion_wstring(text, wtext);
    
    // 创建所有者绘制菜单项
    MENUITEMINFOW mii = { sizeof(MENUITEMINFOW) };
    mii.fMask = MIIM_FTYPE | MIIM_ID | MIIM_DATA;
    mii.fType = MFT_OWNERDRAW;
    mii.wID = id;
    mii.dwItemData = id;
    
    BOOL result = InsertMenuItemW(hMenu, position, TRUE, &mii);
    
    if (result) 
    {
        m_menu_items[id] = MenuItemInfo {id, wtext, MenuItemType::WITH_ICON, hIcon};
    } 
    else 
    {
        DWORD err = GetLastError();
        UtilityFunctions::printerr("InsertMenuItem failed: 0x", String::num(err));
    }
}; 


 // 加载图标
HICON TTrayExtension::load_icon(const godot::String & icon_path)
{
    // 转换图标路径
    std::wstring wicon_path;
    conversion_wstring(icon_path, wicon_path);
    
    // 加载图标（推荐使用16x16或32x32的小图标）
    HICON hIcon = (HICON)LoadImageW(
        NULL,
        wicon_path.c_str(),
        IMAGE_ICON,
        16, 16,  // 设置为16x16像素，好像修改没有效果
        LR_LOADFROMFILE
    );

    return hIcon;
};