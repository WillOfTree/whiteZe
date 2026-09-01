# Effective C++ 笔记

## 条款01：将C++视为一个语言联邦

1. 在使用C++的时候，将C++区分为4个模块（C语言、类、模板、STL），在不同的模块使用不同的策略或技巧
2. 在学习C++时，也应把C++分为4个模块，针对不同的模块进行学习

## ⭐条款02：使用const、enum、inline替换#define

使用constexpr/consteval代替#define定义常量

使用enum class代替数值定义

``` c++
#define STATUS_OK 0
#define STATUS_ERR 1
// 替换为
enum class STATUS {OK, ERR};
```

使用inline，constexpr关键字代替简单的宏函数

- 复杂的函数，不能使用inline等关键字代替
- inline关键字，只用于代码小于10行的函数

``` c++
#define SQUARE (x)((x)*(x))

```

## ⭐条款03：尽量使用const

**修饰变量**：承诺“这个值不会变”

- 这是最基本、最日常的用法。它让代码更安全，也方便编译器优化。

```c++
const int max_players = 4;          // 常量，不会在代码中被意外修改
const std::string game_name = "MyGame";
```

**修饰函数参数**：承诺“我不会修改你传进来的对象”

- 任何**只读访问**的参数，都应该用 `const T&`（特别是对象类型）。
- 对于基础类型（`int`、`float`），写成 `const int` 意义不大，按值传递即可。

```c++
// ✅ 正确：函数承诺不会修改传入的字符串
void log_message(const std::string& msg) {
    std::cout << msg << std::endl;  // 只读，不改
}

// ❌ 错误：如果函数不会修改，但没有加 const
void log_message(std::string& msg) {  // 调用者会困惑：它到底会不会改我的数据？
    std::cout << msg << std::endl;
}
```

**修饰成员函数**：承诺“这个函数不会修改对象的属性”

- 所有 **getter**、**检查器**（`is_`、`has_`）、**计算函数**（不修改成员变量）都应该加 `const`。
- 当被const修饰的函数可以修改用mutable定义的成员变量

```c++
class GameCore {
public:
    int get_version() const { return version_; }   // ✅ 只读，加 const
    void set_version(int v) { version_ = v; }      // ❌ 会修改，不加 const
private:
    int version_;
};
```

**修饰指针和引用**：区分“指针可变”还是“指向的值可变”

- `const char *  A = B`：A指向的值是常量
- `char * const A = B`：指针A是常量

| 写法                      | 含义                             |
| :------------------------ | :------------------------------- |
| `const char * A = B`      | `*A = "x";` 错误<br> `A = &B;`OK |
| `char * const A = B`      | `A = &B;`错误<br>`*A = "c";`OK   |
| `const int * const A = B` | 指针和指向的值都不能变           |

**修饰返回值**：防止调用者修改返回的结果

- 通常用于返回一个内部成员的引用，防止外部代码意外修改它。

```c++
class Player {
private:
    std::string name_;
public:
    const std::string& get_name() const { return name_; }  // 返回 const 引用，外部只能读
};
```

## ⭐条款04：对象使用之前被初始化

- 在C20标准下，推荐在对象声明是就赋值
- 一般情况可以使用`=`和`{}`进行赋值

优先使用赋值方法给类成员赋值

``` c++
class A {
    int version = 1;
    std::String name = "AA";
    int ss {2};
}

// STD的容器，默认构造就是创建一个空容器
std::vector<int> items_;      // ✅ 默认构造，空容器
std::vector<int> items_{};    // ✅ 值初始化，空容器（完全等价）
std::vector<int> items_ = {}; // ✅ 拷贝初始化，空容器（完全等价）

// 但是std::array是特殊的
std::array<int, 5> arr_;    // ⚠️ 元素未初始化！危险！
std::array<int, 5> arr_ {};  // ✅ 所有元素被值初始化为 0
```

必须使用**初始化列表**的情况：`const` 对象、 `&`引用对象、**没有默认构造函数的成员**、当成员变量值依赖外部赋值

