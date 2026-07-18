# 调用外部程序

1. **已经在SConscript脚本中配置完毕**，只需配置external_lib_path、external_lib这两个变量就可实现
2. 另外，在GDExtension中使用库函数时，应引入其对应得头文件

## 调用windows库

1. 配置SConscript脚本，设置`env.Append(LIBS=["mylib"])` （无需扩展名）

   window系统库的扩展文件，不用复制，直接在SConscript中添加库名即可

   ``` python
   # 添加windows系统库使用，不用复制扩展库
   external_lib = ["user32", "shell32"]
   env.Append(LIBS=external_lib) 
   ```

2. 在需要使用的GDExtension中的C++文件中引入头文件即可

   ``` c++
   // 例如系统库，user32、shell32只需引入windows.h文件即可
   #include <windows.h>
   ```

## 调用动态链接库

1. 复制库文件到指定目录`external`

2. 与调用window库相同，首先要添加库的地址

   ``` python
   # 添加自定义第三方库的路径（仅你的库需要）
   env.Append(LIBPATH=["external"])  # 第三方库的目录
   ```

3. 配置库名称（对于系统库，只需在 `LIBS` 中声明名称，**无需**指定 `LIBPATH`。编译器会自动在系统目录中查找这些库。）

   ``` python
   env.Append(LIBS=[
       "user32",       # Windows 系统库，不用设置LIBPATH
       "shell32",      # Windows 系统库，不用设置LIBPATH
       "my_custom_lib" # 第三方库（不需要扩展名）
   ])
   ```

4. 在需要使用的GDExtension中的C++文件中引入头文件即可

