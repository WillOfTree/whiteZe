# 模板-泛型编程

C++使用模板实现范式编程，模板的目的是提高程序的复用性

## 模板基本语法

- template：声明创建一个模板
- typename：表明这是一个数据类型，可以使用class代替
- T 通用的数据类型，名称可以替换，通常为大写字母

``` c++
// 函数声明或定义
template <typename T>
T aaa(T a, T b) 
{
    return (a > b) ? a : b;
}

// 使用方式一：自动推导类型
int m = aaa(3, 5); 
// 使用方式二：显式指定类型
double d = aaa<double>(2.5, 3.7); 
```

## 函数模板

- 当普通函数与模板函数同名时，优先调用普通函数（函数模板可以发生重载）
- 可以通过**空模板参数列表**强制调用函数模板
- 如果函数模板可以残生更好的匹配，优先调用函数模板

``` c++
// 一般的例子，对照组：
void swapInt(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

/* 改写成模板 */ 
// 声明一个模板，告诉编译器不要出错
template <typename T>
void mySwap(T &a, T&b)
{
    T temp = a;
    a = b;
    b = T;
}

// 使用模板
// 编译器自动推导
int a = 10;
int b = 20;
mySwap(10, 20);

// 显示指定类型
int a = 10;
int b = 20;
// <>告诉模板是int类型
mySwap<int>(a, b)
```

模板必须指定T的类型

``` c++
// 声明一个模板，告诉编译器不要出错
template <typename T>
void mySwap(){ cout << "xxx"; }
// 因为mySwap中没有参数，但必须在模板中指定类型
mySwap<int>()
```

#### 2、类模板

- 类模板没有自动类型推导

- 类模板在模板参数列表可以有默认参数

- 类模板中成员函数创建时机

  类模板的成员函数在调用是创建（只有调用的时候才知道存放什么类型）

``` c++
template <class T>
class mySwap{
public:
    void mySwap();
}

//可以添加默认类型
template<class T, class T2=int>
class LinkList{
	T name;
	T2 age;
	void LinkList(T name, T2 age){}
}

int main(){
	string a; int 1;
    //必须使用显示转换，函数模板可以自动推导，类模板不能推导
	LinkList<string, int>(a, b) 

}
```

### 三、普通函数与模板的调用规则

- 优先调用普通函数

  ``` c++
  // 优先调用
  void mySwap(T &a, T&b){
      cout << "xxx"
  }
  
  template <typename T>
  void mySwap(T &a, T&b){
      cout << "xxx"
  }
  ```

- 通过空模板参数列表来强制调用函数模板

``` c
template <typename T>
void mySwap(T &a, T&b){
    cout << "xxx"
}

// 模板参数列表是空的，调用模板
mySwap<>(a, b); 
```



- 函数模板可以发生重载

  ``` c++
  template <typename T>
  void mySwap(T &a, T&b){
      cout << "xxx"
  }
  template <typename T>
  void mySwap(T &a, T&b, T&c){
      cout << "xxx"
  }
  ```

  

- 函数模板可以产生更好的匹配优先调用函数模板

## 模板做函数参数

``` c++
void doWork(Person<string, int> &p) {
	P.show()
}

//参数模板化
template<class T1, class T2>
void doWork(Person<T1, T2>&p){...}
```

## 具体化模板

因为某些特定的数据，例如数组，无法通过模板传递

``` c++
// Person是一个类
// template<>是特殊写法
template<> bool myCompare(Person &p1, Person &p2)
{
    if (p1.n == p2.n)
    {
        return 1;
    }
}
```

## 类模板对象做函数参数

``` c++
// Person<String,int>类模板
void printPerson(Person<String, int>  &a)
```



### 三、类模板与继承

template<class T>

class Base

{

public:

T m_A;

}

 

//必须告诉child类型,否则不能分配内存

class Child: public Base<int> {}

 

//由用户指定类型

template<class T1, class T2>

class Child: pulbic Base<T2>

{}

### 四、模板的分文件编写

1、模板的文件是.hpp

2、方法实现与声明放到同一个文件中

因为C语言是份文件编译，但模板文件类型是在运行时确定，所以不能使用.h方法引入

可以直接引入.cpp文件，

模板文件编译在运行时会出错

 

### 五、模板与友元函数