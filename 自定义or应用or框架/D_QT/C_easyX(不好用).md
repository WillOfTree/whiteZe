# easyX

## 基本介绍

EasyX是封装了windows API库，只能用在windows上，用于C/C++学习，有很多问题，实际生产环境中不可能用于开发游戏

## 基本绘图 

1、坐标默认原点是窗口左上角，x轴右为正，y轴下为正，度量单位是像素点

2、在EasyX中设备分为2种，一种是默认绘图窗口，一种是IMAGE对象，通过SetWorkingImage函数可以设置当前绘制的窗口，设置绘制窗口后，所有的绘图都会绘制这个设备上

3、EasyX is only for C++

- vs2022没有这个错误
- vs2022之前的版本要创建cpp程序

4、头文件：`#include <easys.h>`

### 一、窗口操作函数

``` c++
// 旧版的是graph.h
#include <easyx.h>

/*
创建窗口
@width: 窗体宽度
@height：窗体高度
@flag：窗体样式
	SHOWCONSOLE：显示控制台
*/
initgraph(int width, int height, int flag=NULL);
// 用于防止窗口闪退
getchar();

/* 关闭绘图窗口 */
closegraph();
/* 清空绘图设备，每次绘图完成后都应设置 */
cleardevice();
```

设置填充颜色：`setfillcolor(YELLoW);`

设置线条颜色：`setlinecolor(BLUE);`

设置线条样式：`setlinestyle(样式，线的宽度)`

- 样式：PS_SOILID（实线）
- 宏定义种有更多线条样式

设置背景颜色：`setbkcolor(WHITE)`

- 需要使用清空cleardevice()函数清空黑色背景

### 二、绘图函数

常用的画图函数

- `circle(int x, int y, int radius)`：画饼
- `ellipse(int x, int y, int radius)`：椭圆
- `pie(int x, int y, int radius)`：扇形
- polygon：多边形
- `rectangle(x, y, 常, 宽)`：矩形
- roundrect：圆角矩形
- line：线
- putpixel：画点

以圆形为列

``` c++
/*
圆，无填充
@x：x坐标
@y：y坐标
@radius：半径
*/
circle(int x, int y, int radius);

/* 有边框填充的圆（关键字fill） */
fillcircle(int x, int y, int radius);
/* 无边框填充（关键字soli） */
solidcircle(int x, int y, int radius)
```

### 三、文字绘图

``` c++
/* 在指定位置输出字符串 */
outtextxy(int x, int y, LPCTSTR str);

/* 设置字体颜色 */
// 字体默认是白色
settextcolor(COLORREF color);

/* 设置字体样式 
@height：指定高度
@width：字符宽度，0自适应
@ipsface：字体名称
*/
settextstyle(int height, int width, LPCTSTR ipszface);
settextstyle(20, 0, "楷体");

/* 设置居中 */
textheight(LPCTSTR str);
textwidth(LPCTSTR str);
// 样例
char arr[] = "字符串大小";
int height = 框的高度/2-textheight(arr);
int width = 框的宽度/2-textwidth(arr);
outtextxy(width+框的位置，height+框的位置， (Lxxx)arr);
```

error c2665错误：“outtextxy”

- `outtextxy(50, 50, L"字符串加L")`
- `outtextxy(50, 50, TEXT("字符串加L"))` 
- 项目 $\to$ 属性 $\to$ 配置属性：高级 $\to$ 项目默认属性：字符集 $\to$ 使用多字节字符集

### 四、图片处理函数

使用图形时需要easyx提供给我们的类型IMAGE，例如：IMAGE img；

``` c++
/* 从文件中读取图像
pDsitimg：保存图像的指针
pImgFile；图片名称
width：宽
height：高
resize：是否调整图片大小
*/
loadimage(IMAGE* pDstimg, LPCTSTR plmgFile, int width=0, int height=0, bool Resize=false);


/* 在当前设备上绘制指定图像
x: x坐标
y：y坐标
pSrcimg：IMAGE对象指针
dwRop：SRCCOPY 三元光栅栏操作码
*/
putimage(int x, int y, IMAGE *psrcimg, DWORD dwRop=SRCCOPY);

/* 样例 */
// 定义一个图片
IMAGE img;
// 加载图片
loadimage(&img, "./imag/i.png", 100, 100);
putimage(0,0, &img);
```

### 五、批量绘图

单独使用loadimage、putimage等函数，会出现闪屏

``` c++
/* 双缓冲绘图，需要放在绘图代码之前和之后 
EndBatchDraw()和FlushBatchDraw()效果相同，建议使用FlushBatchDraw();
*/
BeginBatchDraw();
// ---这里添加绘图代码
EndBatchDraw();
FlushBatchDraw();
```

## 鼠标操作

``` c++
// 鼠标是一个结构体
ExMessage msg;

if (peekmessage(&msg, EM_MOUSE)) {
    // 如果有鼠标消息
    switch (msg.message){
        // WM_LBUTTONDOWN：单击事件
        case WM_LBUTTONDOWN:
            if (msg.x >=50 &&msg.y<=50){
                printf("点击成功")
            }
            break;
        // 右键
        case WM_RBUTTONDOWN: break;
    }
}
```

## 键盘操作

```  c++
/* 获取鼠标消息、一*/
#include <conio.h>
getch();
// 例子
while(1){
    // 阻塞方法
    char key = _getch();
}

/* 获取键盘消息、二
常用键值
VK_UP:上
VK_DOWN:下
VK_LEFT:左
VK_RIGHT:右
*/
GetAsyncKeyState(键值);
if(GetAsyncKeyState(VK_UP)) {
    // 按下 上键 的动作
}
```

## 播放音乐

``` c++
#include <easyx.h>
#include <mmsystem.h>
// 加载静态库，预编译
#pragma comment(lib, "winmm.lib")
// 打开音乐./xxxx.mp3,并重命名为BGM
// 参数2：接收信息的缓冲区，NULL为不反回信息
mciSendString(L"open ./xxxx.mp3 alias BGM", NULL, 0, NULL);
mciSendString(L"play BGM", NULL, 0, NULL);
// 重复播放
mciSendString(L"play BGM repeat", NULL, 0, NULL);
```

## 修改窗体

``` c++
// 获取窗体句柄
GetHWnd();
// 样例
HWND hwnd = GetHWnd();
SetWindowText(hwnd, "名称");
MessageBox(hwnd, L"消息框内容", L"标题", MB_OK);
// 点击了OK
int isok = MessageBox(hwnd, L"消息框内容", L"标题", MB_OK);
if(isok == IDOK){}
```

