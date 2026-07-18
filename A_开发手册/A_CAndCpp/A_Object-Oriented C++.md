# Object Oriented C++（面向对象的C++）

## 类的调用方法集合

1.  **应当使用带括号的构造方式**（`AA *a = new AA();`）

2. 有构造函数的类：不论有没有括号，都用构造函数进行初始化；

3. 没有构造函数的类：

    不加括号的new只分配内存空间，不进行内存的初始化`AA *a = new AA;`;

    加括号的new会在分配内存的同时初始化为0  `AA *a = new AA();`

类方法调用（栈中创建）

``` C++
// WorkManager自定义类
class WorkManager{ ... };

// 方法一，拷贝构造
WorkManager worker = WorkManager();
// 方法二，默认构造，没有参数
WorkManager worker;

//调用
worker.print_title();
```

指针方法调用（堆中创建）

``` c++
// WorkManager自定义类
class WorkManager{ ... }

WorkManager * worker = new WorkManager();
worker->print_title();
```

## 构造函数

### 一、默认/参数构造

``` c++
class NPC 
{
    //! 无参构造方法,与类名相同,自动调用
	NPC();
    //! 有参构造方法
    NPC(int a);
}
```

调用方法：

``` c++
// 默认构造函数
NPC p1; 
// 有参数构造函数
NPC p2(10); 
```

### 二、拷贝构造

- 拷贝构造创建的对象与原对象是值相同，但内存位置不同的关系

``` c++
class NPC 
{
    // 拷贝构造，固定写法，需要类名、&、const
	NPC(const NPC &n);
    // 拷贝赋值运算符
    NPC & operator=(const MyClass& other);
}
```

调用拷贝构造：

``` c++
NPC p; // 普通

NPC p2 = p; // 拷贝构造，调用的是拷贝运算符
NPC p3(p2); // 拷贝构造

MyClass base;
MyClass arr[3] = {base, base, base};  // 拷贝构造函数调用3次

// 在函数调用时直接传递对象，都是调用拷贝构造
void processObject(MyClass obj) { ... }

// 值返回时也是拷贝构造（没有RVO优化的时候）
MyClass createObject() 
{
    MyClass obj;
    return obj;  // 可能调用拷贝构造函数
}
```

### 三、移动构造

- 移动构造使用右值引用和移动语义（即指向内存中已经存在的对象）

``` c++
class A
{
    // 移动构造
    A(A && obj);
}
```

### 四、现代C++建议

决策流程：

```text
是否需要自定义析构函数？
    ├── 否 → 使用默认的所有函数
    └── 是 → 
          ├── 是否需要深拷贝？
          │     ├── 否 → 可能不需要拷贝函数
          │     └── 是 → 需要同时定义拷贝构造和拷贝赋值
          │
          └── 是否禁止拷贝？
                ├── 否 → 考虑移动语义
                └── 是 → 删除拷贝构造和拷贝赋值
```

所以函数举例：

```c++
class ModernClass {
public:
    // 1. 析构函数
    ~ModernClass();
    
    // 2. 拷贝构造函数
    ModernClass(const ModernClass&);

    // 3. 拷贝赋值运算符
    ModernClass& operator=(const ModernClass&);

    // 4. 移动构造函数 (C++11)
    ModernClass(ModernClass&&);

    // 5. 移动赋值运算符 (C++11)
    ModernClass& operator=(ModernClass&&);
}
```
## 析构函数

- 构造流程：先构造A的对象，再构造B的对象
- 析构流程：先析构B的对象，再构造A的对象

``` c++
class NPC 
{
    // 析构方法，与类名相同，自动调用
	~NPC();
}
```

## 深拷贝和浅拷贝

- 浅拷贝：并没有正在的拷贝，而是用指针指向了同一块空间，是由于析构（释放）内存时，浅拷贝在第一次就把资源释放，第二次释放就出错了
- 深拷贝：在堆中重新申请空间

``` c++
NPC(const NPC & N){
    // 自己在构造时自定义一个
    m_Height = new int(*N.m_Height)
}
~NPC(){
    if(m_Height !=NULL){
        delete m_Height;
    }
}
```

