## 常用目录结构

``` shell
project 
├─bin # 编译后的可执行文件
├─build # 存放.O 或.dep文件
|	├─debug
|	└─release
├─doc # 项目文档
├─include # 所有头文件
├─src # 源文件
├─lib # 静态库或动态库
├─external # 第三方库
├─tests # 测试代码
├─Makefile # 项目构建配置文件
└─README.md # 项目总体说明文件
```

## HelloWorld

- `<>`：系统头文件
- `""` ：自定义头文件，当前文件所在的目录
- `.h`：是c语言的库，c++的库是不带.h

``` c++
// 标准输入输出流
#include <iostream> 
// 使用命名空间，可以省略std::的书写
// 不建议大面积使用，只在局部使用
useing namespace std;
// 因为iostream中有引入string库，所以可以不引用string而使用string定义变量
// 但要是使用string,应写上#include <string>
#include <string>

int main(int argc, const char * argv[]){
    // 标准的命名空间std
    // cout标准输出
    // << 左运算符，拼接基础类型，字符串
    // endl换行
	std::cout << “hello world” << std::endl;
	system(“pause”);//阻塞

	return EXIT_SUCCESS; // 返回正常退出
}
```

## 引用（&）

### 一、引用的基本用法

- 理解：给变量起别名，他们都指向同一块内存，本质上使用的是指针。

- 语法：`数据类型 &别名 = 变量名| 数组名 |函数名`

  `int &a = b`：定义一个引用变量

``` c++
int a = 100;
int &b = a; // 相当于 int *b = &a;
b = 20;// 修改b，a的值也修改，他们是同一块内存

/* 错误引用 */ 
// 引用必须是一个合法的空间
int &b = 100;

/* 数组引用 */
int a[10] = {0};
int (&arr)[10] = a; //给数组起别名,arr指向a的空间

/* 函数引用 */
int &cc = func(); //引用类型的函数
```

### 二、引用的注意事项

- 引用必须初始化

  ``` c++
  int &a; //错误，没有初始化
  int &a = b; // 正确
  ```

- 引用初始化后不可修改

  ``` c++
  int b = 200;
  int &c = b;
  &c = 300; //错误，引用已经指向了b
  c = 300;  //这是赋值操作，不是引用，正确
  ```

- 并没有引用变量（与指针不同），当去掉&符号，就是普通变量（而指针，只要声明了指针变量，他就一直是指针变量，不论带不带*）

### 三、常量引用

- **避免不必要的拷贝**：常用于函数参数，避免大对象拷贝
- **只读访问**：通过常量引用不能修改所引用的对象
- 若想把函数中的变量数值带出，必须使用* 或&，不论变量是什么类型（int，double等都需要）

``` c++
const int & ref = 10; // 可以赋值任何值
ref = 20;// 错误，ref不能修改

void test(const int &val)
{
    val = 100; //错误不能修改
}
```

## 内存模型

1. 代码区：存放函数的二进制代码，由操作系统管理
2. 全局区：存放全局变量和静态变量以及常量
   - 全局变量、静态变量、常量区、字符串常量、const定义的常量
3. 栈区：由编译器自动分配释放，函数参数、局部变量
4. 堆区：程序员控制，程序结束自动释放
   - 使用new运算符

New创建空间

- 返回的是该类型的**指针**

``` c++
// 创建10个int类型的空间
int *p = new int(10);
    
// 创建数组,10个连续空间的数组
int *arr = new int[10];
    
// 函数
int * func(){}
int *p = func()
```

delete释放空间

```c++
/* 普通变量 */ 
int *p = new int(10)
// 删除
delete p;

/* 释放数组 */ 
// 新建数组
int *p = new int[10];
// 释放整个数组，一定要加[]
delete [] arr;
// 释放数组中的一个值
delete arr[2];
```

## 函数高级

### 对于参数/返回值的总结

1. **对于内置类型**（int, double, bool等）：直接使用值传递
2. **对于小型自定义类型**：根据需要选择
3. **对于大型对象**：总是使用 `const &`
4. **值需要修改时**：使用 `&`（去掉const）
5. **需要副本时**：明确使用值传递

### 一、默认参数

如果有一个值有默认参数，从这个位置开始，到最后面都必须有默认参数

``` c++
// 声明
int func(int a = 1111);
// 从b开始到最后都必须有默认参数
int func(int a, int b =1, int c=2);
```

定义和声明，只能有1个默认参数。

``` c++
int func(int a=1); // 声明中含有默认参数
int func(int a) // 定义就不需要默认参数
{
    return 1;
}

int func(int a); // 声明就不用默认参数
int func(int a=1)  // 定义中含有默认参数
{
    return 1;
}
```

### 二、占位参数

``` c++
// 第二个参数是占位参数
void func(int a, int){
    return 1;
}
func(1,2)
    
// 占位参数的默认值
void func(int = 10){
    return 1;
}
func()
```

### 三、函数重载

函数名相同，但参数不同，从而根据参数选择不同的函数

- 参数不同包括，个数、类型、顺序、引用类型
- 函数的返回值，不能变成重载方式
- 重载，不加默认参数

正常调用

``` c++
void func(int a){
    count << "func的调用——1"
}
void func(){
    count << "func的调用——2"
}


func(1); // 输出func的调用——1
func(); // 输出func的调用——2
```

常量，其他情况

``` c++
void func(int a){
    count << "func的调用——1"
}
void func(const int a){
    count << "const int a"
}
int v = 10; // 变量

func(v); // 输出func的调用——1，v是变量
func(10); // 输出 const int a，10是常量
```

### 四、引用传值（const &与&）

1. 避免不必要的拷贝（重要优势）
2. 可以修改外部变量的值（引用可以看成使用了指针）
3. 通过引用参数，带出多个值