``` c++
class MyCustomNode {
    // ...
private:
    const int health_;
    const std::string & name_;
public:
    // 初始化列表
    MyCustomNode() : health_(100), name_("Default") {} // ✅ 推荐的写法
};
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

## ⭐条款06：明确拒绝自动生成函数

- 使用`=delete`删除不需要的默认生成代码
- 单例不需要拷贝构造，拷贝赋值，移动构造，移动赋值 

``` c++
class TGDGeneralUtils  {
public:
    // ✅ 明确禁止拷贝构造和拷贝赋值
    TGDGeneralUtils(const TGDGeneralUtils&) = delete;
    TGDGeneralUtils& operator=(const TGDGeneralUtils&) = delete;

    // ✅ 禁止移动（单例不需要移动）
    TGDGeneralUtils(TGDGeneralUtils&&) = delete;
    TGDGeneralUtils& operator=(TGDGeneralUtils&&) = delete;

    static TGDGeneralUtils* get_singleton() { return singleton; }

private:
    TGDGeneralUtils() = default;  // 私有构造，防止外部创建
    static TGDGeneralUtils* singleton;
};

TGDGeneralUtils& s1 = TGDGeneralUtils::get();
TGDGeneralUtils s2 = s1; // ❌ 拷贝构造，创建了第二个实例！

TGDGeneralUtils s3 = TGDGeneralUtils::get();
s3 = s1;     // ❌ 拷贝赋值，覆盖了实例内容！
```

## ⭐条款07：多态基类声明为virtual析构函数

- 会被继承的类，基类函数一定要写virtual 析构函数
- **没有虚析构**函数可能会发生的问题：使用delete的时候，不能销毁子类

``` c++
class TimeKeeper { ... } // 父类，没有定义虚函数
class AtomicClock : public TimeKeeper { ... } // 子类继承TimeKeeper

TimeKeeper * getTimeKeeper(){ ... } ; // 定义一个函数，返回TimeKeeper类型的指针
// 获取动态分配对象
TimeKeeper *ptr = getTimeKeeper(); 
// 释放资源
delete ptk; //这里只能释放TimeKeeper对象，不能释放子类AtomicClock对象
```

解决方法，使用虚析构

- 几乎所有的**虚函数的基类**，都应有虚析构函数

``` c++
class TimeKeeper { 
public:
    virtual ~TimeKeeper(){ ... } // 虚析构函数，必须添加的方法
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

## 条款08：别让异常逃离析构函数

``` c++
// 对于可能出现异常的地方使用try
try {
    db.close(); //可能出现异常的地方
} catch (...){
    // 处理方法
}
```

## ⭐条款09：不在构造函数和析构函数中调用虚函数

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

## 条款10：令operator=返回一个reference to * this

- 这两样可以时用连续运算

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

## 条款11：在operator=中处理“自我赋值”

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


## 条款12：复制对象时勿忘其每一个部分

如题

## 条款13：以对象管理资源

- RAII：资源获取即初始化
- 使用对象来管理资源，让C++的析构函数自动 机制替你善后，直接使用new，delete容易出现问题
- RAII要求，讲资源的生命周期绑定到一个对象的生命周期上，当对象析构时会调用资源的析构
- 具体工具：**智能指针**

## 条款14：在资源管理中小心copying行为

- **你用 RAII 对象（如智能指针）管理资源时，如果这个对象被拷贝了，那么它“背后”的资源会发生什么？你必须明确设计这个行为，因为编译器默认生成的拷贝行为往往是错的。**
- 所以有4种方法，在设计RAII类时的解决方法

策略1：禁止拷贝（最安全，单例场景）

```c++
class Lock {
public:
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
};
```

策略2：引用计数（`shared_ptr` 自动帮你做）

```c++
std::shared_ptr<Texture> tex1 = ResourceLoader::load("icon.png");
auto tex2 = tex1;  // 引用计数 +1，两者共享同一份纹理
// 最后一个析构时释放资源，安全
```

策略3：深拷贝（复制底层资源）

```c++
class StringWrapper {
private:
    char* data_;
public:
    StringWrapper(const StringWrapper& other) {
        data_ = new char[strlen(other.data_) + 1];  // 新分配内存
        strcpy(data_, other.data_);                 // 复制内容
    }
};
```

策略4：转移所有权（`unique_ptr` 自动帮你做）

```c++
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
auto ptr2 = std::move(ptr1);  // ptr1 变空，ptr2 拥有资源
// 只有 ptr2 释放资源，安全
```

## ⭐条款15：在资源管理器中提供对原生资源的访问

- 考虑到通用性，等一些必要使用原始指针的情况，RAII类需要提供访问原始资源的方法

方式一：显式转换（用 `.get()`）

- 自己手动编写`.get()`方法
- **`std::unique_ptr` 和 `std::shared_ptr` 都提供了 `.get()` 方法。**

```C++
// ✅ 显式访问原始指针
displayInvestment(pInv.get());
```

方式二：隐式转换（重载 `operator T*`）

- **优点**：调用者感觉就像在使用一个裸指针，极其自然。
- **缺点**：隐式转换可能带来意外错误，比如在拷贝时误转。

```c++
class MyRAII {
private:
    int* resource_;
public:
    operator int*() const { return resource_; }  // 隐式转换为 int*
};

void use_int(int* p) {}

MyRAII obj;
use_int(obj);  // ✅ 隐式转换，编译器自动调用 operator int*()
```

## ⭐条款16：成对使用new和delete时要采取相同形式

``` c++
std::string * s1 = new std::string[100];
delete [] s1;

std::string * s2 = new std::string;
delete s2;
```

## ❓条款17：以独立语句将newed对象置入自能指针

pass

## ❓条款18：让接口容易被正确使用，不易被误用

## ❓条款19：设计class犹如设计type

## ⭐+条款20：宁以pass-by-reference-to-const替代pass-by-value

- 除非有明确理由，函数的参数都应以常量引用（**`const T&`**）的方式传递，而不是值传递
- 值传递问题
  1. **调用拷贝构造函数**（开销可能很大）。
  2. **调用析构函数**（释放临时副本）。
  3. **如果对象很大**（比如 `std::vector`、`std::string` 或自定义类），拷贝的开销会非常明显。
  4. **传值还会导致“对象切片”（Slicing）问题**：

可以使用值传递的情况

- **内置类型**（`int`、`double`、`char*` 等）：传值比传引用更高效（因为引用本身也是指针）。
- **STL迭代器和函数对象**：按惯例，STL 迭代器和函数对象也传值。
- **你确实需要复制**：如果函数需要保存一份本地副本（比如在构造函数里存储参数），传值可以配合移动语义优化。

## ⭐+条款21：必须返回对象时，别妄想返回其reference

- 此条款适用于栈对象（使用new创建的是堆对象）

- 当你必须返回一个“新对象”时，不要试图返回一个指向局部对象的引用或指针，因为那个对象在函数返回时已经被销毁了。

- 【栈】**正确的做法就是：返回一个对象（按值返回），而不是返回引用或指针。**

