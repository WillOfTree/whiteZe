# Aseprite编译方法

## Github编译

1. 将项目fork到自己仓库：[Aseprite GitHub 地址](https://github.com/aseprite/aseprite)

2. 创建工作流：

   在自己fork的Aseprite项目中点击“Action按钮”，然后创建工作流

3. 修改build.yml文件

   build.yml目录：`<Code>/.github/workflows/build.yml`

   ``` yaml
   name: build
   on: [push, pull_request]
   jobs:
     build:
       runs-on: ${{ matrix.os }}
       strategy:
         fail-fast: false
         matrix:
           os: [windows-latest]
           build_type: [Release]
           enable_ui: [on]
           include:
             - os: windows-latest
               build_type: Release
               enable_ui: on
       steps:
       - uses: actions/checkout@v3
         with:
           submodules: 'recursive'
       - name: ccache
         uses: hendrikmuhs/ccache-action@v1
         if: runner.os == 'Linux'
         with:
           key: ${{ matrix.os }}-${{ matrix.enable_ui }}
       - uses: seanmiddleditch/gha-setup-ninja@master
       - uses: ilammy/msvc-dev-cmd@v1
         if: runner.os == 'Windows'
       - name: Install Dependencies
         shell: bash
         run: |
           if [[ "${{ runner.os }}" == "Linux" ]] ; then
             sudo apt-get update -qq
             sudo apt-get install -y \
               libx11-dev libxcursor-dev libxi-dev
           fi
       - name: Generating Makefiles
         shell: bash
         run: |
           if [[ "${{ runner.os }}" == "Windows" ]] ; then
             export enable_ccache=off
           else
             export enable_ccache=on
           fi
           curl -L https://github.com/blueloveTH/aseprite/releases/download/v0.01/skia.zip --output skia.zip
           7z x skia.zip
           cmake -S . -B build -G Ninja \
             -DCMAKE_BUILD_TYPE=${{ matrix.build_type }} \
             -DENABLE_UI=${{ matrix.enable_ui }} \
             -DENABLE_CCACHE=$enable_ccache \
             -DLAF_BACKEND=skia \
             -DSKIA_DIR=./skia \
             -DSKIA_LIBRARY_DIR=./skia/out/Release-x64 \
             -DSKIA_LIBRARY=./skia/out/Release-x64/skia.lib
       - name: Compiling
         shell: bash
         run: |
           cd build && ninja
       - uses: actions/upload-artifact@v3
         with:
           name: aseprite
           path: |
             D:/a/aseprite/aseprite/build/bin/data
             D:/a/aseprite/aseprite/build/bin/aseprite.exe
   ```

4. 保存build.yml文件

5. 等待编译完成，点击完成的工作流，进入后下载软件

## windows编译

1. 需要clone Aseprite代码：https://github.com/aseprite/aseprite/releases 

2. 安装CMake：https://cmake.org/download/

3. 下载Ninja： https://github.com/ninja-build/ninja/releases 

4. 将Ninja解压到CMake\bin目录下

5. 下载Skia库：https://github.com/aseprite/skia/releases 

6. 下载Visual Studio Community 2022，安装后选择`使用C++的桌面开发`，并选择`Windows 11 SDK` 

7. 文件目录

   ``` shell
   aseprite-compile
   ├─Skia-Windows-Release-x64
   └─Aseprite
   ```

8. 运行命令

   ``` shell
   cmake 
   	-DCMAKE_BUILD_TYPE=RelWithDebInfo 
   	-DLAF_BACKEND=skia 
   	# 修改路径
   	-DSKIA_DIR=aseprite-compile\Skia-Windows-Release-x64 
   	# 修改路径
   	-DSKIA_LIBRARY_DIR=aseprite-compile\Skia-Windows-Release-x64\out\Release-x64 
   	# 修改路径
   	-DSKIA_LIBRARY=aseprite-compile\Skia-Windows-Release-x64\out\Release-x64\skia.lib -G Ninja ..
   ```

9. 打包

   `aseprite-compile\Aseprite\build`：运行`ninja aseprite` 