## 初始化列表

使用参数构造函数时，可以使用初始化列表定性成员变量的初始化

``` c++
class Point
{
    int x;
public:
    Point(int i): x(i){}
}
```

常量成员变量必须使用初始化列表进行初始化

``` c++
class TestA
{
    const int t;
public:
    TestA(int b): t(b){}
}
```

引用成员变量必须使用初始化列表进行初始化

``` c++
class TestB
{
    int &t;
public:
    TestB(int b): t(b){}
}
```

参数化的基类必须使用初始哈列表进行初始化

``` c++
class A // 基类
{
    A(int a){};
}; 

class B: public A
{
    B(int x): A(x){}; // 初始化基类的参数
}
```

## 静态相关内容

### 一、静态成员变量

1. 所有静态成员共享同一份数据
2. 静态变量在编译的时候就已经创建，且值为0
3. **必须类内声明，并在类外初始化**，使用前必须初始化
4. **静态数据成员不属于某个对象，在为对象分配空间中不包括静态成员所占空间**
5. 可以在程序的任意位置访问，赋值

定义方法：

``` c++
class A 
{
public:
    // 类内只能声明，类外初始化
	static int m_age; 
    static int *b; 
}

/* 类外初始化加定义 */
// 且不用加static
int A::m_age = 100;
int * A::b = 200;
```

使用方法

``` c++
// 方法二，直接通过类名访问（常用）
A::m_age = 300;

// 方法一，通过对象访问（与普通类使用方法一样普通方法）
A value;
value.m_age = 200;
```

### 二、静态方法

1. 静态方法只能操作**静态变量、其他静态方法**
2. 静态方法没有 this 指针
3. 类中普通方法可用调用静态方法
4. 静态方法也是**全局可用，内存中只有一份**

定义方法：

``` c++
class A 
{
public:
    // 静态成员函数只能访问静态成员变量
	static void func(); 
}

void A::func()
{
    // 其中不能使用非静态成员变量
}
```

使用方法：

``` c++
// 调用一，通过对象
A a;
a.func();

// 调用二，通过类名(常用)
A::func();
```

### 三、静态与非静态方法调用

- 非静态方法调用静态方法（查看**静态成员变量、静态方法**）
- 静态方法不能直接调用非静态方法

#### Ⅰ、静态工厂方法

``` c++
class User
{
    // 非静态方法
    void displayInfo() const {  }
    
    // 静态工厂方法 - 创建对象并返回
    static User createUser(const std::string& name) {
        User newUser(name);          // 创建新对象
        newUser.displayInfo();       // 通过对象调用非静态方法
        return newUser;
    }
}

// 调用方法
User alice = User::createUser("Alice");
```

#### Ⅱ、对象指针调用

``` c++
class A
{
    // 非静态方法
    void displayInfo() const {  }
    
    // 静态方法通过对象指针调用非静态方法
    static void processUser(User * user) {
        user->displayInfo();     // 通过指针调用
    }
}

// 通过指针调用
User bob("Bob"); // 创建对象，bob
User::processUser(& bob); // 传递指针
```

#### Ⅲ、对象引用调用

``` c++
class User
{
    // 非静态方法
    void displayInfo() const {  }
    
    // 静态方法通过对象引用调用非静态方法
    static void updateUser(User& user, const std::string& newName) {
        user.displayInfo();          // 通过引用调用
        user.name = newName;         // 修改对象
    }
}

// 通过引用调用
User charlie("Charlie");
User::updateUser(charlie, "Charles"); // 使用引用，直接传递对象即可
```

静态成员函数可以访问静态成员，在类是单例类的情况下，可以在创建的时候把this指针赋值给那个静态成员，然后在静态成员函数内部访问this指向的静态成员：

``` c++
/* A.h */
class A 
{
public:
    A();
    static void test() 
private:
    // 利用静态方法可以访问静态成员，保存一个静态变量
    static A *m_gA;
    int m_a
}

/* A.cpp */
A * A::m_gA = NULL; // 静态变量初始化

A::A(){
    A::m_gA = this; // 在类使用时就将this保存起来
}

void A::test(){
	A::m_gA.m_a += 1;
}
```