使用const &与&区别

- const & 定义的参数，值不能修改。
- const & 定义的参数在编译的时候，编译器可能会进行更多优化（因为知道不会修改）

使用&传递变量

``` c++
// 值传递 - 产生拷贝（性能差）
void process(vector<int> data) {
    data.size();
}

// 引用传递 - 无拷贝（性能好）
void process(vector<int> & data, int & value) 
{
    data.size(); // 引用变量使用方法与普通变量相同
    value++; // 直接修改原始变量
}

// 通过指针修改（C风格，不推荐在现代C++中使用）
void incrementPtr(int * value) {
    (*value)++;
}

// 通过引用返回多个计算结果
void analyzeVector(
    std::vector<int> & vec, 
    int & minVal) 
{
	//...
}
```

常量引用`const & `：只读访问

``` c++
// 大多数情况下应该这样写
// 参数使用常量引用，避免拷贝
void printInfo(const std::string & prefix) { }

// 需要修改时去掉const
void modifyFunction(std::vector<int> & data) { }

// 值传递，会发生完整拷贝：调用时整个vector被复制一份
// 明确表示需要副本时才使用这个
void processByValue(std::vector<int> data) { }
```

现代C++版本

```c++
// 现代C++中的灵活用法
void smartFunction(std::vector<int> data) { }

// 调用者可以选择：
smartFunction(vec); // 拷贝（如果不介意）
smartFunction(std::move(vec)); // 移动（高效）
```

### 五、返回值

#### Ⅰ、普通返回值

- **最安全**：返回的是独立副本

  **注意**：独立副本意味着重新复制了一份，能获取到局部变量，就是因为返回的是复印件

  `&、*、const &`都不能保存局部变量，但是直接返回可获取副本 

- ✅ **支持所有类型**：包括局部变量

- ⚠️ 若返回一个非基础类型的变量，**可能有拷贝开销**：但现代编译器有优化（NRVO/RVO）

- ✅ **C++17强制优化**：返回局部对象时保证无额外拷贝

**适用情况**：所有的基本变量（int, double等），都应该使用普通返回值；若不考虑性能，所有类型都可以值返回

``` c++
int calculateSum(int a, int b) 
{
    return a + b;
}
```

#### Ⅱ、返回常量引用 (`const &`)

- 与`&`效果相同，但是返回值不允许修改

``` c++
// 返回静态或全局数据
const string & getDefaultName() 
{
    return defaultName;
}

const & String a = getDefaultName();
```

#### Ⅲ、返回引用（&）

``` c++
string & test()
{
    static string a = 10; // 可以返回，静态变量
    string a = "xxx"; // 不能，函数结束后就消失
    return a;
}
```

特殊情况，但是不推荐这么使用

``` c++
int & test()
{
    int a = 10; // 局部变量一般不能返回，但是基本变量可以（int,double等）
    return a;
}
```

错误示例：

``` c++
// 错误示例1：返回局部vector的引用
std::vector<int> & getVectorBad() {
    std::vector<int> localVec = {1, 2, 3};  // 局部变量
    return localVec;  // ❌ 危险！返回即将销毁的局部变量的引用
}  // localVec在此销毁！

// 错误示例2：返回局部vector的指针
std::vector<int> * getVectorPointerBad() {
    std::vector<int> localVec = {1, 2, 3};
    return &localVec;  // ❌ 危险！返回指向局部变量的指针
}
```

#### Ⅳ、参数带出

- ✅ **可返回多个值**：通过多个输出参数
- ⚠️ **可读性差**：不如返回值直观
- ✅ **避免拷贝大对象**：可以重用已分配内存
- ❌ **现代C++不推荐**：优先使用返回值或tuple

适用场景

``` c++
// 1. 需要返回多个相关值
void analyzeString(const std::string& str, 
                  int& charCount, 
                  int& wordCount, 
                  int& lineCount) {
    // 计算多个统计值
}

// 2. 需要重用内存避免分配
void processLargeData(const BigData& input, BigData& output) {
    output.reuseMemory(); // 重用已分配内存
    // 处理数据到output
}

// 3. 需要返回成功/失败状态
bool loadFromFile(const std::string& filename, 
                 std::vector<std::string>& lines) {
    std::ifstream file(filename);
    if (!file) return false;
    
    return true;
}
```

## 作用域

:: 运算符

- 作用域运算符
- 子类调用父类方法的运算符

```c++
// 作用域运算符
// 全局atc ::atc 
int atc=100;
void function()
{
	cout << ::atc <<endl //使用全局atc
	std::cout //std作用域下的cout方法
}
```

namespace关键字

- 使用命名空间，可以省略std::的书写
- 不建议大面积使用，只在局部使用

```c++
//命名空间必须定义在全局作用下
//命名空间可以嵌套命名空间
//命名空间可以放函数，变量，结构体类
//命名空间是开放的，可以随时添加进原来的命名空间，**同一个命名空间名会合并**
namespace LOL  // 声明一个命名空间
{
	void goattc();//函数
	int a;//变量
	struct Person{};//结构体
	class B{};//类
	namespace D{};//命名空间LOL::D::
}

//无名称的命名空间
namespace
{
	int a; //相当于static int a;
}
```

using关键字

``` c++
//using编译指令
using namespace name 
//use声明，在函数内使用会有二义性，声明原则比编译指令高，
using name 
```

## 强类型枚举（enum class）

### 一、传统enum的问题

``` c++
// 传统枚举的问题
enum Color { Red, Green, Blue };
enum TrafficLight { Red, Yellow, Green }; // 错误！Red, Green 重定义

Color c = Red;
TrafficLight t = Red; // 冲突！

int i = Red; // 隐式转换为 int - 可能不是我们想要的
Color c2 = 1; // 隐式从 int 转换 - 危险！
```

