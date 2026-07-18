# ESP32开发说明

## 提前准备

### 一、开发方式

| 开发平台        | 说明                                                         |      |
| --------------- | ------------------------------------------------------------ | ---- |
| MicroPython     | 常用的开发软件为Thonny，支持Python，容易上手                 |      |
| Arduino         | 分为硬件与软件2部分<br>硬件为Arduino开发板（如Nano、Uno等）<br>软件为Arduino语言，Arduino编程基于C++，但是简化了部分语法，不是C++<br>使用Arduino IDE编写代码 |      |
| ESP-IDE         | 乐鑫物联网开发框架，基于C/C++，提供了一个自给自足的SDK，可以开发通用应用程序 |      |
| Lua、JaveScript | 小众开发                                                     |      |

### 二、参数说明

#### Ⅰ、芯片参数

经典双核系列（ESP32原版）

- ESP-WROOM-32 / ESP32 / ESP32-DOWD：**核心模组**，旧型号，教程多资料多

  主打 **2.4G Wi-Fi 4 + 经典蓝牙** 

RISC-V新架构

- ESP32-C 系列

  核心架构 (CPU)：RISC-V 单核 (C3/C6)

  主打方向/特长：**连接与性价比**：专注于Wi-Fi/蓝牙连接的低成本、低功耗IoT设备

  典型应用场景：智能插座、传感器、简单控制设备、蓝牙遥控器

AI 与多媒体旗舰

- ESP32-S 系列

  核心架构 (CPU)：Xtensa LX7 双核 (S3) / RISC-V 双核 (S31)

  主打方向/特长：**高性能、AI与多媒体**：支持摄像头、显示屏、AI加速指令

  典型应用场景：智能音箱、摄像头、边缘AI设备、复杂的HMI人机界面

极致低功耗

- ESP32-P 系列

  核心架构 (CPU)：RISC-V 双核/单核 (P4)

  主打方向/特长：**高性能通用MCU**：不带无线功能，但性能强劲，外设丰富

  典型应用场景：工业HMI、网关、高性能嵌入式控制

- ESP32-H 系列

  核心架构 (CPU)：RISC-V 单核

  主打方向/特长：**专注于Matter/Thread/Zigbee**，低功耗，专为智能家居网状网络设计

  典型应用场景：智能灯泡、窗帘电机、温控器、Matter设备

#### Ⅱ、串口芯片

> 它负责把电脑USB口的信号翻译成开发板能懂的串口信号，让你能直接通过USB线给板子烧录程序。

- CH340：便宜常见，

- CP2102：

  **驱动更省心（优势）**：**CP2102 的驱动是Windows系统自带**的。插上电脑通常自动识别为COM口，基本不用手动找驱动，比CH340省去不少麻烦。

  **体积更小（特点）**：CP2102芯片非常小，所以常出现在**紧凑型**或**低功耗**的开发板上。缺点是如果焊接不牢，比CH340更容易虚焊。

### 三、文档集合

