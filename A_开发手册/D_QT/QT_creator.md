# QT/QT_create

1. 支持平台windows、Unix/X11、MAC OS 、Embedded

## 环境配置

1. 下载QT 开源版本：[Download Qt OSS: Get Qt Online Installer](https://www.qt.io/download-qt-installer-oss)
2. 

## 打包发布

### 一、exe软件发布

1. 修改 debug 模式到 Release 模式
2.  编译运行
3. 找到Release目录下的exe文件
4. 复制到新文件夹 
5. 在文件夹下运行 `windeployqt **.exe` （windeploypt是qt自带的软件，要运行它）

windeployqt也可以通过菜单的qt $\to$ qt(MinGW)命令行直接启动（注意编译套件的版本与windeployqt的版本对应，若不对应程序无法运行，使用什么软件编译的就用什么处理）

### 二、hm nis edit（第三方打包）

### 三、安卓发布及配置

#### Ⅰ、配置环境

1. QT creater界面找到“工具”
2. QT Maintenace Tool$\to$ Start Maintenace Tool
3. 登陆$\to$添加或修改组件$\to$找到Android
4. QT creater$\to$工具$\to$外部$\to$配置
5. 选中“设备”$\to$ “Android”

#### Ⅱ、发布

## 基本功能

### 一、新建项目说明

带GUI项目创建：New Project 新建工程 $\to$ Projects $\to$ Application(Qt)

- Qt widgets Applicaion：空窗口项目
- Qt Console Application：命令行项目
- Qt Quick Application：快速创建项目

基类选择（Class Information）：Base class下拉选项（根据需求选择）

- QWidget -- 空窗口
- QMainWindow-- 提供工具栏、状态栏、侧边栏
- QDialog -- 对话框

###  二、GUI程序设计基础

#### 1、文件说明

- .pro文件：qmake构建系统的项目配置文件，存储各种项目配置

- .txt文件：CMake文件

- main.cpp：主程序入口文件

  ``` c++
  #include "widget.h"
  #include <QApplication>
  int main(int argc char* argv[]){
      // 创建应用程序
      QApplication a(argc, argv);
      // 创建窗口
      Widget w;
      // 显示窗口
      w.show();
      // 应用程序运行，开始消息循环和事件处理
      return a.exec();
  }
  ```

- widget.ui：使用XML格式描述元件及布局的界面

- widget.h：窗口类定义的头文件，使用了.ui文件

  ``` c++
  // 防止头文件重复引用
  #ifndef WIDGET_H
  #define WIDGET_H
  // 窗口类Qwidget
  #include <QWidget>
  // 命名空间
  QT_BEGIN_NAMESPACE
  namespace Ui { class Widget; }
  QT_END_NAMESPACE
  
  class Widget : public QWidget{
      // QT定义的宏，允许使用类中的信号和槽机制
      Q_OBJECT
  public:
      // 构造函数
      Widget(QWidget *parent = nullptr);
      // 析构函数
      ~Widget();
  
  private:
      Ui::Widget *ui;
  };
  
  #endif // WIDGET_H
  ```

- widget.cpp：实现文件

  ```c++
  #include "widget.h"
  // GUI文件
  #include "./ui_widget.h"
  
  Widget::Widget(QWidget *parent)
      // 初始化列表语法
      // 将parent赋值给Qwidget，新建对象ui::widget赋值给UI
      : QWidget(parent), ui(new Ui::Widget) {
      // 初始化ui类
      ui->setupUi(this);
      // 这里可以添加功能，初始按钮等操作
  	QPushButton *btn = new QPushButton;
  }
  
  Widget::~Widget() {
      delete ui;
  }

- ui_widget.h：根据组件信号自动生成

#### 2、项目管理-pro文件

建议使用CMake方式（CMakeLists.txt）

#### 3、UI窗体属性

QObject $\to$ QWidget $\to$ QFrame $\to$ QLabel 

#### 4、自动生成函数方法

右键控件 $\to$ go to slot（转到槽） $\to$ 选择对应的事件 $\to$ 完成

#### 5、坐标

qt的坐标在屏幕的左上角（0，0）；x以右为正方向，y以下为正方向

#### 6、UI控件名称

所有通过UI添加的控件他们都有一个属性 QObject $\to$ objectName，objectname是当前点击的控件名称（`ui->控件名称` ）

#### 7、ui发送关闭信号

屏幕下方Signals and Slots Editor $\to$ ➕ $\to$ 选择发送者，指向事件

<img src="assets/QT_creator/113549.png" style="zoom:55%;" /> <img src="assets/QT_creator/113615.png" style="zoom:55%;" />

### 三、添加资源文件

#### 1、加载资源

1. 应先将资源文件复制到项目类
2. 创建资源文件夹：功能栏File  $\to$ New File... $\to$ Files and Classes中的Qt $\to$ Qt Resource File
3. 添加资源文件：Projects栏 $\to$ Resources文件夹 $\to$ 找到.qrc文件 $\to$ 右键.qrc文件，open in Editor $\to$ add Files（添加前缀用于资源分类）
4. 在Cmake.txt中添加资源文件
5. 使用资源：`QIcon(":/资源文件位置")` 

**提醒信息：File are not auto matically added to the CMakeList.txt file of the CMake project. copy the path to the source files  to the clipboard** 

找到后添加自己的文件

``` c++
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        dialog.h     //这是后来添加的对话框文件
        dialog.cpp  //
        dialog.ui    //
)
```

#### 2、加载字体

使用加载字体时，有些控件字体可能需要单独设置

``` c++
// 设置全局字体
QFontDatabase::addApplicationFont(":/test.ttf");
/* 获取字体名称 */
int f = QFontDatabase::addApplicationFont(":x.ttf");
QString font_name = QFontDatabase::applicationFontFamilies(f).at(0);

/* 根据字体名称设置字体 */
QFont font(font_name, 字号，权重);
// 给指定控件设置字体
ui->控件名->setFont(font);