### 二、强类型枚举的语法和基本用法

```c++
// 定义方法
enum class EnumName {
    enumerator1,
    enumerator2,
};

// 或者使用 struct（效果完全相同）
enum struct EnumName {
    enumerator1,
    enumerator2,
};
```

基本示例

```c++
#include <iostream>

// 定义强类型枚举，比传统枚举多了class关键字
enum class Color { Red, Green, Blue };
enum class TrafficLight { Red, Yellow, Green }; 

int main() {
    // 必须使用作用域初始化变量
    Color c = Color::Red;    
    TrafficLight t = TrafficLight::Red; 
    
    // 错误使用方法
    int i = Color::Red; // 不能隐式转换为 int
    Color c2 = 1;       // 不能从 int 隐式转换
    
    // 显示转换
    Color c3 = static_cast<int>(i); 
    
    return 0;
}
```

### 三、强类型枚举的高级特性

指定底层类型

- 可以显式指定枚举的底层存储类型，这对于内存优化和互操作性很重要。

```c++
// 指定底层类型
enum class Color : uint8_t { Red, Green, Blue };        // 1字节存储
enum class Flags : uint32_t { Read = 1, Write = 2, Execute = 4 }; // 4字节存储

// 检查大小
static_assert(sizeof(Color) == 1, "Color should be 1 byte");
static_assert(sizeof(Flags) == 4, "Flags should be 4 bytes");
```

前向声明

- 由于底层类型确定，强类型枚举支持前向声明。

```c++
// 前向声明
enum class A : int;  // 底层类型必须指定

// 后续定义
enum class A : int {
    Ok,
    Error,
    Pending
};
```

自定义枚举值

- 可以显式设置枚举值，支持位运算模式。

```c++
enum class FilePermissions : uint8_t {
    Read = 1 << 0,    // 0000 0001
    Write = 1 << 1,   // 0000 0010  
    Execute = 1 << 2, // 0000 0100
    All = Read | Write | Execute
};

// 使用
auto perms = FilePermissions::Read | FilePermissions::Write;
```

## 静态方法

1. 静态方法只能访问静态变量
2. **慎用**：过度使用静态方法可能导致代码难以测试或违反面向对象设计原则。

**应用场景1**：工具函数/工具类

- 提供与类相关但不需要实例的功能（如数学计算、字符串处理）
- 不使用类中的变量，方法，必须要的数据可通过参数提供

**应用场景2**：工厂类

- 返回当前实例

``` c++

```

**应用场景3**：单例模式

- 控制类只能有一个实例，并提供全局访问点。

``` c++
class AAA 
{
    static AAA * instance; // 静态对象
public:
    static AAA * Singleton() {
        if (!instance) {
            instance = new AAA();
        }
        return instance;
    }
};

AAA * AAA::instance = nullptr;
```

## Lambda表达式

### 一、格式

格式：`[捕获列表](参数列表) mutable noexcept -> 返回类型 { }`

最简单的 Lambda

```c++
// 最简单的 lambda - 没有参数，没有返回值
auto lambda1 = [] {
    std::cout << "Hello Lambda!" << std::endl;
};
lambda1();  // 调用

// 带参数的 lambda
auto lambda2 = [](int x, int y) {
    return x + y;
};
int result = lambda2(3, 4);  // result = 7
```

### 二、注意事项

lambda定义位置的影响

``` c++
int x = 10, y = 20; 

// 注意00：在lambda定义之前修改变量会影响
x = 100;

auto lambda = [x, y]() { ... }; // 定义

// 注意01：在lambda 定义后修改变量不影响lambda内的副本
x = 100; 

lambda();  // 输出: x = 100, y = 20
```

避免默认捕获

```c++
// ❌ 不推荐：可能意外捕获不需要的变量
auto bad_lambda = [&]() { /* 可能意外修改外部变量 */ };

// ✅ 推荐：显式列出需要捕获的变量
int x = 1, y = 2;
auto good_lambda = [&x, y]() { /* 明确知道捕获了哪些变量 */ };
```

注意生命周期问题

```c++
std::function<void()> create_lambda() {
    int local_var = 42;
    
    // ❌ 危险：返回的 lambda 捕获了局部变量的引用
    return [&local_var]() { std::cout << local_var; };
    
    // ✅ 安全：值捕获
    return [local_var]() { std::cout << local_var; };
}
```

性能考虑

```c++
// 小 lambda - 通常内联，无性能开销
auto small_lambda = [](int x) { return x * x; };

// 大 lambda - 考虑使用 std::function 包装
std::function<int(int)> func = [](int x) {
    // 复杂的实现...
    return x * x;
};
```

### 三、捕获列表详解

#### Ⅰ、值捕获 `[=]`

- 注意：值捕获不能修改变量的值

```c++
int x = 10, y = 20; // 外部变量

// 值捕获：创建外部变量的副本
auto lambda = [x, y]() {
    std::cout << "x = " << x << ", y = " << y << std::endl;
    x = 100;  // 错误！值捕获的变量默认是 const
};

lambda();  // 输出: x = 10, y = 20
```

#### Ⅱ、引用捕获 `[&]`

- 注意：引用捕获可以修改变量的值

```c++
int x = 10, y = 20;

auto lambda = [&x, &y]() {
    x = 100;  // 修改会影响外部变量
    y = 200;
};

lambda(); // 输出: x = 100, y = 200

x=300;
lambda(); // 输出: x = 300, y = 200
```

#### Ⅲ、混合捕获