## 友元函数

- 友元函数是在类中声明的一个非成员函数，但它可以访问该类的私有(private)和保护(protected)成员。

全局函数做友元

``` c++
class Buliding 
{
    // 声明友元函数
	friend void goodGay(Buliding &bul);
private:
    double width;
}

// 定义友元函数 - 不是Box的成员函数
void goodGay(Buliding & bul)
{
	b.width = 2000;
}

// 调用
Buliding b;
goodGay(b);// 调用友元函数
```

类做友元

``` c++
class Buliding
{
    // 声明友元类是GoodGay,
	friend class goodGy;
private:
    double width;
}

// 可修改Buliding私有方法的类
class GoodGay 
{
    void visite(Buliding & b)
    {
    	b.width = 1000;
    }
}

// 调用
Buliding b;

GoodGay g;
g.visite(b); // 友元类可以修改private属性
```

成员函数做友元

``` c++
// 定义
class Buliding{
    // 告诉编译器，允许GoodGay类下的visit方法访问
	friend void GoodGay::visit()；//类做友元
}
class GoodGay {
    void visit(){  }
}
```

## 运算符重载

对已有的运算符进行重新定义，赋予另外一种功能

### 一、加法重载

通过成员函数重载

``` c++
class Person {
public:
    int a;
    int b;
    //重载+号运算
	Person operator+(Person &p){
        return this.a+ p.b;
    } 
}

// 初始值
Person p1;
p1.a = 10;
Person p2;
p2.b = 20;

// 调用
// 本质是Person p3 = p1.operator+(p2);
Person p3 = p1+p2;
```

通过全局函数重载

``` c++
class Person{
    int a;
    int b;
}
// 全局函数重载
Pserson operator+(Person &p1, Person &p2){
    return p1.a+p2.b;
}

// 初始值
Person p1;
p1.a = 10;
Person p2;
p2.b = 20;

// 调用
// 本质：Person p3 = operator+(p1, p2);
Person p3 = p1+p2;
```

### 二、左移运算符

只通过全局函数重载

``` c++
// 全局函数重载
void operator<< (ostream &cout, Person p){
    cout << p.m_a
}


// 重写左移运算符
Person p;
p.m_a = 100;
cout << p;

/* 链式调用 */
// 链式返回
ostream operator<< (ostream &cout, Person p){
    cout << p.m_a;
    return cout;
}
cout <<p <<p << endl;
```

### 三、递增运算符重载

### 四、赋值运算符重载

### 五、关系运算符重载

### 六、函数运算符重载

## 其他内容

### 一、类对象作为类成员

``` c++
class A {
    string name;
    A(string b_na){
    	name = b_na
    }
}

class B {
    A _name; // A类对象
    int _b;
    
    // 使用初始化列表赋值
    B(int a, string n):_b(a), _name(n)
    {
		//... 
    }
}

// 调用
B p(1, 'name')
```

### 二、前置声明

常见错误：

- `class “xxxx“ does not name a type` 
- `declare class does not name a type` 

产生原因：在一个源文件中，要声明或定义一个类的指针时，必须在使用前声明或定义该类

``` c++
/* 文件：A.h */
class ABCDE {...}

/* 文件：B.h */
class ABCDE; // 前置声明
class B
{	
    ABCDE *a; 
}
```

### 三、this指针

1. this指针指向被调用的成员函数（谁调用，就指向谁）
2. this指针用途：
   - 当形参和成员变量同名时，可用this区分
   - 在类的非静态成员函数中返回对象本身，可使用`return *this`

解决名称冲突

``` c++
class Person {
	int age;
    Person(int age){
        // 属性名与方法名重名
        this->age = age
    }
}
// this指针指向的时p1
Person p1(18);
```

返回类本身（可进行链式编程）

```c++
class Person
{
public:
    int age;
    // 若返回值(Person func(int a))，就不会进行累加操作
    Person & func(int a){
        this->age +=a;
        return * this
    }
}

Person p1;
p1.func(10).func(20).func(30);
```