/* 另一种设置 */
QFont font;
// 设置字号
font.setPointSize(12);
// 设置字体
font.setFamily("KaiTi");
// 给指定控件设置字体
ui->控件名->setFont(font);
```

#### 3、加载ico文件-cmake

1、创建ico文件：[在线制作ico图标 | 在线ico图标转换工具 方便制作favicon.ico - 比特虫 - Bitbug.net](https://www.bitbug.net/) 生成 `logo.ico`文件，

2、将logo.ico文件放到cmakeLists.txt同级目录下

**无法显示的ico文件会**出现 `ninja: build stopped: subcommand failed.` 错误

3、创建 `.rc` 文件：在 `cmakeLists.txt` 同级目录创建 `.txt` 文件并改名为 `logo.rc` 

4、修改`logo.rc` 文件

``` cmake
IDI_ICON1 ICON DISCARDABLE "logo.ico"
```

5、修改cmakeList.txt文件

``` cmake
# 第一步
# ${CMAKE_CURRENT_SOURCE_DIR}：cmakeList所在的位置
# 设置app_icon变量
set(app_icon "${CMAKE_CURRENT_SOURCE_DIR}/logo.rc")

# 第二步
# 找到qt_add_executable项添加${app_icon}
# 例子：
qt_add_executable(Qt_app_tomato_cpp
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${app_icon} # 添加项
)
```

### 四、对象树

- 简单来讲，当使用qt创建对象时都是继承QObject对象（例：QWidget,QMainWindow,），子类创建对象时会在QObject中自动维护一个children列表，当窗口释放时，会自动释放

### 新建项目大量警告

- Help $\to$ About Plugins $\to$ C++ $\to$ ClangCodeModel 将其勾选掉

## 不同UI之间传值

### 一、信号槽传值

信号发出者：定义一个信号

``` c++
class Dialog{
signals:
    void send(int);
}
```

信号发出者：定义一个发出信号的槽函数

``` c++
class Dialog{
private slots:
    // 这个槽函数是dialog页面中的button等控件调用
    void emit_sign();
}

// 这个函数发出信号
Dialog::emit_sign(){
    emit send(11);
}
```

信号接收者：定义一个槽函数用来处理信号

``` c++
class Dialog_main{
private slots:
    void show();
}
```

连接信号与槽

``` c++
// 要导入UI头文件
#include "Dialog"
// 显示Dialog窗口
Dialog *d = new Dialog;
d->show();
// 将信号连接
connect(d, &Dialog::send, this, &Dialog_main::show);
```

### 二、public函数传值

### 三、静态变量传值



## 信号

1. 使用观察者模式实现，`connect` 必须继承`QObject` 
2. ``connect(信号发送者，发送的信号，信号的接收者，处理的槽函数 )` 

### 一、系统槽（处理方法）

``` c++
// 退出方法 
&Qwidget::close
```

### 二、信号槽

- 槽：处理方法，信号的回调函数

#### 1、使用系统槽

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    
    // 创建一个按钮，这个按钮触发一个信号
	QPushButton *btn = new QPushButton;
	/* 
	参数列表：信号发送者，发送的信号，信号的接收者，处理的槽函数 
	功能说明：给btn按钮绑定一个信号（clicked单击信号），当点击时触发关闭方法
	&Qwidget::close：系统提供关闭程序的处理方法
	*/ 
	connect(btn, &QPushButton::clicked, this，&Qwidget::close);
}
```

#### 2、连接自定义槽

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    // 创建一个按钮、触发方法
	QPushButton *btn = new QPushButton;
	
    /* 方法一 */
    // classOver是自己定义的
    // 触发自己写的函数
	connect(btn, &QPushButton::clicked, this，&widget::classOver);
    
    /* 方法二、Lambda表达式 */
	// []:表示lambda的开始,
	connect(btn, &Mybutten::clicked, [=](){ 
        // 这里直接写处理方法 
    })
}

/* 方法一的触发方法 */
void widget::classOver() {
    cout << "触发";
}
```

#### 3、断开信号与槽的连接

``` c++
// 创建一个按钮
QPushButton *btn = new QPushButton;

// 触发自己写的函数
disconnect(btn, &QPushButton::clicked, this，&widget::classOver);
```

### 三、自定义信号触发自定义方法

#### 1、创建自定义信号

``` c++
/* 继承的类可以是Qwidget类， */
class Teach: public QObject {

/* 
1、自定义信号必须在 signals
2、返回类型必须时 void
3、信号只需要声明，不用实现
4、信号可以有参数，可以重载
*/
signals:
	void hungry();
}
```

#### 2、创建槽函数

``` c++
/* 声明 */
class Student : public QObject
{
public:
    // 早期槽函数只能放到public slots中，现在直接放到public中即可
    // 返回值必须是void
    void treat();
};

/* 实现 */
void student::treat() {
    cout << "xxx";
}
```

#### 3、信号连接

``` c++
// 引入自定义的槽和信号
#include "student.h"
#include "Teacher.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) 
{
    Teacher *zt = new Teacher(this);
    student *st = new student(this);
    // 将信号连接，zt的hungry信号触发st中的treat方法
    connect(zt, &Teacher::hungry, st, &student::treat);
    
    // 调用hungry函数, 即可触发信号
    // emit 触发信号
    emit zt->hungry();
}
```

### 四、自定义信号传参

1、创建有参数信号

``` c++
/* 继承的类可以是Qwidget类， */
class Teach: public QObject {
signals:
	void hungry(int foodName);
}
```

2、槽函数

``` c++
/* 声明 */
class Student : public QObject{
public:
    void treat(int foodName);
};

/* 实现 */
void student::treat(int foodName) {
    cout << foodName;
}
```

3、连接没有重载的信号

``` c++
// 引入自定义的槽和信号
#include "student.h"
#include "Teacher.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    Teacher *zt = new Teacher(this);
    student *st = new student(this);
    
    // 将信号连接
   	connect(zt, &Teacher::hungry, st, &student::treat);
    
    // 调用hungry函数, 即可触发信号
    // emit 触发信号,携带参数
    emit zt->hungry("xxxxx");
}
```

4、重载的信号

``` c++
// 引入自定义的槽和信号
#include "student.h"
#include "Teacher.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    Teacher *zt = new Teacher(this);
    student *st = new student(this);
    
    // 重载带参的函数
    void(Teacher::*th_info)(int) = &Teacher::hunqry;
    void(Teacher::*st_info)(int) = &Teacher::hunqry
    // 将信号连接
    connect(zt,th_info, st, st_info);
    
    // 调用hungry函数, 即可触发信号
    // emit 触发信号,携带参数
    emit zt->hungry("xxxxx");
}
            
```