```c++
int a = 1, b = 2, c = 3, d = 4;

// a 值捕获，b 引用捕获，
// lambda内部c 和 d 不能访问
auto lambda1 = [a, &b]() {
    std::cout << a << ", " << b << std::endl;
};

// a 值捕获
// 其他所有变量引用捕获
auto lambda2 = [a, &]() {
    std::cout << a << ", " << b << ", " << c << std::endl;
};

// a 引用捕获，
// 其他所有变量值捕获  
auto lambda3 = [&a, =]() {  // C++20 之前使用 [&a, b, c, d]
    std::cout << a << ", " << b << ", " << c << std::endl;
};
```

#### Ⅳ、初始化捕获

```c++
// 在捕获时初始化变量
int x = 10;

// 创建副本并重命名
auto lambda1 = [value = x + 1]() {
    return value;  // 11
};

// 移动语义
auto unique_ptr = std::make_unique<int>(42);

auto lambda2 = [ptr = std::move(unique_ptr)]() {
    return *ptr;
};
```

### 四、`mutable` 关键字

默认情况下，值捕获的变量在 lambda 内是 `const` 的，使用 `mutable` 可以修改：

```c++
int counter = 0;

// 没有 mutable - 错误
// auto lambda1 = [counter]() { counter++; };  // 编译错误

// 有 mutable - 正确（但修改的是副本）
auto lambda2 = [counter]() mutable {
    counter++;
    std::cout << "内部 counter: " << counter << std::endl;
};

lambda2();  // 输出: 内部 counter: 1
lambda2();  // 输出: 内部 counter: 2
std::cout << "外部 counter: " << counter << std::endl;  // 输出: 外部 counter: 0
```

### 五、返回类型推导和指定

#### Ⅰ、自动类型推导

```c++
// 编译器自动推导返回类型
auto square = [](int x) { return x * x; };           // 返回 int
auto greet = [](const std::string& name) {           // 返回 std::string
    return "Hello, " + name;
};
```

#### Ⅱ、显式指定返回类型

```c++
// 需要显式指定返回类型的情况
auto complex_lambda = [](int x) -> double {
    if (x > 0) return x * 1.5;
    else return x * 0.5;  // 没有 -> double 可能推导为 int
};

// 返回复杂类型
auto make_vector = []() -> std::vector<int> {
    return {1, 2, 3, 4, 5};
};
```

### 六、泛型 Lambda

```c++
// 使用 auto 参数
auto generic_lambda = [](auto x, auto y) {
    return x + y;
};

// 可以用于任何支持 + 操作的类型
generic_lambda(1, 2); // 3
generic_lambda(1.5, 2.5); // 4.0
generic_lambda("a", "b"); // "ab"
```

### 七、constexpr Lambda

```c++
// 可以在编译期求值的 lambda
constexpr auto square = [](int n) constexpr -> int {
    return n * n;
};

constexpr int result = square(5);  // 编译期计算
static_assert(square(5) == 25, "Compile-time calculation");
```

### 八、模板 Lambda 和新捕获

```c++
// 模板 lambda（比 auto 更强大）
auto template_lambda = []<typename T>(const std::vector<T>& vec) {
    return vec.size();
};
```

### 九、this捕获

``` c++
// 捕获 this 的改进
class MyClass {
    int value = 42;
public:
    auto get_lambda() {
        // C++20: [*this] 捕获当前对象的副本
        return [*this]() { return value; };
    }
};
```

## Const常用方法

### 一、常量变量

``` c++
const int MAX_SIZE = 100;
const double PI = 3.14159;
const char* const NAME = "Constant Name";  // 指针和指向的内容都是常量

// 对象常量
const std::string GREETING = "Hello";
const std::vector<int> EMPTY_LIST{};
```

### 二、常量成员函数

- const定义的函数不能修改普通的类成员变量

``` c++
class MyClass 
{
private:
    // 2种类型变量，在不同的情况下的使用
    int value;
    mutable int cache;
    
public:
    // 情况一：不能修改成员变量，const成员函数
    int getValue() const {
        value = 10;  // 错误！不能修改成员变量
        return value;
    }
    
    // 情况二：可以修改mutable成员
    int getCachedValue() const {
        cache++;  // 允许，因为cache是mutable
        return cache;
    }
};
```

关于其他需要注意的使用方法

- const对象只能调用const定义的函数

``` c++
// 假设MyClass类中有方法setValue()方法

const MyClass A();  // const 对象
int x = A.getValue();  // 正确：可以在const对象上调用const函数
A.setValue(200);    // 错误：不能在const对象上调用非const函数

MyClass B();  // 非const对象
B.getValue();       // 正确：也可以在非const对象上调用const函数
B.setValue(300);    // 正确
```

### 三、常量参数

值传递

```C++
void printValue(const int value) 
{
    value = 10;  // 错误！value是常量
    std::cout << value << std::endl;
}
```

引用传递（推荐）

```c++
void processString(const std::string & str) 
{
    str.clear();  // 错误！不能修改str
    std::cout << "Length: " << str.length() << std::endl;
}
```

指针参数

```c++
// 指针，传递数组，需要同时传递数组个数
void processData(const int* data, int size) 
{
    *data = 10;  // 错误！不能通过data修改内容
}
```

### 四、常量返回值

#### Ⅰ、普通的返回值

- 返回const值通常没有实际意义，因为返回值本身就是副本。

定义

``` c++
// 定义
class Example 
{
private:
    int data = 42;
public:
    // 返回const值 - 通常没有实际意义
    // getValueAsConst() const：getValueAsConst()函数中不会修改类变量
    const int getValueAsConst() const {
        return data;
    }
};
```

使用方法

```c++
int main() 
{
    Example obj;
    
    // 正确使用方法一
    const int val1 = obj.getValueAsConst();  
    
    // 正确：可以复制到非const变量
    int val2 = obj.getValueAsConst();        
    val2 = 100;  // 可以修改副本
    
    // 直接使用，正确
    std::cout << obj.getValueAsConst() << std::endl;  
    
    return 0;
}
```

