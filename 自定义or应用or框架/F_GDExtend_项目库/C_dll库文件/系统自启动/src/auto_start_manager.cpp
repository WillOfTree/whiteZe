/**
 * @file tray_extension.cpp
 * @brief 实现 Windows 系统托盘图标功能，集成 Godot。
 * 
 * 如果需要从godot中获取参数，可以使用OS.get_cmdline_user_args()获取参数，在godot编辑器中
 * 
 * 信号：
 * emit_signal("system_auto_start_error", 1, error_text);
 *
 * @author 叙白
 * @date 2025
 */
#include "objects/auto_start_manager.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

// 静态成员初始化
TAutoStartManager * TAutoStartManager::singleton = nullptr;


void TAutoStartManager::_bind_methods()
{
    //! 供GDScript调用方法
    ClassDB::bind_method(D_METHOD("set_app_name", "app_name"), &TAutoStartManager::change_app_name); // 设置应用名称
    ClassDB::bind_method(
        D_METHOD("set_autostart", "enable", "parameter"), 
        &TAutoStartManager::set_autostart, 
        DEFVAL(String()) // 设置parameter默认参数为字符串""
    ); // 设置自启动
    ClassDB::bind_method(D_METHOD("detecting_autostart_enabled"), &TAutoStartManager::is_autostart_enabled); // 检查自启动是否开启
    
    //! 单例
    ClassDB::bind_static_method("TAutoStartManager", D_METHOD("get_singleton"), &TAutoStartManager::get_singleton);
    
    //! 信号
    //# 错误代码 1：无法打开注册表
    //# 错误代码 2：无法获取注册表Run键的句柄
    //# 错误代码 3：写入注册表失败
    //# 错误代码 4：删除注册表失败
    ADD_SIGNAL(MethodInfo( // 菜单点击
        "system_auto_start_error",
        PropertyInfo(Variant::INT, "code"), // 错误代码
        PropertyInfo(Variant::STRING, "info") // 错误提示
    ));

    //# 成功代码 1：开机自启已启用
    //# 成功代码 0：开机自启已禁用
    ADD_SIGNAL(MethodInfo( // 菜单点击
        "system_auto_start_success",
        PropertyInfo(Variant::INT, "code"), // 成功代码
        PropertyInfo(Variant::STRING, "info") // 成功提示
    ));
}


/**
 * 单例
 */
TAutoStartManager * TAutoStartManager::get_singleton()
{
    if (TAutoStartManager::singleton == nullptr)
    {
        TAutoStartManager::singleton = memnew(TAutoStartManager);
    }

    return TAutoStartManager::singleton;
};


/**
 * 获取可执行应用路径
 */
String TAutoStartManager::get_executable_path() 
{
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return String(path);
}


/**
 * 获取注册表Run键的句柄（使用当前用户路径，无需管理员权限）
 **/ 
HKEY TAutoStartManager::get_run_key() 
{
    HKEY hKey; // 注册表句柄
    LONG result = RegOpenKeyExW(
        HKEY_CURRENT_USER, // 使用HKCU，无需管理员权限 [citation:1][citation:7]
        m_run_key, // L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0,
        KEY_SET_VALUE | KEY_QUERY_VALUE, // 设置和查询权限
        &hKey
    );
    
    if (result != ERROR_SUCCESS) // 打开注册表失败
    {
        String error_text = "open registry key failed, error code: " + String::num((int64_t)result);
        emit_signal("system_auto_start_error", 1, error_text);
        return NULL;
    }
    
    return hKey;
}


/**
 * 设置开机自启（enable=true添加，false删除）
 */
void TAutoStartManager::set_autostart(bool enable, String parameter) 
{
    HKEY hKey = get_run_key(); // 获取注册表Run键的句柄

    if (!hKey)
    {
        emit_signal("system_auto_start_error", 2, "无法获取注册表Run键的句柄");
        return;
    }
    
    
    //# 获取当前程序路径
    String exe_path = get_executable_path();

    // 检查是否有参数
    String target_character = "";
    if (parameter != "")
    {
        target_character = exe_path + " " + parameter;
    }
    else
    {
        target_character = exe_path; // 默认情况下，只设置可执行文件路径
    }
    
    //# 转换为wstring类型
    std::wstring exe_path_ws;
    string_conversion_wstring(target_character, exe_path_ws);

    //# 验证app名称是否配置
    if (m_APP_NAME == L"MyGodotApp") 
    {
        print_error("current registered app name is 'MyGodotApp'"); 
        print_error("you can change it by calling 'set_app_name' function");
    }

    
    if (enable) {
        // 写入注册表 [citation:2][citation:6]
        LONG result = RegSetValueExW(
            hKey,
            m_APP_NAME.c_str(),
            0,
            REG_SZ,                           // 字符串类型 [citation:7]
            (const BYTE*)exe_path_ws.c_str(),
            (exe_path_ws.length() + 1) * sizeof(wchar_t)
        );
        
        if (result == ERROR_SUCCESS) 
        {
            emit_signal("system_auto_start_success", 1, "startup enabled");

        } else {
            String error_text = "write registry value failed, error code: " + String::num((int64_t)result);
            emit_signal("system_auto_start_error", 3, error_text);
        }
    } else {
        // 删除注册表项 [citation:1]
        LONG result = RegDeleteValueW(hKey, m_APP_NAME.c_str());
        
        if (result == ERROR_SUCCESS || result == ERROR_FILE_NOT_FOUND) 
        {
            emit_signal("system_auto_start_success", 0, "startup disabled");

        } else {
            String error_text = "delete registry value failed, error code: " + String::num((int64_t)result);
            emit_signal("system_auto_start_error", 4, error_text);
        }
    }
    
    RegCloseKey(hKey); // 关闭注册表句柄
}


/**
 * 查询是否已设置为开机自启
 * 
 * @return true 已启用，false 未启用
 */
bool TAutoStartManager::is_autostart_enabled() {
    HKEY hKey = get_run_key(); // 打开注册表Run键

    if (!hKey)
    {
        emit_signal("system_auto_start_error", 2,"无法获取注册表Run键的句柄");
        return 0;
    }
    
    wchar_t path[MAX_PATH]; // 存储路径
    DWORD size = sizeof(path); // 存储路径长度
    DWORD type = REG_SZ; // 存储路径类型
    
    LONG result = RegQueryValueExW(
        hKey,
        m_APP_NAME.c_str(),
        NULL,
        &type,
        (LPBYTE)path,
        &size
    );
    
    RegCloseKey(hKey);
    
    return (result == ERROR_SUCCESS);  // 存在即为已启用 [citation:7]
}


/**
 * 修改应用名称
 * 
 * @param app_name 应用名称
 */
void TAutoStartManager::change_app_name(String app_name)
{
    string_conversion_wstring(app_name, m_APP_NAME);
}


/**
 * godot string转换为wstring类型
 * 
 * @param a godot string
 * @param aim_string wstring类型
 * 
 * @example
 *  String a = "你好，世界";
 *  std::wstring wtext;
 *  string_conversion_wstring(a, wtext);
 */
void TAutoStartManager::string_conversion_wstring(const String a, std::wstring & aim_string)
{
    // 获取 UTF-16 数据
    auto utf16_data = a.utf16();

    // 转换为 wchar_t* (Windows 兼容)
    const wchar_t* win_path = reinterpret_cast<const wchar_t*>(utf16_data.ptr());

    // 构造 std::wstring（需计算实际字符数，不包括null终止符）
    aim_string = std::wstring(win_path, utf16_data.size());
};