### 五、信号连接信号

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    Teacher *zt = new Teacher(this);
    
    // 重载带参的函数
    void(Teacher::*th_info)(int) = &Teacher::hunqry;
    // 将信号连接
    connect(btn, &QPushButton::clicked, zt, th_info);
    
    // 调用hungry函数, 即可触发信号
    // emit 触发信号,携带参数
    emit zt->hungry("xxxxx");
}
```

## 代码生成

带有菜单栏（menu bar）、任务栏（tool bars）、铆接部件（dock widgets）、状态栏（status bar）、中心部件（central widget）的主窗口程序类，是许多应用程序的基础

### 一、菜单栏

``` c++
// 菜单栏头文件
#include <QMenuBar>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 创建菜单栏，只能有1个
    QMenuBar *bar = menuBar();
    // 将菜单栏设置到窗口中
	this->setMenuBar(bar);
    // 添加菜单项，没有菜单项，菜单栏不会显示
    QMenu *fileMenu = bar ->addMenu("文件");
    QMenu *editMenu = bar ->addMenu("编辑");
    // 为文件菜单项添加内容
    QAction *NewAction = fileMenu->addAction("新建");
    // 添加分割线
    fileMenu->addSwparator();
    
    /* 添加子菜单 */ 
    QMenu *subMenu = New Qmenu;
    subMenu->addAction("zcid");
    // 挂载到新建菜单下
    newAction->setMenu(subMenu);
}
```

### 二、工具栏

``` c++
// 菜单栏头文件
#include <QToolBar>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 工具栏可以有多个
    // this指定依附的对象，亦可以省略
    QToolBar *toolBar = new QToolBar(this);  
    
    /* 添加工具栏到窗口 */ 
    addToolBar(toolBar);
    // 设置添加位置,其他位置查看手册
    addToolBar(Qt::LeftToolBarArea, toolBar);
    // 只允许在左停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea);
    // 设置禁止浮动
    toolBar->setFloatable(false);
    // 设置禁止移动
    toolBar->setMovable(false);
    
    /* 添加菜单项 */ 
    // 准备菜单
    QMenuBar *bar = menuBar();
    QMenu *fileMenu = bar->addMenu("文件");
    // 添加菜单到工具栏
    toolBar->addAction(fileMenu);
    
}
```

### 三、状态栏

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 状态栏只能有1个，
    // QStatusBar可以直接创建
    QStatusBar * stBar = new statusBar();
    // 将状态栏添加到页面
    setStatusBar(stBar);
    
    /* 给状态栏添加信息 */ 
    // 标签头文件
	#include <QLabel>
    // 创建标签
    QLabel *label = new QLabel("提示信息", this);
    // 将标签添加到状态栏，左侧
    stBar->addWidget(label);
    /* 添加右侧信息 */
    QLabel *labe12 = new QLabel("右侧提示信息", this);
    stBar->addPermanentWidget(labe12);
    
    /* 插入信息 */
    QLabel *labe4 = new QLabel("插入提示信息", this);
    // 0 是标注位置，
    stBar->insertWidget(0,labe12);
}
```

### 四、铆接（浮动窗口）

``` c++
// 头文件
#include <QDockWidget>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 创建铆接对象
    QDockWidget *dock = new QDockWidget;
    // 将铆接到窗口
    // Qt::BottomDockWidgetArea：底部，更多位置查看手册
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    // 设置只允许下方设置
    dock->setAllowedAreas(Qt::BottomDockWidgetArea)
    
    /* 核心部件 */
    // 核心部件只能有1个，铆接位置根据中心部件确定
    #include <QTextEdit>
    QTextEdit *edit = new QTextEdit(this);
    setCentralWidget(edit);
}
```

### 五、托盘栏程序

简单使用

``` c++
#include <QMenu>

/* 创建菜单 */ 
QMenu *menu = new QMenu(this);
// 创建菜单相
QAction *serial = new QAction(QString("串口选择"), this);
// 退出功能
QAction *out = new QAction(QString("退出"), this);
// 创建带图标的功能
//QAction *serial = new QAction(QIcon(":/res/aaa.jpg"), QString("串口选择"), this);
menu->addAction(serial);
menu->addSeparator();//添加分割线
menu->addAction(out);

/* 创建系统托盘 */
m_systemtrayi = new QSystemTrayIcon(this);
// 设置图标,资源文件不对无法显示
m_systemtrayi->setIcon(QIcon("://res/aaa.jpg"));
// 设置托盘提示信息
m_systemtrayi->setToolTip(QString("键盘串口"));
// 设置托盘菜单
m_systemtrayi->setContextMenu(menu);
// 显示托盘
m_systemtrayi->show();

/* 信号-退出 */ 
// out是QAction
// QAction::triggered是点击事件
connect(out, &QAction::triggered, this, &QApplication::quit);
```

二级菜单多选使用

``` c++
// 托盘菜单（主菜单）
QMenu *menu = new QMenu(this);
// 创建二级菜单
QMenu *serial = new QMenu(QString("串口选择"), this);
// 创建二级菜单的选项
QAction *serial_on = new QAction(QString("开启"), this);
// 主菜单添加二级菜单
menu->addMenu(serial);
// 二级菜单社会选项
serial->addAction(serial_on);

// 设置二级菜单项可选
serial->setCheckable(true);
// 设置二级菜单项选中
serial->setChecked(true);
// 设置没有选中不选中
serial->setChecked(false);
```

二级菜单单选使用

``` c++
// 创建主菜单
QMenu *menu = new QMenu(this);
// 创建二级菜单
QMenu *serial = new QMenu(QString("串口选择"), this);
// 创建二级菜单项
QAction *serial_on = new QAction(QString("开启"), this);
QAction *serial_off = new QAction(QString("关闭"), this);

// 重要：创建团组
QActionGroup * serial_group  = new QActionGroup(this);
// 设置团组
serial_group->addAction(serial_on);
serial_group->addAction(serial_off);

// 设置选项状态
serial_on->setCheckable(true);
serial_off->setCheckable(true);
serial_off->setChecked(true);
// 正常添加二级菜单
menu->addMenu(serial);
serial->addAction(serial_on);
serial->addAction(serial_off);
```

## 对话框

对话框分为：模态对话框（弹出后不可对其他位置操作），非模态对话框（可以对其他窗口操作）

### 一、模态对话框

``` c++
#include <QDialog>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    ui->setupUi(this);
    
    // 创建模态对话框
    QDialog dlg(this);
    dlg.exec();
    // 重置模态框大小
    dlg.resize(117, 31);
}
```

### 二、非模态对话框