#### Ⅱ、返回const引用

定义

``` c++
class Student 
{
private:
    std::string name;
    int age;
    static const std::string defaultSchool;
    
public:
    Student(const std::string& n, int a) : name(n), age(a) {}
    
    // 返回const引用 - 防止外部修改内部数据
    const std::string & getName() const 
    {
        return name;
    }
    
    // 返回静态成员的const引用
    static const std::string & getDefaultSchool() 
    {
        return defaultSchool;
    }
    
    // 不要返回局部变量的引用 - 危险！
    const std::string & getNameUpperCase() const 
    {
        std::string upper = name;
        return upper;  // 错误！返回局部变量的引用
    }
};

// 静态成员定义
const std::string Student::defaultSchool = "ABC School";
```

使用方法

``` c++
int main() {
    Student A("Alice", 20);
    
    // 使用const引用
    const std::string & nameRef = A.getName();  // 正确
    std::cout << nameRef << std::endl;          // 正确：读取
    nameRef = "Bob";  // 错误！不能通过const引用修改
    
    // 可以复制到非const变量进行修改
    std::string nameCopy = A.getName();
    nameCopy = "Bob";  // 正确：修改的是副本
    
    // 使用静态成员的const引用
    const std::string & school = A::getDefaultSchool();
    
    return 0;
}
```

#### Ⅲ、返回const指针

定义

``` c++
class DataContainer 
{
private:
    int* data;
    int size;
    
public:
    DataContainer(int s) : size(s) {
        data = new int[size]{1, 2, 3, 4, 5};
    }
    
    // 返回const指针 - 防止外部修改指向的数据
    const int* getData() const 
    {
        return data;
    }
    
    // 返回指向const的指针
    int* const getMutableData() 
    {
        return data;  // 指针本身是const，但指向的数据可修改
    }
};
```

使用方法

``` c++
int main() {
    DataContainer container(5);
    
    // 使用const指针
    const int* dataPtr = container.getData();
    std::cout << dataPtr[0] << " ";  // 正确：读取
    dataPtr[0] = 10;  // 错误！不能通过const指针修改数据
    
    // 可以复制数据到非const数组进行修改
    int copy[5];
    std::copy(dataPtr, dataPtr + 5, copy);
    copy[0] = 100;  // 正确：修改的是副本
    
    return 0;
}
```

### 五、常量指针和指针常量

- 更详细参考：C语言 - 基本运算符 - 十、const限定符
- `const`在`*`左侧：\*p不可修改
- `const`在`*`右侧，p不可修改

```c++
int main() 
{
    int value = 10;
    int another = 20;
    
    // 指向常量的指针 - 指针可以改变，指向的内容不能改变
    const int* ptr1 = &value;
    *ptr1 = 30;  // 错误！
    ptr1 = &another;  // 正确
    
    // 指针常量 - 指针不能改变，指向的内容可以改变
    int* const ptr2 = &value;
    *ptr2 = 30;      // 正确
    ptr2 = &another;  // 错误！
    
    // 指向常量的指针常量 - 都不能改变
    const int* const ptr3 = &value;
    *ptr3 = 40;      // 错误！
    ptr3 = &another; // 错误！
    
    return 0;
}
```

### 六、常量迭代器

```c++
#include <vector>

void processVector(const std::vector<int>& vec) 
{
    // 常量迭代器
    for (std::vector<int>::const_iterator it = vec.begin(); 
         it != vec.end(); ++it) {
        // *it = 10;  // 错误！不能修改元素
        std::cout << *it << " ";
    }
    
    // C++11 简化写法
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
}
```

### 七、常量与函数重载

```c++
class Array 
{
private:
    int* data;
    int size;
    
public:
    // const版本 - 用于const对象
    const int& operator[](int index) const {
        std::cout << "const operator[]" << std::endl;
        return data[index];
    }
    
    // 非const版本 - 用于非const对象
    int& operator[](int index) {
        std::cout << "non-const operator[]" << std::endl;
        return data[index];
    }
};

int main() {
    Array arr1;
    const Array arr2;
    
    arr1[0] = 10;    // 调用非const版本
    int value = arr2[0];  // 调用const版本
    
    return 0;
}
```

### 八、类中的常量成员

- 类中的常量成员，要么在定义时初始化，要么使用初始化列表赋值

```c++
class Circle 
{
private:
    const double PI = 3.14159;  // C++11 类内初始化
    const int id;
    
public:
    // const id使用初始化列表中初始化
    Circle(int circleId) : id(circleId) 
    {  
        id = circleId;  // 错误！不能在构造函数体内初始化
    }
};
```

### 九、常量表达式 (constexpr)

```C++
// 编译时常量
constexpr int ARRAY_SIZE = 100;
constexpr double CalculateArea(double r) 
{
    return 3.14159 * r * r;
}

int main() {
    int arr[ARRAY_SIZE];  // 编译时确定大小
    constexpr double area = CalculateArea(5.0);  // 编译时计算
    
    return 0;
}
```

#### 16、const修饰

①、常函数

- 限制修改类属性的值

``` c++
class Person{
    // 加了mutable，就可以修改
	mutable int B;
	int a;
    //常函数，不允许修改类的成员属性
	void showInfo() const {
        // 错误，不能修改
		this->a = 100;
        // 正确，mutable是可以修改的
        this->B = 100;
	}
}
```

②、常对象

- 常对象可以调用常函数，不能调用普通方法

``` c++
class Person{
	mutable int B;
	int a;
    //常函数，不允许修改类的成员属性
	void showInfo() const {
        // 错误，不能修改
		this->a = 100;
        // 正确，mutable是可以修改的
        this->B = 100;
	}
    // 普通方法
    void func(){...}
}

const Person p2; 
p2.a = 100; // 错误，不能修改
p2.B = 100; //正确，mutable修饰，可以修改
cout << p2.name // 可以读
    
const Person p3;
p3.func(); // 错误，不能调用
p3.showInfo();// 正确，可以调用常函数
```