### 四、空指针

``` c++
class Person
{
public:
    int age;
    // 若返回值(Person func(int a))，就不会进行累加操作
    void func(){
        cout << "this this kong";
    }
    void func2(){
        // 因为默认成员属性前面有this->
        // 当空指针类的时候，就变成NULL->age
        cout << age;
    }
}

Person *p1 = NULL;
p1.func(); // 没错
p1.func2();// 报错
```

### 标识符

- override、final

`= default`标识符

- 将该函数声明为显式默认函数，这使得编译器为显式默认函数生成默认实现，比手动编程的函数实现更有效
- 不是任何函数都可以使用`= default`的，必须是特殊的成员函数（默认构造、拷贝构造、析构函数等）

``` c++
class A
{
    A () = default;
}
```

`= delete`标识符

- 禁用该成员函数，信用的成员函数为显示删除
- 基本所有的函数都可以显示删除

``` c++
class A
{
    A () = delete;
}
```



## OOP三大特性

### 一、封装

1. 类和结构体的区别就是默认权限不同，struct默认为公共，class默认权限是私有

#### 1、分文件编写类

①、创建类的头文件（NPC.h）

``` c++
#ifndef __xxx
#define __xxx
class NPC 
{
    // 构造和析构，必须在public下，或者什么都每没加的地方
	NPC()；  //构造方法,与类名相同
	~NPC()； //析构方法
private:
protected:
public:
    //成员属性
	int Name；
    //定义一个方法
	void move(int a); 
}
#endif //宏定义
```

②、创建类的.cpp文件（NPC.cpp）

``` c++
// 引入头文件
#include “NPC.h” 

NPC::NPC(){} //实现构造方法
NPC::~NPC(){ //析构方法
	delete this->a; //释放空间a
} 

//::成员操作符
void NPC::move(int a){ 
	std::cout << “1”;
}
```

③、在其他文件中使用类

``` c++
// 引入类的头文件
#include “NPC.h”

int main() {
    /* 普通方法 */
	NPC n1    // 实例化
	n1.move(1) // 调用NPC类中的方法move
	
    /* 使用new方法创建类 */
	NPC *n2；
    // 为什么要用指针，因为new返回一个该类型的指针
	n2 = new NPC() 
    n2 = &n1     // 可以指向一个已经创建的对象
        
	/* 构造函数调用 */
	NPC n3(1) //调用构造函数
	NPC * n3 = new NPC(1)
}
```

#### 2、类引用第三方类

``` c++
#ifndef __xxx
#define __xxx
// 第三方类
class Rect{ ... } 
// 引用的类
class NPC 
{
    //引用另外的类
	Rect * a; 
}
#endif //宏定义
```

### 二、继承

1. 父类的private权限不允许继承

   ```c++
   class Base {
   private:
       int a;//不允许继承
   } 
   ```

#### Ⅰ、基本语法

1. 构造函数：继承中构造函数的调用顺序

   - 子类未定义构造函数，编译器会自动添加进构造函数，

   ``` c++
   // 先调用父类构造函数，再调用子类构造函数
   class Base {} // 父类
   class chile : Base {}  // 子类
   
   chile c; // 先调用Base中的构造方法，再调用chile中构造方法
   
   /* 有参数的构造函数继承 */
   class Base {
       Base(int a){ ... }
   }
   class chile : Base {
       chile() {...};
   } 
   // 父类构造需要一个参数，所以，必须提供参数
   chile c(100); 
   ```

2. 析构函数：继承中构造函数的调用顺序

   ``` c++
   // 先调用子类析构函数，再调用父类析构函数
   class Base {} // 父类
   class chile : Base {}  // 子类
   
   chile c; // 构造
   delet c; // 析构，先调用chile中的析构函数，再调用父类的析构函数
   ```

   

