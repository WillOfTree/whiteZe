# Effective C++ 笔记

## 前言其他

### 一、顶层const/底层const

- 只有一个const（`const int a`）：顶层const
- 有2个const（`const int * const a`）：第一个const是底层，第二个const是顶层

> 《Effective C++》P58：当执行对象拷贝操作种，常量的顶层const不受影响，而底层const必须一致

- 靠近变量的是`顶层const`，可以忽略的const

- 拷贝操作，普通变量的赋值一般都是拷贝操作

- “引用&”不适用当前规则

  常量的引用（`const int &a`）可以接任何类型

  普通变量可以赋值常量引用

``` c++
/* 顶层const可以忽略 */
const int a = 10;
int b = a; // 这里就不受影响，其a的const可以去掉
int *b = &a; // 错误，取地址相等于加了底层const
const int *b = &a; //正确

/* 多个const，底层const必须一致 */
const int * const p = new int(10);
const int *p1 = p; // 正确
int *p1 = p; //错误
int * const p = p; //错误
```

### 二、右值优化

1. 禁用右值优化，编译器会自动右值优化

   `set(CMAKE_CXX_STANDARD 14)`

   `set(CMAKE_CXX_FLAGS -fno-elide-constructors)` 

2. 拷贝次数理解

   这里就说明了，为什么使用指针/引用取值，更高效

   ``` c++
   // 此方法发生了2次拷贝
   int gate() {
       int a = 10; // 拷贝第1次，当函数执行完后会释放资源
       return a; // 返回值不会直接返回给x，而是返回给一个临时变量temp
   }
   int x = gate(); // 将临时变量temp赋值给x（赋值给x后会释放temp）， 拷贝第2次
   ```

3. 未确定概念

   1. C++表达式
   2. 左值引用不接受右值引用，左值引用2次就变右值；`int &&y = 10 // 正确` 
   3. 移动拷贝：`Big a = std::move(bb);` 
   4. 将亡值

## 条款01：将C++视为一个语言联邦

1. 在使用C++的时候，将C++区分为4个模块（C语言、类、模板、STL），在不同的模块使用不同的策略或技巧
2. 在学习C++时，也应把C++分为4个模块，针对不同的模块进行学习

## 条款02：使用const、enum、inline替换#define

1. 使用#define不能进行类型检查，出现错误不容易发现

2. 使用常量替换#define

   ``` c++
   /* 普通数值 */
   #define AspectRation 1.63
   // 替换为
   const double AspectRatio = 1.653;
   
   /* 字符串替换 */
   #define AuthorName "Scott Meyers" 
   // 替换为以下2种的任意一种，使用string的更容易
   const char* const authorName = "Scott Meyers";
   const std::string authorName("Scott Meyers");
   ```

3. 类中定义的#define没有意义

   ``` c++
   class A {
   private:
       /* 方式一，使用静态变量 */
       #define NUM 5 // 没有意义，无法在类A作用域中
       //应替换为这种定义方式，
       // 类专用的静态整数类型常量，不用定义即可使用
       static const int Num = 5; // 声明，例外，不用类外定义
       
       /* 方式二，使用枚举 */
       enum {Num = 5};
   }
   // 方式一,不用类外定义
   // const int A::Num;
   ```

4. 使用内联函数替换#define定义函数

   - 例子会因为参数不同，返回的值也是不同的，造成不可预测结果
   - 可获取宏的效率，以及不同函数可预测的结果，类型安全

   ``` c++
   int f(int num){ return num}; // 使用的函数
   // 宏定义
   #define CALL_MAX(a, b) f((a)>(b)?(a):(b))
   // 替换为内联函数模板
   template<typename T>
   inline T Call_Max(const T &a, const T&b) {
       return f(a>b ? a:b);
   }
   ```

## 条款03：尽量使用const

1. const用于指针

   `const *`，远离变量，指向的值是常量

   `* const`，靠近变量，指针本身是常量

   ``` c++
   /* 指针可以指向任意变量 */
   int greeting = 100;
   const char * p = greeting; // 指针是可以修改的
   p = &a; // p可以指向其他地址
   *p = 20; // 错误
   
   /* 指向的内容可以修改 */
   char * const p = greeting; // 指向的内容可以修改
   p = &a; // 错误，不可以，
   *p = 20; //可以修改
   ```

2. 定义函数返回值

   ``` c++
   class Rational {};
   const Rational operator* (const Rational &l, const Rational &R);
   
   Rational a,b,c;
   (a*b) = c; //错误, a*b返回值为const不能为左值
   // 当写成这样，就会报错
   if (a*b = c); //应该写成==
   ```

3. 在成员函数上使用const，返回类型不可修改

   - 可以使接口意图更加明确，确定那些函数可以修改对象
   - mutable 关键字 ？
   - const_cast / static_cast

   ``` c++
   const int hum(int a) const{// 限定整个函数不允许修改  
   ```

## 条款04：对象使用之前被初始化

1. c语言部分，一般都不会初始化，而C++部分一般会被初始化

2. 构造函数中的是赋值，并不是初始化

   ``` c++
   class A {
   public:
       A(const std::string & name, const std::string address) {
           // 赋值，并非初始化
           theName = name;
           theAddress = address;
           num = 0;
       }
   private:
       /* 这些是使用库，会先赋值给一个临时变量，造成资源浪费 */
       std::string theName;
       std::string theAddress;
       /* 这个可以直接构造 */
       int num;
   }
   ```