## 智能指针

1. `unique_ptr`、`shared_ptr`、`weak_ptr`：自动管理内存，避免内存泄漏。

2. 注意：因为是自动管理内存，不需要手动释放（不用析构函数）

3. 手动放弃所有权需要手动释放

   ``` c++
   void risky() {
       auto A = std::make_unique<int>(42);
       int* raw_ptr = A.release();  // 放弃所有权，需手动管理 ❗
       delete raw_ptr;  // 必须手动释放，否则内存泄漏！
   }
   ```

### 一、`std::unique_ptr` - 独占所有权

- **优先使用 `unique_ptr`** - 最轻量，无引用计数开销

``` c++
// 创建 unique_ptr
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
// 移动语义（所有权转移），不能使用=赋值
std::unique_ptr<MyClass> ptr2 = std::move(ptr1);

// 双重指针（几乎无用，违背 unique_ptr 设计初衷）
std::unique_ptr<TStateInterface> * a = std::make_unique<TStateInterface>;

// 创建动态数组
std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
arr[0] = 42;
arr[1] = 24;

// 或者使用自定义删除器
auto deleter = [](int* p) {
    delete[] p;
};
std::unique_ptr<int[], decltype(deleter)> arr2(new int[5], deleter);
```

### 二、`std::shared_ptr` - 共享所有权

``` c++
// 创建 shared_ptr（推荐使用 make_shared）
std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>();
// 共享所有权
std::shared_ptr<Resource> ptr2 = ptr1;
```

### 三、`std::weak_ptr` - 弱引用

- **避免循环引用** - 使用 `weak_ptr` 打破循环

``` c++
std::shared_ptr<int> shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;

```

## 范围循环for auto

### 一、遍历Vector容器

1. 要使用vector的下标，需要最朴素的for遍历方法
2. for auto不能获取下标

``` c++
std::vector<int> i; //定义一个vector容器

// 修改你正在迭代的容器的值，或者你想避免拷贝大的对象
for(auto &it : num) {
    cout << it << endl;
}
// it 用于捕获vector里面的值
for(auto it :num) {
    cout << it << endl;
}
```

### 二、遍历map容器

``` c++
map<int, int> num_map;      
num_map[2] = 4;
num_map[4] = 5;

for(auto &it : num_map) {       
    cout << it.first << endl; // 输出key
    cout << it.second << endl;// 输出value
}
```

## 尾随返回类型（C11）

### 一、处理复杂类型

1. 特别是依赖函数参数的类型
2. 这是尾随返回类型**最主要的价值**。

**问题场景**：

```c++
// 我们想要一个函数，返回两个参数乘积的类型
// 但 a 和 b 的类型在参数列表中，传统语法无法在返回类型位置使用它们
template<typename T, typename U>
???  multiply(T a, U b) {  // 这里应该写什么返回类型？
    return a * b;
}
```

**尾随返回类型的解决方案**：

```c++
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// 使用
auto result1 = multiply(3, 4.5);     // double
auto result2 = multiply(3.0f, 4L);   // long? float? 编译器自动推导
```

### 二、函数指针类型作为返回类型

**传统语法的复杂性**：

```c++
// 一个返回"函数指针"的函数，该函数指针指向一个接受int返回int的函数
int (*getFunction())(int) {
    return some_function;
}
// 非常难以阅读！
```

**尾随返回类型的清晰写法**：

```c++
auto getFunction() -> int (*)(int) {
    return some_function;
}
// 或者结合decltype更清晰
auto getFunction() -> decltype(&some_function) {
    return some_function;
}
```

### 三、类成员函数中引用类自身类型

- **在类内部定义返回自身类型或嵌套类型的成员函数** 

```c++
class Container {
public:
    // 传统语法：错误！Container在返回类型位置还不完整
    // Container begin(); // 可能编译错误
    
    // 尾随返回类型：正确！此时Container已经是完整类型
    auto begin() -> Container;
    
    // 对于嵌套类型尤其有用
    class Iterator;
    auto getIterator() -> Iterator;  // 清晰！
};
```

### 四、 提高复杂返回类型的可读性

- 当返回类型很长时，尾随语法让函数名更突出：

```c++
// 传统语法：函数名被埋在类型中间
std::vector<std::pair<std::string, int>> createMapping();

// 尾随返回类型：函数名在开头，清晰可见
auto createMapping() -> std::vector<std::pair<std::string, int>>;
```

### 实际应用场景

场景1：Lambda 表达式

- Lambda 表达式的语法实际上就是尾随返回类型的简化形式：

```c++
// Lambda 的返回类型推导就是尾随语法
auto lambda = [](int x, int y) -> double {
    return (x + y) * 1.0;
};
```

场景2：SFINAE 和模板元编程

```c++
template<typename T>
auto process(T&& value) 
    -> typename std::enable_if<std::is_integral<T>::value, void>::type {
    // 仅对整数类型启用
}

template<typename T>
auto process(T&& value)
    -> typename std::enable_if<std::is_floating_point<T>::value, void>::type {
    // 仅对浮点类型启用
}
```

场景3：现代 C++ 中的完美转发

```c++
template<typename Func, typename... Args>
auto invoke(Func&& f, Args&&... args)
    -> decltype(std::forward<Func>(f)(std::forward<Args>(args)...)) {
    return std::forward<Func>(f)(std::forward<Args>(args)...);
}
```

## 新增关键字

### 一、auto

``` c++
auto a = 1; // 
auto & b = 12;
const auto c = 22;

/* 使用auto作为函数返回值类型时，要使用尾随返回类型 */
auto add(int x, int y) -> int 
{
    return x+y;
}
auto a = add(1,2);
```

