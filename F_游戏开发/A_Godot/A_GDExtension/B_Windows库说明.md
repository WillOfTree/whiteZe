# Windows库说明

## 额外的库

1. user32.lib：包含 DefWindowProcW, PostQuitMessage, RegisterClassW, CreateWindowExW
2. shell32.lib：包含 Shell_NotifyIconW
3. comctl32.lib：包含 LoadImageW（不需要也可以使用）
4. 头文件：`#include <windows.h>` 

## 出现的错误信息

| 错误符号                | 所属库      | 功能         |
| :---------------------- | :---------- | :----------- |
| __imp_DefWindowProcW    | user32.lib  | 默认窗口过程 |
| __imp_PostQuitMessage   | user32.lib  | 退出消息循环 |
| __imp_RegisterClassW    | user32.lib  | 注册窗口类   |
| __imp_CreateWindowExW   | user32.lib  | 创建窗口     |
| __imp_LoadImageW        | user32.lib  | 加载图像资源 |
| __imp_Shell_NotifyIconW | shell32.lib | 系统托盘操作 |

## 
