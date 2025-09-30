# README

## 获取实例

``` python
# 所有功能的核心
var t = TTrayExtension.get_singleton()
```

## 初始化

- `init_tray_icon(p, "提示信息")`：p托盘图标位置，一般为绝对路径，不能使用res://路径

``` python
# res:// 转换为绝对路径
var p = ProjectSettings.globalize_path("res://assets/192-fish.ico")

# 初始化托盘程序
t.init_tray_icon(p, "提示信息")
```

## 添加菜单

- `add_menu_item(“标题”, id)`：id用于区分点击的对象

``` python
t.add_menu_item("主页", 1001);
t.add_menu_item("隐藏", 1003);

# 添加分割线
t.add_menu_item("-", 0); 
```

## 连接信号

``` python
# 连接信号-托盘图标右击
t.trayicon_right_clicked.connect(right_click) 

# 连接信号-托盘图标左击
t.trayicon_left_clicked.connect(left_click)
	
# 连接信号-菜单单击
t.menu_item_selected.connect(menu_item_click)
```

菜单响应方法

``` python
# 显示右击菜单，信号触发方法
func right_click() ->void:
	var t = TTrayExtension.get_singleton()
	t.show_menu_item() # 显示菜单
	pass

# 单击连接信号
func left_click() ->void:
	pass

# 菜单项单击事件
# a是菜单的id，根据不同的id触发不同的方法
func menu_item_click(a:int) -> void:
	match a:
		1002: get_tree().quit()	
        1001: TTrayExtension.get_singleton().show_window()
        1003: TTrayExtension.get_singleton().hide_window()
	pass
```

## 其他方法

- `t.show_menu_item()` ：显示托盘的菜单栏
- `t.show_window()`：显示窗体
- `t.hide_window()`：隐藏窗体
- `t.remove_menu_item(id)`：移出菜单项，参数：id