``` c++
// 父类
class Base {}
// 继承base类，默认是private继承
class chile : Base {} 
// 继承多个父类,Base、Base2
class chile : Base, Base2 {} 

/* 继承方式 */
// 公众继承
// Base中的类public protected private不变
class chile : public Base {} 

// Base中的public 变为 protected
class chile : protected Base {} //保护继承

// Base中的private protected变为private
class chile : private Base {} //父类属性变为private
```

#### Ⅱ、显式调用父类构造

``` c++
class Base{
    Base(){}
}

class Son:public Base{
    // 调用父类构造函数
    Son() : Base(){ ... } 
}
```

#### Ⅲ、同名函数

- 函数还是参数都符合就近原则
- 父类中是虚函数，则调用子类函数
- 访问父类同名成员，需要添加作用域

``` c++
class base{
    void func(){...}
}

class son:public base {
    void func(){ ... }
}

son s1;
// 默认调用子类中的属性、方法，
// 子类会隐藏掉所有的同名函数（父类重载的函数都不会被调用）
s1.func(); 

/* 调用父类的方法需要添加作用域,调用父类Base中的属性 */ 
s1.Base::func();
```

#### Ⅳ、同名静态成员

``` c++
class Base{
public:
	static int m_A;    
}
// 类外赋值
int Base::m_A = 100;

class son: public Base{
public:
	static int m_A;    
}
// 类外赋值
int son::m_A = 200;

// 方法一，通过对象访问
son s1;
s.m_A; //访问son类自己的m_A
s.Base::m_A; //访问父类base的m_A属性

// 方法二、通过类名访问
son::m_A; //不用初始化对象
son::Base::m_A //通过子类的父类访问
```

#### Ⅴ、泛化

1. 父类可以存放子类对象，就叫泛化

1. 使用父类定义对象A，A可以存放其子类变量，

   （只能存放，但要调用子类方法，需要虚函数）

  ``` c++
  class Animal{}; // 父类
  class A: public Animal{}; // 子类
  
  Animal *p  = new A(); //正确，父类可以存放子类
  ```

2. 父类指针被子类对象初始化，反之不对

   即：父类定义的变量，可以存放子类对象
3. 注意：**这种情况只能调用父类中的方法**，调用子类中的方法需要用虚函数

``` c++
class Animal {
    void set_value();
}

class A: public Animal {
    void set_value();
}

/* 调用-只能调用父类方法 */
// An可存放子类A
Animal *An = new A(); 
An->set_value(); // 调用Animal中的方法
// An存放父类Animal
Animal *An = new Animal();
An->set_value(); // 调用Animal中的方法

/* 另一种写法 */
A a;
Animal *An = &a;
An->set_value();

/* 错误 */
A *a = new Animal();
```

#### Ⅵ、多继承

- 不管是怎么继承方式，只要没有虚函数，就调用定义类中的方法
- 只要父类包含`virtual`关键字，优先调用子类中方法

``` c++
/* 多继承 */
class A {}
class B {}
class C: public B, public A {}

/* 树形继承 */
class A {}
class B: public A {}
class C: public B {}

A *p = new A(); // 调用class A中方法
B *p = new B(); // 调用class B中方法
C *p = new C(); // 调用class C中方法
```

#### Ⅶ、虚继承

``` c++
/* 虚继承 */
class A {};
class B {};
// B,A只会实例化1次
class C: virtual public B, virtual public A {}
```

### 三、多态

1. 多态分为2类，一是静态多态和动态多态
   - 静态多态：函数重载、运算符重载、函数名复用
   - 动态多态：派生类、虚函数 

2. 静态多态和动态多态的区别
   - 静态多态的函数地址-编译的时候确定
   - 动态多态的函数地址-运行的时候确定

3. 注意：

   在其他语言中例如python，php中他们的变量并没有类型，从而，天然可以使用多态

   而在C/C++中不同的类需要不同的类定义，即使，而使用多态，就可以实现一个类的定义，可以调用不同类中的同名方法（父类和子类中的同名方法，使用父类定义）

4. 总结：一般规律

   存在virtual关键字：

   `A *p = new B();` p指向的是B类，p调用的方法都是B类的

   不存在virtual关键字：就近原则，看指针类型

   `A *p = new B();` p指向的是A类，P调用的方法都是A类的