初始化列表的自动推导新规则（C17）

``` c++
// 在C++17以前的版本会把{}推断为initializer_list<>类型
auto x_1 {3}; // x_1类型为int
auto x_2 {3.0}; // double
auto x_3 = {1,2,3}; // 类型为std::intializer_list<int>类型
auto x_4 {1,2,3}; // 错误，必须是单一元素
auto x_5 {1, 2.0, 3.0}; // 错误，数值类型不同
```

### 二、decltype-类型说明符

- 用于**查询表达式或实体的类型**。它的名字来源于 "declare type"（声明类型）。
- decltype会自动变成预期类型

``` c++
int x = 10;
decltype(x) a;        // a 的类型是 int

const int y = 20;
decltype(y) b;        // b 的类型是 const int  

int& ref = x;
decltype(ref) c = x;  // c 的类型是 int&，必须初始化

const int& cref = y;
decltype(cref) d = y; // d 的类型是 const int&，必须初始化

std::vector<int> vec;
decltype(vec) e;      // e 的类型是 std::vector<int>
decltype(vec.size()) f; // f 的类型是 std::vector<int>::size_type（通常是size_t）

const int x = 0;
decltype(auto) x2 = x; // x2类型为const int 
```

与auto一起使用

``` c++
auto add(int x, int y) -> decltype(x+y) 
{
    return x+y;
}
auto a = add(1,2);
```

### 三、type alias-类型别名

### 四、attribute-属性

- 允许程序员向编译器指定附加信息以强制执行约束

### 五、constexpr

- `constexpr` 表示 **常量表达式**，用于声明在**编译时**就能计算出结果的变量或函数。
- 比 `#define` 宏更安全，有类型检查，应优先使用constexpr

基本常量定义

```c++
// ❌ 避免
#define MAX_SIZE 1024
#define PI 3.14159

// ✅ 推荐
constexpr int MaxSize = 1024;
constexpr double Pi = 3.14159;
constexpr auto AppName = "MyApplication";
```

函数式常量

```c++
// ❌ 避免
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// ✅ 推荐
constexpr auto square(auto x) { return x * x; }
constexpr auto max(auto a, auto b) { return a > b ? a : b; }
```

`constexpr` 变量必须用常量表达式初始化：

- 常量不能赋值，constexpr相当于常量

```c++
constexpr int a = 10;            // ✅ 正确
constexpr int b = a + 5;         // ✅ 正确

int x = 10;
// constexpr int c = x;          // ❌ 错误：x 不是常量表达式

constexpr int d = sizeof(int);   // ✅ 正确：sizeof 是常量表达式
```

C++11 中`constexpr` 函数的限制

- 函数体只能包含单个 `return` 语句
- 不能有变量、循环、条件语句（除了 `?:`）

```c++
// C++11 风格的 constexpr 函数
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);  // 只能递归
}

constexpr int square(int x) {
    return x * x;  // 单条 return 语句
}
```

C++14 中`constexpr` 函数的限制

- 可以有局部变量（但不能是 `static` 或 `thread_local`）
- 可以有循环和条件语句
- 可以有多个语句

```c++
// C++14 风格的 constexpr 函数
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

constexpr int power(int base, int exp) {
    if (exp == 0) return 1;
    int result = 1;
    while (exp-- > 0) {
        result *= base;
    }
    return result;
}
```

C++17/20 的进一步增强

- C++17：支持 `if constexpr`
- C++20：支持虚函数、异常、动态内存分配等

```c++
// C++17: constexpr if
template<typename T>
constexpr auto get_value(const T& t) {
    if constexpr (std::is_pointer_v<T>) {
        return *t;  // 编译期条件分支
    } else {
        return t;
    }
}
```

### 六、explicit

- `explicit` 是一个关键字，用于防止编译器进行隐式的类型转换。它主要用在构造函数和转换运算符上，要求必须显式地进行类型转换。
- 不应该使用 `explicit` 的情况：
  1. **多参数构造函数**（没有隐式转换风险）
  2. **拷贝构造函数和移动构造函数**
  3. **确实需要隐式转换的类**（如字符串类）
- 应该使用 `explicit` 的情况：
  1. **单参数构造函数**（现在包括多参数有默认值的构造函数）
  2. **转换运算符**（特别是 `operator bool()`）
  3. **资源管理类**（文件句柄、智能指针等）
  4. **数值包装类**（单位、范围限制等）

简单直观的使用建议

```c++
class GoodDesign {
public:
    // 多参数构造函数 - 不需要 explicit
    GoodDesign(int a, int b, int c) : a(a), b(b), c(c) {}
    
    // 单参数构造函数 - 应该使用 explicit
    explicit GoodDesign(int value) : a(value), b(value), c(value) {}
    
    // 转换运算符 - 应该使用 explicit
    explicit operator bool() const { return a != 0; }
    
    // 拷贝构造 - 不需要 explicit
    GoodDesign(const GoodDesign&) = default;
    
private:
    int a, b, c;
};
```

### 七、noexcept

- 用于标识函数不会引发任何异常

### 八、inline-内联命名空间

- 内联命名空间中的内容会被视为在外层命名空间中直接可见。

**内联命名空间的主要价值**：

| 应用场景     | 优点                       |
| :----------- | :------------------------- |
| **版本控制** | 无缝升级，保持向后兼容     |
| **ABI 管理** | 同时提供稳定和实验性接口   |
| **实现隐藏** | 简化用户接口，隐藏复杂细节 |
| **库演化**   | 管理不同配置或变体         |

使用样例：