``` c++
#include <QDialog>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    ui->setupUi(this);
    
    // 创建非模态
    // 创建模态对话框
    QDialog *dlg = new QDialog(this);
    dlg->show();
    // 重置模态框大小
    dlg->resize(117, 31);
    // 设置属性，结束后释放内存，查看手册
    dlg->setAttribute(Qt::WA_DeleteOnClose);
}
```

### 三、弹出对话框

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    ui->setupUi(this);
    
    /* UI控件发出信号 */
    // &QAction::triggered：触发动作，triggered类似于click
    connect(ui->控件名称, &QAction::triggered, [=](){
        // lambda表达式触发
    });
    // 触发自定义的方法处理
    connect((ui->控件名称, &QAction::triggered, this, &widget::myclick);
}
            
void Widget::myclick() {
    cout << 自定义的方法;
}
```

### 四、消息对话框

警告、错误等提醒对话框

``` c++
#include <QMessageBox>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    ui->setupUi(this);
    
   	/* 消息对话框是静态属性，可以直接使用（不用New） */ 
    // 错误提示
    int k = QMessageBox::critical(this, "标题", "内容");
    // 消息提示
    int k=QMessageBox::information(this, "标题", "内容");
    // 警告提示
    int k=QMessageBox::warning(this, "标题", "内容");
    
    /* 询问提示, 带有yes，no按钮 */ 
    // 参数4：
    // 	QMessageBox::Save：保存按钮，更多按钮查看手册
    // 参数5：
    // 	默认选项,QMessageBox::Save默认点击保存
    int k = QMessageBox::question(this, "标题", "内容", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save);
    // 判断当前选择
    if (QMessageBox::Save == k){}
}
```

### 五、颜色对话框

``` c++
#include <QColorDialog>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    QColor color = QColorDialog::getColor();
    // 设置默认色彩
    QColor color = QColorDialog::getColor(QColor(255,233,200));
    // 打印选中颜色
    cont << color.red();
    cont << color.green();
    cont << color.blue();
}
```

### 六、字体对话框

``` c++
#include <QFontDialog>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    bool ok;
    QFont Qfont = QFontDialog::getFont(&ok, QFont("华文彩云", 字号));
    // 结果
    cont << Qfont.family();
    cont << Qfont.pointSize();
    cont << Qfont.bold();
    cont << Qfont.italic();
}
```

### 七、文件对话框

``` c++
#include <QFileDialog>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 只能查看.txt文件
    QString path = QFileDialog::getOpenFileName(this, "标题", "默认打开目录", "*.txt");
    // 用户打开的目录
    qDebug() << path;
}
```

## UI Design

### 注意

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    // 1、这个方法必须在最上方
    // 2、所有通过图形界面添加的控件都属于ui类
    ui->setupUi(this);
}
```

### 一、窗口属性

必须在qt的Qwidget、Qdigt、QMainWindow等类中使用

#### 1、修改窗体属性

- Qt::MSWindowFiredSizeDialogHint: 为Windows系统上的窗口装饰一个窄的对话框边框，通常这个提示用于固定大小的对话框
- Qt::MSWindowOwnDC: 为Windows系统上的窗口添加自身的显示上下文菜单
- Qt::X11BypassWindowManagerHint: 完全忽视窗口管理器，它的作用是产生一个根本不被管理的无窗口边框的窗口(此时，用户无法使用键盘进行输入，除非手动调用QWidget::activateWindow()函数)
- Qt::FramelessWindowHint: 产生一个无窗口边框的窗口，此时用户无法移动该窗口和改变它的大小
- Qt::CustomizeWindowHint：关闭默认的窗口标题提示
- Qt::WindowTitleHint：为窗口装饰一个标题栏
- Qt::WindowSystemMenuHint:为窗口添加一个窗口系统系统菜单，并尽可能地添加一个关闭按钮
- Qt::WindowMinimizeButtonHint:为窗口添加一个“最小化”按钮
- Qt::WindowMaximizeButtonHint:为窗口添加一个“最大化”按钮
- Qt::WindowMinMaxButtonHint:为窗口添加一个“最小化”按钮 和一个“最大化”按钮
- Qt::WindowContextHelpButtonHint: 为窗口添加一个“上下文帮助”按钮
- Qt::WindowStaysOnTopHint: 置顶窗口
- Qt::WindowType_Mask:  一个用于提示窗口标识的窗口类型部分的掩码

``` c++
// 设置窗体名称
setWindowTitle(“sss”)

// 窗体图标
setWindowIcon(QPixmap(“:/images/t.png”))

// 固定大小窗体大小
setFixedSize(400, 300)

// 设置当前窗体大小，当前代码所在的窗体**
this->resize(600,400);
resize(600, 400);

// 设置无边框
this->setWindowFlag(Qt::FramelessWindowHint);
/*

*/
```

#### 2、设置图标

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 初始化ui类 */
    ui->setupUi(this);
    
    /* 通过UI名设置图标 */
    ui->控件名称->setIcon(QIcon(":/image/luffy.png"));
}
```

#### 3、窗体根据鼠标移动

``` c++
// widget类的父类有响应的方法
//获取：窗口基于屏幕的位置，左上角位置
QPoint pt = this->pos();
//获取当前点位于屏幕坐标的点
QPoint pt0 = this->cursor().pos();
//屏幕坐标点 --> 成当前窗口坐标点
QPoint pt1 = this->mapFromGlobal(pt0);
//窗口上坐标点 -- >屏幕坐标
QPoint pt2 = this->mapToGlobal(pt1);
//当前窗口坐标 -- > 成屏幕坐标
QPoint pt3 = this->mapToParent(pt1);
//屏幕坐标 -- >窗口坐标
QPoint pt4 = this->mapFromParent(pt0);
```

操作样例

``` c++
/* 1、获取鼠标位置 */
class Widget: public widget {
private:
    // 鼠标与左三角的偏移量
    QPoint mOffset;
protected:
	// 获取鼠标当前位置
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
}

/* 实现鼠标方法 */
void widget::mousePressEvent(QMouseEvent *event) {
    // 计算偏移量
    // globalPos鼠标相对于左上角的点位置
    // event->pos() == this->pos();
    mOffset = event->globalPos() - this->pos();
}
void widget::mouseMoveEvent(QMouseEvent *event) {
    // 
    this->move(event->globalPos() - mOffset);
}
```

### 二、QPushButton-按钮

1、头文件：`#include <QPushButton>`