- [环境配置与ESP32文档](https://docs.waveshare.net/ESP32-ESP-IDF-Tutorials/ESP-IDF-Installation) 
- [ESP-IDF VS code扩展文档](https://docs.espressif.com/projects/vscode-esp-idf-extension/zh_CN/latest/index.html) 
- [ESP-IDF编程指南](https://docs.espressif.com/projects/esp-idf/zh_CN/v6.0/esp32s3/get-started/index.html) 

### 四、一些名称

- **电源类（别接错，会烧板子）**：
  - **GND**：**地线/负极**。所有外设都要共地（连在一起）。
  - **3V3**：**3.3伏正极输出**。给小型传感器供电，**最大电流约600mA**，别带大电机。
  - **V5**：**5伏正极**。直接从USB口来的，电压不稳，**建议别用来给外设供电**，容易烧坏传感器。
- **控制类（核心操作）**：
  - **RST**：**重启按钮**。按下去板子就从头运行，死机时按它比拔线快。
- **通信类（烧录代码必用）**：
  - **RX/TX**：**串口收发引脚**。`TX`发数据，`RX`收数据。**烧录程序时千万别接任何东西**，否则会冲突导致烧录失败。这两个脚默认接在USB芯片上，平时不用管。
- **数字编号（1到23）**：这就是**GPIO编号**。比如`D2`就代表GPIO 2号脚。除了编号，记住两条铁律：
  1. **输入用**：接按钮、人体红外传感器。
  2. **输出用**：接LED灯、蜂鸣器、舵机信号线。

## 环境配置

### 一、VS code + ESP-IDF

> 使用VS code +  ESP-IDF 扩展 的方式开发（这是目前最主流且对新手最友好的方法。）

ESP-IDF 安装备注

1. 安装ESP-IDF（优先使用离线安装，离线安装能修改安装路径）

2. 安装驱动程序

3. 验证ESP-IDF安装是否成功

   - 打开IDF_v6.X_Powershell

     1. 查看桌面是否存在
     2. 打开ESP-IDF安装软件（eim-gui-windows-x64.exe）$\to$  打开管理面版 $\to$ 打开IDF终端

   - 输入`idf.py --version` 正确输出版本既安装成功

     若没有可能需要将IDF_PATH、IDF_TOOLS_PATH、IDF_PYTHON_ENV_PATH路径添加进系统变量

VS code 安装备注

1. 安装ESP-IDF插件（2.0.0以上版本会自动检测ESP-IDF环境）
2. 安装C/C++ Extension Pack

## 编辑器操作

### 一、创建新项目

VS code 扩展 ESP-IDF $\to$ Advanced $\to$ 新项目向导（创建新项目）$\to$ 选择ESP-IDF版本 $\to$ 选择模板

- 需要选择ESP-IDF版本，直接选择提前下载的即可（可能启动时间会长一点，需要等待）

- 关于模板，ESP提前预设了多种不同模板（ESP-IDF Templates）与示例（ESP-IDF Examples），根据需求选择

- 创建新项目

  1. Enter Project directory：项目目录，不允许中文、空格、特殊字符、也不宜过长

  2. Choose ESP-IDF Target：选择目标芯片，最终要在哪个板子上运行代码

  3. Choose ESP-IDF Board：官方预设的参数，非官方硬件，可以选择Custom board或空白

     `chip with LP core`：低功耗核心

     `via builtin USB-JTAG`：使用内置 USB-JTAG 调试工具，默认选择这个即可（via：调试工具）

     `via ESP-prog`：使用外置 ESP-PROG 调试工具

     `via ESP-PROG-2`：ESP-PROG的升级版

  4. Choose seral port：选择串口，告诉编译器，使用哪个串口连接的板子

  5. Add your ESP-IDF Component directory：组件库目录，包括屏幕

### 二、编译选项说明

位置：VS code 最下方

![](assets/屏幕截图 2026-06-14 171507.png)

- ![](assets/屏幕截图 2026-07-12 223215.png)：IDF的版本
- UART：烧录方式，一般选择UART即可
- COM3：串口，若不清楚，可以拔掉再插上USB进行查看
- esp32c6：目标芯片，与你的设备芯片选择相同即可，第一次配置，会需要一点时间
- 🔧：编译，会在项目中生成build文件夹
- ⚡：烧录
- ![](assets/屏幕截图 2026-06-14 172529.png)：监视设备，用于监视硬件输出，退出监视模式`ctrl + ]` 
- ![](assets/屏幕截图 2026-06-14 172851.png)：SDK配置编辑器，可以修改板子的一些设置过的参数
- ![](assets/屏幕截图 2026-06-14 173155.png)：一键运行，ESP-IDF会依次运行构建、烧录、监视3个步骤

### 三、关于includePath设置

- 推荐使用compileCommands来配置，这样只要编译过，就可以自动添加头文件

使用命令 `Ctrl + Shift + P`或者`F1` $\to$ 创建c_cpp_properties.json文件$\to$ 添加配置

- 命令输入：`C/C++: Edit Configurations (JSON)` 

- 添加（位置与`name`同一级）：

  `"compileCommands": "${workspaceFolder}/build/compile_commands.json",` 

  