``` c++
namespace MyLibrary {
    // 使用了inline关键字，v1命名空间为默认使用的类
    inline namespace v1 {
        class A { ... }
    }
    
    // 尚未内联，用户需要显式选择
    namespace v2 {
        class A { ... }
    }
}

int main() {
    // 默认使用最新版本（v1）
    MyLibrary::A p1;
    p1.process();  // 假定A中有方法process() 
   
    // 如果想用 v2，需要显式指定
    MyLibrary::v2::A p2;
    p2.process();  // 假定A中有方法process() 
    
    return 0;
}
```

### 九、explicit-说明符（C20）

- 编译时可以有条件的选择构造函数是否为显示构造

### 十、constinit

- 用于确保变量在编译或程序启动时完成静态初始化
- 使用consteval的函数，可以使用constinit定义的变量赋值

constinit主要用于：

- **避免静态初始化顺序的问题**
- **线程局部存储**
- **编译期默认值 + 运行时覆盖**（单例模式的实例指针，在编译期实例指针为nullptr，所以可以使用constinit）
- **性能关键的全局/静态变量（需要快速初始化的性能敏感变量）** 

运行时初始化的变量**不推荐使用**constinit，例如：

- 函数返回值 ❌
- 静态变量值需要在运行时从其他位置获取（没有初始化为nullptr，当然这些变量可以初始为nullptr，也是可以使用constinit）❌
- 动态分配，`constinit static auto ptr = new MyClass(); `  ❌

const与constexpr区别

1. const主要用于定义函数参数，定义常量函数
2. constexpr感觉是#define功能的替换，主要用于C++，在C中使用constexpr

| 关键字      | 作用时期     | 主要用途                   | 是否必须初始化 | C++标准 |
| :---------- | :----------- | :------------------------- | :------------- | :------ |
| `const`     | 主要运行时   | 表示运行时不可修改         | 是             | C++98   |
| `constexpr` | 编译期       | 编译期常量/函数            | 是             | C++11   |
| `consteval` | 编译期       | 立即函数（必须编译期求值） | 是             | C++20   |
| `constinit` | 编译期初始化 | 保证静态变量编译期初始化   | 是             | C++20   |

什么时候用什么

1. **默认使用 `constexpr`** - 对于能在编译期确定的值
2. **需要强制编译期求值时用 `consteval`** - 特别是元编程和反射
3. **全局/静态变量用 `constinit`** - 避免静态初始化问题，默认使用constinit，当编译器错误时，再使用普通静态变量
4. **运行时常量用 `const`** - 当值在运行时才能确定时

### if constexpr语句

- if constexpr允许基于常量表达式的分支编译，if constexpr会丢弃不适用的分支代码，只编译为true的代码

``` c++
if constexpr(condition)
{
    // 判断条件为true时编译
} else {
    // 判断条件为false时编译
}
```

## C++11新增语言功能

### 静态断言

在编译程序时编译器会检查断言

``` c++
/* 编译器会检查size是否>3，若给为假，则显示提示内容 */
static_assert(Size>3, "vector size sis too small");
```

### 空指针

1. 使用NULL有明显缺陷，编译器会将其值定义为0，而使用nullptr就不会有这样的问题

### 左值引用和右值引用

``` c++
int x = 0; // x是左值
int & x_1 = 0; // x_1是左值引用
int && x_2 = x; // 编译错误，x是左值，x_2是右值引用
int && x_3 = 0; // x_3是右值引用，绑定到0
```

### 非静态数据成员初始化器

- 使用{}或=进行成员初始化

### 右尖括号

- 在C++11版本以前`>>`是错误的，2个`>`中间必须有空格

### char32_t和char16_t

- char32_t表示32位宽字符，无符号整型数据
- char16_t表示16位宽字符，无符号整型

### 原始字符串文本

``` c++
int main()
{
    string s1 = R"(HEllo.\n)"; // 输出HEllo.\n
    string s2 = R"(\n\n)"; // 输出\n\n
}
```

## C++14新增语言功能

### 一、二进制文本

``` c++
int a = 0b0000111; // 二进制文本以“ob”开头
int b = 0B0000111; // 二进制文本以“0B”开头
```

### 二、变量模板

- 可以定义参数化常量

### 三、返回类型推导

## C++17新增语言功能

### 二、内联变量（inline）

- 可以直接使用inline对静态变量进行初始化

``` c++
class myClass
{
    inline static int var = 10; // 直接进行复制
}
```

### 三、嵌套命名空间

- 命名空间可以嵌套

### 四、结构化绑定

``` c++
// 格式：auto [x,y,z] = expr;
int a[2] = {1,2};

auto [x,y] = a; // 创建e2，然后将a复制到e,x引用e[0]，y引用e[1]
auto & [x1, x2] = a; // x1引用a[0]，x2引用a[1]
```

### 五、带初始化的选择语句

- if与switch语句简化为常用代码模式

### 七、UTF-8字符串文本

- 以u8开头的字符文本是char类型的文本

``` c++
char x = u8'x';
char8_t s2[] = u8"a毛";
```

### 八、枚举直接列表初始化

- 枚举类型可以适用{}进行初始化

``` c++
enum b: unsigned char {};
b a {0}; // 正确
b b {-1}; //错误
```

### 九、新增属性

- [[fallthrough]]、[[nodiscard]]、[[maybe_unused]]

### 十、_has_include运算符

- _has_include运算符用于#if和#elif表达式，检查头文件或源文件是否可被包含

## C++20新增加的语言功能

### 一、协程

- co_await与co_yield的函数，等等

### 二、概念

### 三、指定初始化

### 四、新增属性

- [[likely]]、[[unlikely]]属性

### 六、即时函数

- 使用consteval定义返回值的函数

### 七、枚举作用域（using enum）

### 八、char8_t

- 用于声明UTF-8无符号变量或函数，与无符号整型相同

### 