2、创建按钮

``` c++
/* 第一种方法 */ 
QPushButton *btn = new QPushButton;

/*第二种方法*/
// 按照窗体创建按钮
QPushButton *btn = new QPushButton(“按钮名称”, this)
```

3、功能

``` c++
QPushButton *btn = new QPushButton;

/* 设置按钮文件 */
btn->setText(“按钮名称”);
/* 移动 */
btn->move(100, 100);
/* 调整大小 */
btn->resive(50,50);
/*覆盖样式*/
btn->setStyleSheet("background:#fff");
/* 不可点击 */
btn->seEnabled(true);

/* 显示到窗体哪个位置 */
// 顶层弹出，单独一个窗口
btn->show();      
// 显示在当前窗体，this是当前的类
btn->setParent(this) 
// 向布局Layout中添加
ui->vLayout->addWidget(btn) 
```

4、支持的信号

``` c++
// 点击
&QPushButton::clicked 
```

### 三、Tool Button

功能与QPushButton相同，主要用于显示图片

其属性 autoRaise 是透明效果

 ### 四、Radio Button

``` c++
// 默认选中
ui->控件名->setChecked(true);

// 监听用户选中
connect(ui->控件名， &QRadioButton::clicked, [=](){
    选中状态
})
```

### 五、CheckBox

``` c++
// 默认选中
ui->控件名->setChecked(true);

// 监听用户选中
connect(ui->控件名， &QCheckBox::stateChanged, [=](int state){
    //选中状态
})
```

### 六、list_widget（ItemBase）

基于用户自定义数据，用于展示列表数据

#### 1、生成添加数据

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    /* 创建控件 */
    // listwidget每一行都是一个item
    QListWidgetItem *item = new QListWidgetItem("锄禾日当午");
    // 设置对齐方式
    item->setTextAlignment(Qt::AlignHCenter);
    // 将数据添加进ui的指定的QList控件中
    ui->控件名称->addItem(item);
    
    /* 添加多条数据 */
    // 必须使用QStringList类型
    QStringList list;
    // 2中添加数据形式,不能设置居中
    list.push_back("xxx");
    list << "xxxx" << "cccc";
    ui->控件名称->addItem(list);
}
```

#### 2、单击事件

``` c++
// 槽函数声明
class Widget : public QWidget{
    // QT定义的宏，允许使用类中的信号和槽机制
    Q_OBJECT
public:
private:
public:
    // 单击事件
    void onItemClicked(QListWidgetItem *item);
    // 双击事件
    void onItemDoubleClicked(QListWidgetItem *item);
};

/* 建立连接 */
// 控件是整个QListWidget
connect(ui->控件名称, &QListWidget::itemclicked, this, &Widget::onItemClicked);
connect(ui->控件名称, &QListWidget::itemDoubleclicked, this, &Widget::onItemClicked);

/* 被触发函数 */
void onItemClicked(QListWidgetItem *item){
    // 获取当前点击的文本
    item->text();
    
}
```

#### 3、ListWidget效果集合

``` c++
// 设置无边框
ui->控件名称->setFrameShape(QListWidget::NoFrame);

```

### 七、tree_widget（ItemBase）

可展开的列表，有斜三角符号的列表

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 生成数据
    QStringList list;
    list << "英雄" << "x";
    // 创建tree控件头部
 	ui->控件名称->setHeaderLabels(list);
    // 生成tree内部数据，使用匿名对象
    QTreWidgetItem *liItem = new QTreeWidgetItem(QStringList() << "xxx");
    // 将数据添加进UI
    ui->控件名称->addTopLevelTiem(liItem);
    
    // 创建子列表
    QTreWidgetItem *otherItem = new QTreeWidgetItem(QStringList() << "子列表");
    // 将子列表添加到liItem项下
    liTtem->addChild(otherItem);
}
```

### 八、table_widget（ItemBase）

带有横线、竖线的普通表格

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
    // 创建表头数据
    QStringList list;
    list << "xx" << "www" << "aaa";
    // 告诉tablewidget有几列
    ui->控件名称->setColumnCount(list.size());
    // 设置表格头数据
    ui->控件名称->setHorizontalHeaderLabels(list);
    // 设置行数
    ui->控件名称->setRowCount(5);
    // 向表格中添加内容,QTableWidgetItem只能用QString类型
    ui->控件名称->setItem(行, 例, new QTableWidgetItem("数据"));
    
    /* 循环添加 */ 
    QStringList Name;
    Name << "xxx " << "sdfdf" << "sdf";
    for (int i=0; i<5; i++){
        int cot = 0;
        ui->控件名称->setItem(i, col++, new QTableWidgetItem(Name[i]));
    }
    
    /* table查找元素 */
    // isEmpty()：返回true，false
    // Qt::MatchExactly：匹配方式，向前查看手册
    bool em = ui->控件名称->findItem("查找的元素名",Qt::MatchExactly).isEmpty();
    
    /* 删除元素 */
    // .first()：查找元素第一次匹配的位置
    // .row()：返回行号
    int rownum = ui->控件名称->findItem("查找的元素名",Qt::MatchExactly).first()->row();
    // 根据行号删除元素
    ui->控件名称->removeRow(rownum);
    
    // 将int 转换为QString
    QString::number(18+i);
}
```

### 九、stacked Widget

``` c++
// 设置默认页
ui->控件名称->setCurrentIndex(0);

/* 实现栈切换功能 */
// statckedWidget必须使用button按钮操作他的页面切换
connect(ui->控件名称, &QPushButton::clicked, [=](){
    ui->控件名称->setCurrentIndex(1);
})
```

### 十、comboBox-下拉框

``` c++
/* 给下拉框添加内容 */
ui->控件名称->addItem("选项1");
ui->控件名称->addItem("选项2");

/* 点击按钮，修改下拉框显示内容 */
connect(ui->控件名称, &QPushButton::clicked, [=](){
    ui->控件名称->setCurrentText("xxx");
})

```

### 十一、QLineEdit-输入框

密码不显示设置：design界面 $\to$ QLineEdit $\to$ echoMode

- NoEcho：什么都不显示
- Password：显示圆圈
- PasswordEchoOnEdit：输入时显示，焦点切换后显示圆圈

### 十二、Text Edit与Plain TextEdit

文本输入框，Text Edit带有文本样式，Plain TextEdit不带样式

``` c++
//输入框内简单文本， QString
ui->QTextEdit/QPlainTextEdit ->toPlainText() ;
//带有样式的内容
ui->QTextEdit->toHtml() ;