3. 更好的方法是使用初始列表

   ``` c++
   class A {
   public:
       // 使用初始列表
       A(const std::string & name, const std::string address)
           : theName(name), theAddress(address), num(0){}
   private:
       std::string theName;
       std::string theAddress;
       int num;
   }
   ```

4. 不同编译单元（不同文件的源代码）中定义的非局部静态对象（除静态变量以外的变量）的初始顺序是不确定的

   - 可能造成的问题是，使用过程中发现类未定义，但在编写代码的时候，定义顺序是正常的
   - 解决办法：使用静态对象定义，避免跨编译单元的初始化问题

   ``` c++
   class F {};
   
   F& tfs() { // 类外定义一个函数，返回静态对象
      static F fs;
      return fs; // 直接返回对象
   }
   ```

## 条款05：C++默认调用函数顺序

1. 编译器会隐式生成类的**构造函数**、**拷贝构造函数**、**析构函数**、**拷贝赋值运算符（=）** 

   - `Empty el`：会自动添加构造函数、析构函数
   - `Empty e2(el)`：会自动添加拷贝构造函数
   - `el = e2`：会自动添加拷贝运算符函数

   ``` c++
   class Empyt {} // 什么都不写的类
   // 与下面的是等价的
   class Empyt {
       Empty() {...} // 默认构造函数
       Empty(const Empty & rhs) { ... } // 默认拷贝构造函数
       ~Empty() { ... } //析构函数
       Empty & operator=(const Empty& rhs) {...}// 拷贝运算符
   }
   ```

2. 编译器生成的代码，往往是非常简单的，若有歧义，就不会进行编译，并生成一个错误

3. 基类的拷贝赋值运算符（operator=）是private，其派生类将无法生成拷贝赋值运算符，因为无法调用基类部分的函数处理基类部分

## 条款06：明确拒绝自动生成函数

1. 将拷贝赋值和拷贝构造声明为private

   ``` c++
   class A {
   private:
       // 当调用 = 或拷贝构造时，程序会报错
   	A(const A &); // 声明，不用定义
       A & operator= (const A &); // 只声明，不定义
   }
   ```

2. C++ 11 使用的方法（推荐）

   ``` c++
   // 禁用编译器自动生成代码
   class uncopytable {
   public:// private也是可以的
       uncopytable(const uncopyable &) = delete;
       uncopyable & operator= (const uncopyable &) = delete;
   }
   ```

## 条款07：多态基类声明为虚析构函数

1. 没有虚析构函数可能会发生的问题：使用delete的时候，不能销毁子类

   ``` c++
   class TimeKeeper { ... } // 父类，没有定义虚函数
   class AtomicClock : public TimeKeeper { ... } // 子类继承TimeKeeper
   
   TimeKeeper * getTimeKeeper(){ ... } ; // 定义一个函数，返回TimeKeeper类型的指针
   // 获取动态分配对象
   TimeKeeper *ptr = getTimeKeeper(); 
   // 释放资源
   delete ptk; //这里只能释放TimeKeeper对象，不能释放子类AtomicClock对象
   ```

2. 解决方法，使用虚析构

   几乎所有的虚函数的基类，都应有虚析构函数

   ``` c++
   class TimeKeeper { 
   public:
       // 虚析构函数
       virtual ~TimeKeeper(){ ... }
   } 
   class AtomicClock : public TimeKeeper { ... } // 子类继承TimeKeeper
   // 定义一个函数，返回TimeKeeper类型的指针
   TimeKeeper * getTimeKeeper(){ ... } ; 
   
   // 获取动态分配对象
   TimeKeeper *ptr = getTimeKeeper(); 
   // 释放资源, 由于父类有虚析构函数，
   // 这里会先析构子类，再析构父类
   delete ptk; 
   ```

3. STL的String是不包含虚析构函数的

## 条款08：异常

``` c++
// 对于可能出现异常的地方使用try
try {
    db.close(); //可能出现异常的地方
} catch (...){
    // 处理方法
}
```

## 条款09：不在构造函数和析构函数中调用虚函数

1. 例子：

   ``` c++
   class Transaction {
   public:
       Transaction(); // 构造函数
       virtual void logTransaction() const = 0;
   }
   Transaction::Transaction(){
       logTransaction(); // 在构造函数中调用虚函数
   }
   
   class BuyTransaction: public Transaction {
   public:
       virtual void logTransaction() const;
   }
   
   // 注意，这里构造函数会先调用Transaction的logTransaction方法，再调用子类的logTransaction方法
   // 若派生类的数据没有准备好，会出错
   BuyTransaction b;
   ```

## 条款10：操作符重载

1. 这两样可以时用连续运算

``` c++
class Widget {
public:
    Widget & operator= (const Widget& rhs)
    {
        // ...
        return *this;
    }
}
```

## 条款11：防止自我赋值

1. 当使用指针获取数组时，有可能对同一个变量进行赋值

   ``` c++
   class W {..}
   W w1;
   w1 = w1; //这看起来很傻，但有些地方不容易看出来
   
   a[1] = a[2]; // 若a[1]、a[2]中都存放相同的对象，就很隐蔽
   *p = a; // 同理
   ```

2. 防止自我赋值方法

   ``` c++
   Widget & Widget::operator= (const Widget& rhs)
   {
       if (this == &rhs) return *this; 
   }
   ```

   

## 条款12：拷贝对象所以部分

1. 
