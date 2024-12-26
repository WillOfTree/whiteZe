#!/usr/bin/env python
import os
import sys

# 导入SConstruct环境
env = SConscript("external/godot-cpp/SConstruct")

#------------设置----------------------------------

sources = []      # Cpp文件位置
CPPPATH_temp = [] # 头文件位置

# 设置生成库的文件路径
libpath = "./demo/bin/{}/lib{}{}".format(env["platform"], env['suffix'], env['SHLIBSUFFIX'])

#------------准备函数-------------------------------

# 遍历目录和文件
def recursive_listdir():
    paths = os.walk(r'src')
    # path：路径
    # dir_list：目录
    # file_lst：文件
    for path, dir_list, file_lst in paths:
        
        # .h文件目录
        #CPPPATH_temp.append(path) # 添加目录

        for dir_name in file_lst:
            file_extension = os.path.splitext(dir_name) # 获取文件后缀
           
            if file_extension[1] == ".cpp":
                sources.append(Glob(os.path.join(path, dir_name)))
                # sources.append(os.path.join(path, dir_name))


def recursive_head_files():
    paths = os.walk(r'include')
    # path：路径
    # dir_list：目录
    # file_lst：文件
    for path, dir_list, file_lst in paths:
        # .h文件目录
        CPPPATH_temp.append(path) # 添加目录

#--------------------------------------------------

recursive_listdir()
recursive_head_files()

# 添加Cpp文件夹路径
env.Append(CPPPATH = CPPPATH_temp)

sharedlib = env.SharedLibrary(libpath, sources)
# 设置scons默认编译的文件
env.Default(sharedlib)

# 跨平台编译设置
# if env["platform"] == "macos":
#     library = env.SharedLibrary(
#         "demo/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
#             env["platform"], env["target"], env["platform"], env["target"]
#         ),
#         source=sources,
#     )
#     env.Default(library)

# windows
# elif env["platform"] == "windows":
#     # 设置生成库的文件路径
#     # libpath = "./demo/bin/libcpp{}{}".format(env['suffix'], env['SHLIBSUFFIX'])
#     sharedlib = env.SharedLibrary(libpath, sources)
#     # 设置scons默认编译的文件
#     env.Default(sharedlib)
#     pass

# # Linux
# elif env["platform"] == "linux":
#     pass

# # andio
# elif env["platform"] == "android":
#     sharedlib = env.SharedLibrary(libpath, sources)
#     # 设置scons默认编译的文件
#     env.Default(sharedlib)
#     pass

# else :
#     # "demo/bin/libgdexample.{}.{}.framework/libgdexample.{}.{}".format(
#     #         env["platform"], env["target"], env["platform"], env["target"]
#     #     ),

#     sharedlib = env.SharedLibrary(libpath, sources)
#     # 设置scons默认编译的文件
#     env.Default(sharedlib)
#     pass