// 清空输入框
ui->text->clear();
// 返回光标
ui->text->setFocus() ;
```

### 十三、Qlabel-标签

``` c++
/* 显示图片 */ 
ui->控件名称->setPixmap(QPixmap(":/image/u.png"));
// 设置图片宽高
QPixmap pix;
pix.load(":/image/u.png");
ui->控件名称->setPixmap(pix);
ui->控件名称->setFixedSize(pix.width(), pix.height());

/* 显示Gif图片 */ 
QMovie *movie = new QMove(":/Image/o.gif");
ui->控件名称->setMovie(movie);
// 播放
movie->start();
// 设置速度
movie->setSpeed(300);
// 播放完停止
connect(movie, &QMovie::frameChanged, [=](int frameId){
    if(frameId == movie->frameCount()-1){
        movie->stop();
    }
});

/* 显示文本 */
label->setText("xxxx");
    
```

### 十四、QSlider-滑块

常用信号：

- `QSlider::valueChanged` ：滑块数字改变时发出信号
- `QSlider::sliderMoved` ：滑块移动时发出信号，不能准确的获取滑块的值

常用方法：

``` c++
QSlider *p = new QSlider;

/* 常用方法 */
// 设置最大值
p->setMaximum(int);
// 设置最小值
p->setMinimum(int);
// 设置当前值
p->setValue(int);
// 获取当前值
int i = p->value();
```

### 十五、封装控件

1、右键项目 $\to$ 添加新文件 $\to$ 选中模板：Qt $\to$ Qt设计师界面类（<img src="assets/QT_creator/124348.png" style="zoom:45%;" />）

2、选择Widget（空的界面）$\to$ 下一步，完成 $\to$ 在设计页面中组合控件

3、在其他页面添加自定义封装的控件，

- 添加Widget控件

- 在widget控件上右键 $\to$ 提升为... （<img src="assets/QT_creator/124912.png" style="zoom:45%;" />）

- 设置属性

  <img src="assets/QT_creator/125332.png" style="zoom:55%;" />

4、点击添加 $\to$ 提升（设计时没有效果，运行时有效果）

## QT内置对象

### 一、数据类型

为了统一不同平台相同类型的大小统一而定义的类型

### 二、QPixmap -用于加载图片

``` c++
QPixmap(“:/images/time.png”);
btn->setIcon(QPixmap(“:/image/time.png”));
```

### 三、容器

#### 1、QVector 

QVector在6.2版本后与QList合并，查看QList

#### 2、QList

``` c++
#include <Qlist>

// 存放QString类型的Qlist容器
QList<QString> namelist; //QList类型数组
// 添加数据
nameList << “sss” << “添加数据”;
nameList.back_push("ssss");
// 使用
nameList[1]; 

/* 可用方法*/
// 获取长度
nameList.lenght();
```

#### 3、QStringList

``` c++
QStringList iconNameList; //字符串数组
iconNameList << “这样添加数据” ;
iconNameList.at(1); 使用数据
```

### 四、数据类型

#### 1、QString

``` c++
QString str //声明

//格式化字符串
QString(“:/images/%1.png”).arg(nameList[1]);

/* 类型转换 */
QString::nemeber(123);
str.toInt() //转数字
str.toUtf8() // 转QByteArray类型
```

#### 2、QByteArray 

``` c++
// 可隐式转换为QString****类型**
QByteArray array = QByteArray(size, 0);

array.toUtf8(); //转QByteArray类型
array.toInt(); // 转换为int
```

### 五、QDebug

``` c++
#include <QDebug>
qDebug() << "sssss";
```

### 六、Socket

``` c++
udp = QudpSocket(this);
udp->bind();
udp->writeDatagram(“wenben”, QHostAddress(192.168..), 111);

// 接收数据
connect(udp, &QUdpSocket::readyRead, [=](){
	qint64 size = udp->pendingDatagramSize();
	QByteArray array = QByteArray(size, 0);
	udp->readDatagram(array.data(), size);
})
```

### 七、HTTP请求

- QT Network是异步工作，不用考虑同步获取信息

#### 基本流程

``` c++
/* 定义槽函数 */
class Widget : public QWidget
{
private slots:
    // 注意，只有槽函数才能用在connect中
    void http_get(QNetworkReply *rep);
};

/* 创建对象 */
QNetworkAccessManager *net = QNetworkAccessManager(this);
// 当请求结束后，net会发射一个finished信号
connect(net, &QNetworkAccessManager::finished, this, &widget::http_get);

/* 创建请求 */
QNetworkRequest request;
request.setUrl(QUrl("http://"));
// 注意：这里net发送请求后会自动触发finished信号，
// 而根据connect方法，将finished信号与http_get联系在一起
net->get(request);
```

#### 1、修改配置文件

- pro文件：`QT += core gui network` 

- cmake文件：
  1. 直接复制：`find_package(Qt6 REQUIRED COMPONENTS Network)` 
  
  2. 在 `target_link_libraries` 中添加 `Qt6::Network` 
  

#### 2、设置信号

``` c++
// 网络请求完成后调用onReplied函数
// QNetworkAccessManager::finished 网络请求完成
connect(netm, &QNetworkAccessManager::finished, this, &widget::onReplied);
void widget::onReplied(QNetworkReply *reply) {}
```

#### 2、GET请求

头文件：

- `#include <QNetWork/QNetworkAccessManager>` 
- `#include <QNetWork/QNetworkReply>`
- `#include <QNetWork/QNetworkRequest>`

创建网络访问管理对象：`QNetworkAccessManager *netm = new QNetworkAccessManager(this);` 

发送请求：

``` c++
/*  方式一 */
#include <QNetworkRequest>
QUrl url("http://");
QNetworkReply * reply = netM->get(QNetworkRequest(url));

/* 方式二（可以方便设置请求头） */ 
#include <QNetworkRequest>
QNetworkRequest request;
request.setUrl(QUrl("http://"));
QNetworkReply * reply = netM->get(request);
```

获取请求返回数据

