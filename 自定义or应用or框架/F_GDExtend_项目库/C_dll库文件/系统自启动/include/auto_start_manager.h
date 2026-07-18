/**
 * @file system_auto_start.h
 * @brief 用于系统自启动
 *
 * @author 叙白
 * @date 2025-07-12
 */
#ifndef __TAutoStartManager_CPP_H__
#define __TAutoStartManager_CPP_H__

#include <godot_cpp/classes/object.hpp>

#include <windows.h>
#include <string>


//? 向前引用，间接引用的类，也需要向前引用声明
namespace godot
{
    class String;
}


class TAutoStartManager : public godot::Object
{
    GDCLASS(TAutoStartManager, godot::Object);

public:
    static TAutoStartManager * get_singleton(); // 获取静态对象

protected:
    static void _bind_methods();

private:
    std::wstring m_APP_NAME = L"MyGodotApp";  // 可以改成你的应用名称
    static TAutoStartManager * singleton; // 静态对象

    LPCWSTR m_run_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run"; // 注册表路径

    //! 核心功能
    HKEY get_run_key();  // 获取注册表Run键的句柄
    void set_autostart(bool enable, godot::String parameter=""); // 设置开机自启（enable=true添加，false删除）
    bool is_autostart_enabled(); // 查询是否已设置为开机自启
    
    //! 辅助函数
    void change_app_name(godot::String app_name); // 修改应用名称
    godot::String get_executable_path(); // 获取可执行文件的路径
    void string_conversion_wstring(const godot::String a, std::wstring & aim_string); // godot string 转换为 wstring类型
};
#endif