  很多初学者担心“按值返回会拷贝多次，效率低”。实际上：

  1. **C++17 起有强制拷贝省略（Guaranteed Copy Elision）**：临时对象直接构造在调用者的目标位置，**零次拷贝**。
  2. **即使没有 C++17，编译器也会做返回值优化（RVO）和移动语义**，性能开销极小。
  3. **返回引用所节省的性能远小于返回悬空引用带来的崩溃风险**。

- 【堆】当要返回的是堆对象时，应该返回智能指针，直接返回new创建的对象也是不安全的（没有人负责析构）

## ⭐条款22：将成员变量声明为private

如题

## ⭐+条款23：宁以non-member,non-friend替代member函数

- **如果一个函数可以不用访问类的私有成员就能实现，那么它就应该被设计为 `non-member` 非成员函数（且不是 `friend`），而不是类的成员函数。**

- 为什么推荐非成员函数？核心原因是**封装性（Encapsulation）**。

  - **成员函数可以访问私有成员**（包括私有的函数和数据），因此它的“权力”更大。
  - **非成员函数只能访问公有接口**，它的“权力”更小。
  - **权力越小，耦合度越低，封装性越好。**

  **用一句话说：能够通过公有接口完成的功能，就不要让它成为成员函数，以免它接触到不该接触的内部细节。**

可以直接定义为类的静态方法，或者使用namespace关键字

- 静态方法与静态变量不同，静态变量需要占用静态存储区，但静态方法与普通方法一样，就是没有this指针

``` c++
// 核心功能（必须访问私有成员的）
class TGDGeneralUtils {
private:
    Dictionary config_data_;
public:
    void save_config(const String& path);   // 需要访问 config_data_
    Dictionary get_config() const;          // 需要访问 config_data_
    
    // ✅ 静态成员函数：不访问实例成员，但通过类名调用，逻辑上属于这个类
    static void Update(double delta);
};

// 使用命名空间
namespace T {
    namespace TGD {
        // 复杂的代码，要在.cpp中实现
        void reset_config(TGDGeneralUtils& utils);
        void print(utils.get_config());  
        
        // 极其简单的代码使用inline关键字
        // 直接在.h文件中编写
        inline void reset_config(TGDGeneralUtils& utils) {
            utils.load_config("res://default.cfg");  // 只调用公有接口
        }
    }
}

// .cpp调用
T::TGD::reset_config(utils);
```

## ❓条款24：若所有参数接需要类型转换，请为此采用non-member函数

- **当运算符（如 `operator*`）的所有参数（包括左操作数）都可能需要隐式类型转换时，这个运算符必须重载为 `non-member` 函数，而不能是 `member` 函数。** 

  

## ❓条款25：考虑出一个不抛异常的swap函数

## ⭐条款26：尽可能延后变量的定义时间

- 简单的来说，变量应该在你真正需要的时候才定义，而不是在函数开头就定义好
- 尽可能在定义时初始化，而不是先定义再赋值
- 如果在循环中变量每次都要初始化，则在循环体内部定义
- 如果变量在循环体只是赋值，且代价高，在循环体外部定义

## ⭐条款27：尽量少做转型动作

- **转型（cast）是危险的，应该尽量避免。如果必须使用，也要用 C++ 风格的新式转型，而不是 C 风格的旧式转型。** 

场景 1：Godot 类型与 C++ 类型之间的转换（用 `static_cast`）

```c++
// Godot 的 Variant 类型转换
int value = static_cast<int>(variant);  // 明确转换

// 枚举类型转换
ITurnbaseState::FSMStateType state = 
    static_cast<ITurnbaseState::FSMStateType>(aim_state);
```

场景 2：多态对象转型（用 `dynamic_cast`）

- **注意**：`dynamic_cast` 需要基类有虚函数（如 `godot::Object`），否则编译报错。

```c++
// 假设你有一个基类指针，需要转为派生类
Node* node = get_node("Player");
Player* player = dynamic_cast<Player*>(node);
if (player) {
    player->jump();  // 安全调用派生类方法
}
```

场景 3：去掉 `const`（用 `const_cast`，极少用）

```c++
void process(const String& str) {
    // 如果某个旧 API 需要非 const 指针（尽量避免）
    char* mutable_str = const_cast<char*>(str.utf8().get_data());
}
```

## ⭐条款28：避免返回handles指向对象内部成分

- **不要返回指向对象内部成员（如成员变量、私有数据）的引用、指针或迭代器（这些统称为“handles”），以免破坏对象的封装性，导致悬垂引用（dangling handles）或意外修改。** 
- 如果必须返回，有以下方案
  1. 用const保护
  2. 按值返回（返回副本）
  3. 如果返回引用，确保对象生命周期比引用长

``` c++
// 使用const保护
class Player {
private:
    int health_;
public:
    const int& getHealth() const { return health_; } // ✅ 只能读，不能改
};

// 按值返回
class Player {
private:
    std::string name_;
public:
    std::string getName() const { return name_; } // ✅ 返回副本，完全安全
};

// 如果返回引用，确保对象生命周期比引用长
class Game {
private:
    std::vector<Player> players_;
public:
     // ✅ 对象在 Game 内，生命周期明确
    Player& getPlayer(int index) { return players_[index]; }
};
```

**关于按值返回这个方案：**

- 只要函数返回的不是**指针**（`T*`）或**引用**（`T&`），那么返回的就是一个**独立的副本**。调用者对这个返回值的任何修改，都不会影响原始对象。
- 同时普通函数也是适用的，范围包括容器，普通变量
- 但是数组会退化为指针，返回的是数组指针

## 条款30：透彻了解inlining的里里外外

多数情况，编译器的优化远超90%的程序员，所以不要自己手动添加inline关键字，除非在.h文件中写一些极短的函数

## ⭐条款31：将文件间的编译依存关系降到最低

方案一：用指针/引用代替值成员

- `Person.hpp` 不再依赖 `Address.hpp` 和 `Job.hpp` 的具体定义。
- 修改 `Address` 或 `Job` 时，只有 `Person.cpp` 需要重新编译，而不是所有包含 `Person.hpp` 的文件。

```c++
// Person.hpp（头文件）
#include <string>

class Address;   // ✅ 前置声明
class Job;       // ✅ 前置声明

class Person {
private:
    std::string name_;
    std::unique_ptr<Address> address_;  // ✅ 用指针代替值对象
    std::unique_ptr<Job> job_;
};

// Person.cpp（实现文件）
#include "Person.hpp"
#include "Address.hpp"   // ✅ 真正的依赖放在 .cpp 里
#include "Job.hpp"

Person::Person() : address_(std::make_unique<Address>()), job_(std::make_unique<Job>()) {}
```

方案二：使用接口类（抽象基类）

- 如果你希望彻底解耦，可以让 `Person` 只依赖 `Address` 和 `Job` 的抽象接口：

```c++
// Person.hpp
class AddressInterface;   // 抽象基类
class JobInterface;       // 抽象基类

class Person {
private:
    std::unique_ptr<AddressInterface> address_;
    std::unique_ptr<JobInterface> job_;
};

// 具体实现放在 .cpp 或单独的模块中
```

方案三：PIMPL 惯用法（Pointer to IMPLementation）

- 这是 C++ 中非常经典的一种解耦技巧，把类的所有私有成员都封装到一个实现类中：
- 任何 `Address` 或 `Job` 的改动，都不会导致 `Person.hpp` 的变更。
- 只有 `Person.cpp` 需要重新编译。
- 这是 C++ 中降低编译依赖最彻底的方案。

```c++
// Person.hpp（头文件，只有接口）
class Person {
public:
    Person();
    ~Person();
    void setName(const std::string& name);
private:
    struct Impl;              // ✅ 只声明内部结构
    std::unique_ptr<Impl> pImpl_;  // 指向实现的指针
};

// Person.cpp（实现文件）
#include "Person.hpp"
#include "Address.hpp"
#include "Job.hpp"

struct Person::Impl {
    std::string name;
    Address address;
    Job job;
};

Person::Person() : pImpl_(std::make_unique<Impl>()) {}
Person::~Person() = default;
void Person::setName(const std::string& name) { pImpl_->name = name; }
```

## ❓条款32：确定你的public继承塑膜出is-a关系

## 条款33：避免遮掩继承而来的名称

``` c++
class Derived : public Base {
public:
    using Base::func;        // ✅ 将基类的所有 func 重载引入到派生类作用域
    void func() {            // 这个会覆盖其中一种行为
        std::cout << "Derived::func()\n";
    }
};

Derived d;
d.func();      // ✅ Derived::func()
d.func(10);    // ✅ Base::func(int)
```

## 条款34：区分接口继承和实现继承

纯虚函数（`= 0`）：声明一个“契约”

- **意图**：告诉派生类：“你必须支持这个操作，但我不知道你怎么做。”

```c++
class ITurnbaseState {
public:
    virtual void OnEnter() = 0;   // ✅ 所有状态都必须有 OnEnter，但各自实现不同
};
```

普通虚函数：提供“默认行为”，允许派生类修改

- **意图**：告诉派生类：“你有一个默认做法，但如果需要，你可以改。”

```c++
class Enemy {
public:
    virtual void takeDamage(int damage) {
        health_ -= damage;   // ✅ 默认：直接扣血
        if (health_ <= 0) die();
    }
};
```

非虚函数：规定“不变的行为”

- **意图**：告诉派生类：“这个行为是固定的，不要修改它。”

```c++
class Player {
public:
    void saveGame() {
        // ✅ 整个游戏的存盘流程是固定的，派生类不应该改变
    }
};
```

## ⭐条款35：考虑virtual函数以外的其他选择

- **“不要把虚函数（`virtual`）当成解决问题的唯一工具。有很多更灵活、更解耦的设计模式可以替代它。”** 

方案 1：NVI（非虚接口）—— 用 public 非虚函数包裹 private 虚函数

- **核心思想**：把 `virtual` 函数设为 `private`，通过一个 `public` 非虚函数来调用它。这样基类可以控制调用时机（比如加锁、日志、前置/后置条件检查）。
- **优点**：
  - 基类可以控制流程，强制派生类遵循规则。
  - 派生类只需要关注核心逻辑，不需要重复处理横切关注点（如日志、校验）。

```c++
class GameCharacter {
public:
    // ✅ 对外接口：非虚函数，固定流程
    void takeDamage(int damage) {
        log("Before damage");   // 前置操作
        doTakeDamage(damage);   // 调用私有虚函数
        log("After damage");    // 后置操作
    }
    
private:
    virtual void doTakeDamage(int damage) = 0;  // 派生类重写这个
};
```

方案 2：策略模式（函数指针）—— 把行为当作对象传递

- **核心思想**：不要继承基类，而是把行为封装成一个独立的函数（或函数对象），通过构造函数或方法注入。
- **优点**：
  - 行为可以**运行时动态切换**。
  - 不需要为每种策略创建一个新类。

```c++
class GameCharacter {
public:
    // 用函数指针指定“健康计算”策略
    using HealthCalcFunc = int(*)(int level);
    
    explicit GameCharacter(HealthCalcFunc hcf) : healthFunc_(hcf) {}
    
    int getHealth() const { return healthFunc_(level_); }
    
private:
    HealthCalcFunc healthFunc_;
    int level_ = 10;
};

// 不同的健康计算策略
int baseHealth(int level) { return level * 10; }
int eliteHealth(int level) { return level * 20; }

// 使用
GameCharacter normal(baseHealth);
GameCharacter elite(eliteHealth);
```

方案 3：`std::function` —— 更灵活的策略模式

- 用 `std::function` 替代裸函数指针，可以接受**函数、Lambda、函数对象**等任意可调用对象，灵活度更高。
- **优点**：
  - 比函数指针更灵活，可捕获上下文。
  - 更容易与现代 C++ 风格融合。

```c++
class GameCharacter {
public:
    using HealthCalcFunc = std::function<int(int)>;
    
    explicit GameCharacter(HealthCalcFunc hcf) : healthFunc_(hcf) {}
    
private:
    HealthCalcFunc healthFunc_;
};

// 使用
GameCharacter char1([](int level) { return level * 10; });           // Lambda
GameCharacter char2(std::bind(&healthCalc, std::placeholders::_1));  // 绑定
```

方案 4：策略模式（类继承） —— 用独立的类层次封装算法

- 将算法封装在独立的类层次中，通过组合的方式注入到主类中。

```c++
class HealthCalcStrategy {
public:
    virtual int calc(int level) const = 0;
    virtual ~HealthCalcStrategy() = default;
};

class NormalHealthCalc : public HealthCalcStrategy {
public:
    int calc(int level) const override { return level * 10; }
};

class EliteHealthCalc : public HealthCalcStrategy {
public:
    int calc(int level) const override { return level * 20; }
};

class GameCharacter {
public:
    explicit GameCharacter(const HealthCalcStrategy& strategy) : strategy_(strategy) {}
    
private:
    const HealthCalcStrategy& strategy_;
};
```

## 条款38：通过复合塑出has-a或根据某物实现出

- **“复合（Composition）是一种比继承更灵活、更解耦的关系。它用来表达‘有一个’（has-a）或‘根据某物实现’（is-implemented-in-terms-of）。”** 

``` c++
class Address {};
class PhoneNumber {};

class Person {
private:
    std::string name_;          // 复合（字符串对象）
    Address address_;           // 复合（Address 对象）
    PhoneNumber phone_;         // 复合（PhoneNumber 对象）
};
```

## ⭐条款39：明智而审慎地使用private继承

除非需要利用“空基类优化”（EBO），其他情况可使用复合代替，不要使用private继承

## ⭐条款40：明智而审慎的使用多重继承

- 多继承问题多多，可使用虚继承解决，不要使用多重继承

## ❓条款41：了解隐式接口和编译期多态

## ❓条款42：了解typename的双重意义

## ❓条款43：学习处理模板化基类的名称

## ❓条款44：将与参数无关的代码抽离templates

## ❓条款45：运用成员函数模板接受所以兼容类型

## ❓条款46：需要类型转换时请为模板定义非成员函数

## ❓条款47：请使用traits classes表现类型信息

## ❓条款48：认识template元编程

## ❓条款49：了解new-handler行为

## ❓条款50：了解new和delete的合理替换时机

## ❓条款51：编写new和delete时需固守常规

## ❓条款52：写了placement new也要写placement delete