``` c++
// reply是QNetWorkReply数据

/* 获取响应数据 */  
QByteArray r_data = reply->readAll();

// 请求方式
reply->operation();
// 请求Url 
reply->url();
// 请求头列表
reply->rawHeaderList();

/* 释放内容 */ 
reply->deleteLater();

/* 响应状态码 */ 
int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

/* 判读请求是否成功 */ 
if(reply->error() != QNetworkReply::NoError || status_code != 200) {
    // 请求失败
   QMessageBox::warning(this, "提示", "请求错误", QMessageBox::ok);
} 
```

设置请求头：

``` c++
#include <QNetworkRequest>
QNetworkRequest request;

/* 设置头内容 */
request.setRawHeader("Connection", "keep-alive");
request.setRawHeader("User-Agent", "Client");
```

#### 3、POST请求

``` c++
// 准备json字符串
QJsonObject js;
js.insert("xxx", "sss");
QJsonDocument doc(js);
QByteArray d = doc.toJson();

// 构造请求
QNetworkRqeust request;
request.setUrl(QUrl("http://"));
request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
request.setRawHeader("content-type", "application/json");

// 构造管理类
QNetworkAccessManager *manager = new QNetworkAccessManager(this); 
manager->post(request, d);
```

### 八、Json对象

json数组中元素可以是不同数据类型

- json数组：`[1,2.4,“aa”,4]`
- json对象：`{"key":value, "key2":value}`

#### 1、json对象 / json数组创建

``` c++
/* 创建一个接送对象 */
#include <QJsonObject>
QJsonObject j;

/* 创建json数组 */
#include <QJsonArray>
QJsonArray j_array;

/* jsonDocument */
#include <QJsonDocument>
// 创建一个jsondocument对象
// j是一个jsonObject对象
QJsonDocument doc(j);
// 等价于
QJsonDocument doc;
doc.setObject(json);
```

#### 2、向json对象中添加数据

``` c++
/* 将键值对添加到j */ 
j.insert("name", "xxxx");

/* 将json对象添加进j */
// 创建一个j2对象
QJsonObject j2;
// 将j2添加进j
json.insert("x2", j2);
```

#### 3、json数组添加数据

``` c++
/* 向json数组中添加json对象 */
QJsonObject j3;
ja.append(j3);
```

#### 4、jsonDocument

``` c++
QJsonDocument doc(j);
// 将jsonDocument对象转换为json字符串
QByteArray jdoc = doc.tojson();
```

#### 5、json解析

``` c++
/* 1、获取json文本 */
// 可以从网络，本地文件获取
QByteArray bytext = reply->readAll(); 

/* 2、创建jsondocument对象 */ 
// 创建QJsonDocument对象解析bytext
QJsonDocument doc = QJsonDocumnet::fromJson(bytext);
// 判断似乎是json对象
if (!doc.isObject()) {
    qDbug() << "error";
}

// 带有错误信息的error
QJsonParseError err;
QJsonDocument doc = QJsonDocumnet::fromJson(json, &err);
if (err.error != QJsonParseError::NoError) {
    return;
}

/* 3、将jsonDocument转换为json对象 */ 
QJsonObject obj = doc.object();

/* 4、读取json对象 */
// 根据key获取value 
// 注意一定是双引号，单引号是字符
QString info = obj["name"].toString();
QString info = obj.value("key").toString();
// 获取接送所有key
QStringList keys = obj.keys();
// 获取一个指定key
QString key = keys[1];
// 根据key获取value
QJsonValue v = obj.value(key);

/* 根据不同类型解析不同字符 */ 
#include <QJsonValue>
if(v.isBool()){
    v.toBool();
}else if(v.isString()){
    v.toString();
}else if(v.isDouble()){
    v.toInt();
}else if(v.isObject()){
    v.toObject();
}else if(v.isArray()){
    v.toArray();
}
```

### 九、DateTime

头文件：`#include <QDateTime>`

#### 1、获取QDateTime类型

``` c++
// 通过当前时间
QDateTime T = QDateTime::currentDateTime();

// 通过字符串
QString s= "2019-03-31 12:24:36";
QDateTime T = QDateTime::fromString(s, "yyyy-MM-dd hh:mm:ss"); 

// 通过int类型
int ms = 1537537358;
// 秒
QDateTime T = QDateTime::fromSecsSinceEpoch(ms);
// 毫秒
QDateTime T = QDateTime::fromMSecsSinceEpoch(ms);
```

#### 2、常用方法

``` c++
/* QDateTime转Qstring： */
// 2019.03.13 14:47:24:333 周三 
QString S = T.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
QString S = T.toString("yyyy-MM-dd hh:mm:ss");

/* QDateTime转时间戳 */
int date = T.toSecsSinceEpoch();
int date = T.toMSecsSinceEpoch();
```

### 十、QTime

获取QTime中的时分秒

``` c++
// 时间字符串
QString Ts = "01:20:30";
QTime T = QTime::fromString(Ts);
// 获取小时
T.hour();
// 获取分钟
T.minute();
// 获取秒
T.second();
// 总秒数
T.hour()*60*60 + T.minute()*60 +T.second();
```

时间戳转字符串

``` c++
// QTime(0, 0, 0)创建时分秒对象
QString time=QTime(0, 0, 0).addSecs(t).toString(QString::fromLatin1("HH:mm:ss"));
qDebug()<<timer; //输出:"00:01:40"
```

### 十一、QTimer-计时器

``` c++
QTimer t = new QTimer;
//this->time->setInterval(1000);
// 信号，每次QTimer计时结束后调用time_run方法
connect(t, &QTimer::timeout, this, &Dialog::time_run);

void Dialog::time_run(){
    // 开始计时，1000单位是毫秒
    t->start(1000);
    // 结束计时
    t->stop();
}
```

### 十二、音乐播放

Cmake添加：

1. 直接复制：`find_package(Qt6 REQUIRED COMPONENTS Multimedia)` 
2. 在`target_link_libraries`中添加`Qt6::Multimedia` 

#### 1、QSound-最简单

6.2版本以上使用QSoundEffect替代

音频文件应先添加进资源

#### 2、QSoundEffect-提示音

适合提示音、只能播放wav格式音频

``` c++
#include <QSoundEffect>
QSoundEffect *effect=new QSoundEffect;
effect->setSource(QUrl::fromLocalFile("/666.wav"));
effect->setLoopCount(1);  //循环次数
effect->setVolume(0.25f); //音量  0~1之间
effect->play();
```

#### 3、QMediaPlayer-播放器

可以播放音乐mp3、播放wav格式文件

