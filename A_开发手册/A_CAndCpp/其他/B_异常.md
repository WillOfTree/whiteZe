## C语言处理错误方式

## 异常概念

## 异常用法

## 自定义异常体系

## 标准库异常体系

## 异常的优缺点 

## 异常

### 一、基本语法

``` c++
try{} catch(int) {}//捕获int类型异常

try{} catch(){} catch(){} //捕获多个异常

try{} catch(...){} //捕获其他类型异常

 

throw 1//抛出异常，可被catch抓到

throw 3.14//抛出double异常

 自定义异常类

class my Exception

{

public:

void myException();

}

 

throw MyException(); //抛出异常类

catch(MyException e)
```

### 二、栈解旋

从try开始，到throw抛出异常之前，所有栈上的对象都会被释放

### 三、异常接口声明

void func() throw() //不能抛出任何异常

void func() throw(int) //抛出int类型异常,当前函数只能抛出int错误

{

throw 1;

}

### 四、异常生命周期

throw new MyException();

catch(MyException *e)

{

delete e;

}

### 五、异常多态

### 六、标准异常库

\#include<stdexcept>

throw out_of_range(“年龄越界”); //越界异常

e.what() //异常信息