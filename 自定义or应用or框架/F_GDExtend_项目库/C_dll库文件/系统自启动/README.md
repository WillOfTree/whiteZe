# 系统自启动

## 信号

**system_auto_start_error**

- 错误代码 1：无法打开注册表
- 错误代码 2：无法获取注册表Run键的句柄
- 错误代码 3：写入注册表失败
- 错误代码 4：删除注册表失败

``` c++
ADD_SIGNAL(MethodInfo( // 菜单点击
	"system_auto_start_error",
	PropertyInfo(Variant::INT, "code"), // 错误代码
	PropertyInfo(Variant::STRING, "info") // 错误提示
));
```

 **system_auto_start_success**

- 成功代码 1：开机自启已启用
- 成功代码 0：开机自启已禁用

``` c++
ADD_SIGNAL(MethodInfo( // 菜单点击
	"system_auto_start_success",
	PropertyInfo(Variant::INT, "code"), // 成功代码
	PropertyInfo(Variant::STRING, "info") // 成功提示
));
```

## 方法

``` python
func _ready() -> void:
    ## 获取静态对象
	var _system = TAutoStartManager.get_singleton()
    ## 检查自动启动状态
    var g = _system.detecting_autostart_enabled();
	print(g)
    ## 设置应用名称
	_system.set_app_name("xxxxx")
    ## 核心：设置自启动
    # 1打开系统自启动
    # 0关闭系统自启动
	_system.set_autostart(0)
	## 信号方法，错误信息
	_system.system_auto_start_error.connect(test_error)
    ## 信号方法，成功信号
    _system.system_auto_start_success.connect(test_success)

func test_error(code, info):
    pass

func test_success(code, info):
    pass
	
```