``` c++
#include <QMediaPlayer>
QMediaPlayer *player = new QMediaPlayer;
player->setMedia(QUrl::fromLocalFile(":/666.wav"));
player->setVolume(50); //0~100音量范围,默认是100
player->play();
```

播放mp3格式

``` c++
 #include <QMediaPlayer>
 QMediaPlayer *player = new QMediaPlayer;
 //播放进度的信号提示
 connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

 player->setMedia(QUrl::fromLocalFile(":/owa.mp3"));
 player->setVolume(50); //0~100音量范围,默认是100
 player->play();
```

### 十三、串口操作

1. 串口头文件添加

    操作串口：`#include <QSerialPort>` 

    串口信息：`#include <QSerialPortInfo>`  

2. Cmake添加

    直接复制：`find_package(Qt6 COMPONENTS SerialPort REQUIRED)`
    在 `target_link_libraries` 中添加 `Qt6::SerialPort` 

``` c++
/* 查找可用串口 */
QStringList m_serialList;
foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
{
    QSerialPort serialT;
    serialT.setPort(info);
    if(serialT.open(QIODevice::ReadWrite))
    {
        m_serialList << info.portName();
        // 关闭串口
        serialT.close();
    }
    //
    qDebug()<<"serialPortName:"<<info.portName();
}
// 对串口从小到大排序
std::sort(m_serialList.begin(), m_serialList.end());
// 打印所有串口
//for(int i=0; i<m_serialList.size(); i++){
//    qDebug() << m_serialList[i];
//}

/* 串口连接 */
// 打开串口
m_serialPort = new QSerialPort();
// 设置串口名，应该是选择串口吧
m_serialPort->setPortName(m_serialList[0]);
// 打开串口
m_serialPort->open(QIODevice::ReadWrite);
// 设置波特率
m_serialPort->setBaudRate(QSerialPort::Baud4800);//设置波特率为4800
m_serialPort->setDataBits(QSerialPort::Data8);//设置数据位8
m_serialPort->setParity(QSerialPort::NoParity); //无校验位
m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
m_serialPort->setStopBits(QSerialPort::OneStop);//停止位设置为1

/* 关闭串口 */
m_serialPort->close();
```

### 十四、托盘程序

1. 基于`Qt::widgets` 
2. 需要的其他内 `QMenu` ：用于生成菜单

创建菜单类

``` c++
/* 创建托盘程序类 */
// 创建系统托盘
QSystemTrayIcon *m_systemtrayi = new QSystemTrayIcon(this);
// 设置图标,资源文件不对无法显示(路径正确、cmake中添加资源文件)
m_systemtrayi->setIcon(QIcon("://res/aaa.jpg"));
// 设置托盘提示信息
m_systemtrayi->setToolTip(QString("键盘串口"));
// 设置托盘菜单
m_systemtrayi->setContextMenu(menu);
// 显示托盘
m_systemtrayi->show();

/* 托盘程序的菜单，添加后直接右键图标就可显示 */
// 创建菜单
QMenu *menu = new QMenu(this);
// 创建菜单项
QAction *serial = new QAction(QString("串口选择"), this);
// 创建带图标的菜单项
QAction *serial = new QAction(QIcon("://res/aaa.jpg"), QString("串口选择"), this);
// 添加分割线
menu->addSeparator();
// 给菜单添加菜单项
menu->addAction(serial);
```

触发的事件

- `&QAction::triggered` ：QAction的点击事件

``` c++
/* 创造的菜单
QMenu *menu = new QMenu(this);
QAction *out = new QAction(QString("退出"), this);
*/
// 信号-退出
connect(out, &QAction::triggered, this, &QApplication::quit);
```

## 事件

### 一、鼠标事件

``` c++
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget) {
}
```

### 二、键盘事件

#### Ⅰ、普通键盘事件

1. 引入头文件：`#include <QKeyEvent>` 
2. 重写父类widget中的keyPressEvent函数即可
3. 父类必须调用.show()才可以有效果

``` c++
/* .h文件中的定义 */
#include <QKeyEvent>
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
   	// 重写方法、重点
    void keyPressEvent(QKeyEvent *event);
};

/* .cpp文件 */
// 当键盘按下时会自动调用这个方法
void Widget::keyPressEvent(QKeyEvent* event) {
    qDebug() << event->key();
    // 按键比对
    // Qt::Key_Escape
    // Qt::Key_Return
    // Qt::Key_F1
    // Qt::Key_A
}
```

#### Ⅱ、全局键盘事件

查看文档路径 `whiteZe\自定义or应用or框架\D_C++orQT\全局键盘事件` 

### 三、定时器事件



### 三、事件拦截

## 绘图

## 文件操作

### 一、读取文件信息

``` c++
// 文件对话框
#include <QFileDialog>
// 点击选择文件按钮
connect(ui->控件名称, &QPushButton::clicked, [=](){
    // 弹出文件对话框，选择文件
    QString path = QFileDialog::getOpenFileName(this, "打开文件", "默认路径");
    if(path.isEmpty()){
        // 没有选择文件，设置默认路径为C:/
    	ui->控件名称->setText("C:/");
    }else {
        // 给输入框设置选中的路径
    	ui->控件名称->setText(path);
        
        /* 读取文件 */
        #include <QFile>
        QFile file(path);
        // 使用指定方式打开
        file.open(QIODevice::ReadOnly);
        // 读取全部数据
        QByteArray arr = file.readAll();
        // 将数据放到UI中，这里是隐式转换，由QByteArray转Qstring
        ui->控件名称->setText(arr);
        
        /* 读取一行 */
        QByteArray arr = file.readLine();
        // file.atEnd：判断是否读到文件尾
        while(!file.atEnd()) {
            QByteArray arr = file.readLine();
        }
        
        /* 关闭文件 */
        file.close();
    }
})
```

### 二、写文件

``` c++
/* 读取文件 */
#include <QFile>
QFile file(path);
// 覆盖写
file.open(QIODevice::WriteOnly);
file.write("ccccc");
file.close();

/* 追加写 */
file.open(QIODevice::Append);
```

### 三、文件信息类

``` c++
#include <QFileInfo>
string path = "C://";
QFileInfo info(path);
// 后缀名
info.suffix();
// 大小
info.size();
// 文件名
info.fileName();
// 文件路径
info.filePath();
// 创建时间
info.created().toString("yyyy-MM-dd hh:mm:ss");
```

### 文件流

#### 1、数据量小

#### 2、数据量大