#### Ⅰ、虚函数

- 构造函数没有虚函数，析构函数有虚函数
- 父类的虚函必须实现，若不需要实现，可以考虑纯虚函数
- 父类的虚函数（函数名：speak）实现后，其所有子类孙子类的speak方法都是虚函数

``` c++
/* 类的定义 */
class Animal { // 父类
	virtual void speak(){ 
        printf("动物在说话");
    }
}

class A:public Animal{ //子类
	void speak() override{ 
        printf("A在说话");
    }
}

/* 调用方法 */
// 若父类没有virtual，则只能调用父类中的方法
Animal *An = new Animal();
An->speak(); // 调用父类Animal中方法
Animal *An = new A();
An->speak(); // 调用子类A中方法
```

其子类孙子类可以重写speak方法、也可不写

``` c++
/* 类的定义 */
class A { // 父类
	virtual void speak(){ 
        printf("动物在说话");
    }
}

class B:public A{ //子类
}

class C:public B{ //子类
	void speak() override{ 
        printf("C在说话");
    }
}

/* 情况一：没有重写父类方法的子类，会调用父类方法 */ 
A *p1 = new B();
p1->speak(); // 输出：动物在说话

/* 情况二：重写了父类方法的子类，调用子类方法 */
A *p2 = new C();
p2->speak(); // 输出：C在说话

/* 补充，与new后有关 */
A *p3 = new C();
p3->speak(); // 输出：C在说话
B *p4 = new C();
p4->speak(); // 输出：C在说话
```

#### Ⅱ、父类中调用子类方法

``` c++
/* father.h文件中 */
// 父类中声明子类已定义
class son;
class father{}

/* father.cpp文件中*/
// 引入子类头文件
#include "son.h"
```

#### Ⅲ、抽象类/纯虚函数

1. 只要类中含有一个纯虚函数，那么这个类就是抽象类。

2. 抽象类/纯虚函数在继承中可以出现

   ``` c++
   class A{}; // 普遍函数
   class B: public A // 纯虚函数
   {
   public:
       virtual void aaa() = 0;
   }
   
   class C : public B // 实际使用的类
   {
   public:
       virtual void aaa()
       {
           std::cout << "ee1ee\n";
       }
   };
   
   /* 只能调用A中的方法，虚函数定义在B中 */
   A *p = new C(); 
   /* 可以调用父类A的方法，也可以调用子类的虚函数 */
   B *p = new C();
   p->aaa();
   ```

   

3. 父类不能使用`new`出新对象，子类可以使用`new`出新对象

   ``` c++
   class Animal{}; // 假设Animal为纯虚函数
   class Cat: public Animal{}; // 子类
   
   /* 纯虚函数不能创建对象 */
   Animal A; //错误1
   Animal *A = new Animal(); //错误1
   
   /* 虽然不能初始化抽象类，但可以存放其子类 */
   Animal *A = new Cat();
   ```

   > 不允许对不可访问的基类 ~ 进行转换

   - 子类继承时没有添加`Public`
   - `class Cat: public Animal{}`：不要忘记添加权限

   > 不允许使用抽象类类型 ~ 的对象，函数 ~ 是抽象函数

   - 纯虚函数不能创建对象

4. 抽象类特点：

   - 无法实例化对象，不能创建对象，但可以创建类指针 
   - 子类必须重写抽象类中的纯虚函数，否则子类也是抽象类
   - 抽象类只用`.h`文件即可，不需要`.cpp`文件
   - 特点：必须有 `virtual`与`=0` 

``` c++
/* 类的定义 */
// 纯虚函数的类，简单理解为接口文件（Animal接口类）
class Animal {
	virtual int speak()=0; // 纯虚函数
}

// 注意一定写public或private或protection
class cat:public Animal{
	int speak() override{ printf("A在说话") }
}

/* 纯虚函数调用-接口 */
Animal *A  = new cat();
A->speak();
```

#### Ⅳ、抽象类多级继承

- 只要有一个子类重写了纯虚函数即可

  ``` c++
  class Animal {
  	virtual void speak()=0; // 纯虚函数
  }
  class land_animal:public Animal{ // 这里重写了虚函数，即可
  	void speak(){ printf("land_animal在说话") }
  }
  class cat:public land_animal {} // 其孙子类没有重写也没问题 
  ```

普通继承方式

``` c++
/* 所有子类都重写 */
class Animal {
	virtual void speak()=0; // 纯虚函数
}
class land_animal:public Animal{
	void speak() override{ printf("land_animal在说话") }
}
class cat:public land_animal {
    void speak() override{ printf("cat在说话")}
}
Animal *A = new cat();
A->speak(); // 打印cat在说话
Animal *A = new land_animal();
A->speak(); // 打印land_animal在说话

/* 只重写一部分 */
class Animal {
	virtual void speak()=0; // 纯虚函数
}
class land_animal:public Animal{
	void speak(){ printf("land_animal在说话") }
}
class cat:public land_animal {}
Animal *A = new cat();
A->speak(); // 打印land_animal在说话
Animal *A = new land_animal();
A->speak(); // 打印land_animal在说话
```

虚继承方法

``` c++
```



#### Ⅲ、虚析构

- 在使用多态的时候，父类指针无法调用子类的的析构函数
- 父类指针被子类初始化，调用析构方法时只会调用父类析构函数
- 使用虚析构函数，就可解决没有调用子类析构函数的问题

``` c++
/* 虚析构的定义 */
class Animal {
    virtual ~Animal(){ ... }
} 

/* 使用虚构函数 */
class Cat:public Animal {
    // 使用了虚析构，子类父类的析构函数都会被调用
	~Cat()
}

/* 
发生问题原因：
创建的是父类的指针animal,释放的也是父类animal,而我们则是利用多态创建的子类cat，调用的也是子类cat中的speak方法，而没有释放掉子类cat中的堆空间
*/
Animal * animal = new Cat(); 
delete animal; 
```

#### Ⅳ、纯析构函数

``` c++
/* 纯虚析构的定义 */
class Animal {
    // 必须定义，定义虚构函数后，让子类重写
    // 这样子类析构的时候，就会调用子类的析构函数
	virtual ~Animal() = 0;
} 

// 纯虚析构，需要在内中声明，在类外实现
// 纯虚析构必须得有实现
Animal::~Animal(){
	cout << “animal纯虚析构”;
}

/* 使用虚构函数 */
class Cat:public Animal {
public:
    char *name;
    void Cat(const* name){
        this->name = new char[strlen(name)+1]; 
        strcpy(this->name, name);
    }
	// 注意，这里并未重写父类析构，
    // 但只要父类定义了虚析构函数，就可以调用这里的析构函数
	~Cat() {
		if (this->name !=NULL){
			delete [] this->name;
		}
	}
}

/* 
发生问题原因：
创建的是父类的指针animal,释放的也是父类animal,而我们则是利用多态创建的子类cat，调用的也是子类cat中的speak方法，而没有释放掉子类cat中的堆空间
*/
Animal * animal = new Cat(“TOM”); 
//多态，调用Cat类的speak方法
Animal->speak(); 
delete animal;
```

#### Ⅴ、override和final

- override：说明重写父类方法，若父类没有此虚函数，则会报错
- final：最终方法，无法被继承

无法被继承的类

``` c++
/* final */
class A final { //类无法被继承
    virtual void fun();
}

/* 错误 */
class B: public A{}
```

无法被继承的函数

- 其子函数，不能出现被final定义的函数，其类可以被继承

``` c++
class A { //类无法被继承
    void fun() final; // 方法无法被继承
}
class B:public A{
    void fun(); // 错误，fun被final定义，无法被重写
    void zfun(); // 正确，可以被调用
}
```

override重写方法

- 指出重写父类方法，若父类没有此方法，错误

``` c++
class A {
    virtual void fun();
}
class B:public A{
    virtual void cc() override; //错误，父类没有此方法
    virtual void fun() override; //正确
}
```
