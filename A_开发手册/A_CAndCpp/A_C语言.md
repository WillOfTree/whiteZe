# C语言程序设计

## 备注：

### 一、返回值

1. int、double、float、string类型是可以直接返回的，返回的是原版的拷贝
1. STL标准库中的类型一般要返回引用，或指针

### 二、结构体

1、结构体可以相互赋值（相同结构），结构体数组不能相互赋值

``` c
// 普通结构体
struct _A {
    int a;
}
struct _A a,b;
a.a = 11;
b = a;
print("%d",b.a); //打印11

// 结构体数组，本质数组就不能使用‘=’相互赋值
struct _b {
    int a;
}
struct _b cc[100];
struct _b dd, ee[100];
dd = cc; // 错误
ee = cc; // 错误
```

2、结构体数组`[]`符号与使用指针效果相同

``` c
// book 是一个Person类型结构体
struct Person *pson = book;

for (int i = 0; i < len; i++) {
    // pson[i] 等价于 *(pson + i)
    printf("%s\n", pson[i].name);
    // 与6行等价，注意一定是(*(pson+1)).name
    printf("%s\n",(*(pson+1)).name)
}
```

## 多应用开发

### 一、多应用的结构和文件

1、每个文件的功能

- 共享的函数写到1个单独的.c文件
- 共享的函数原型（声明）、宏定义、全局变量声明放到单独的.h文件

2、调用

``` c
/* <>是调用系统的函数库文件
   “”是调用用户定义的函数库文件，搜索位置为当前目录*/
/* my.c是共享函数文件
   my.h是共享的声明文件*/
#include<./my.h>
```

3、样例

- main主文件

  ``` c
  #include <stdio.h>
  #include "guess.h"
  
  int main(void)
  {
      int number;
      GuessNumber(number);
      return 0;
  }
  ```

- MakeNumber.c

  ``` c
  #include <stdio.h>
  #include "MakeNumber.h"
  int MakeNumber(void){}
  ```

- MakeNumber.h

  ``` c
  #ifndef _XXXXX_H_
  #define _XXXXX_H_
  
  #define MAX_NUMBER 100
  int MakeNumber(void);
  #endif
  ```

### 二、条件编译

防止.h文件多次引入

``` c
#ifndef _XXXXX_H_
#define _XXXXX_H_
...//头文件内容
#endif
```

### 三、IDE中多文件

1. 创建.h后缀名的头文件（例：func.h）
2. 创建.c后缀的源文件（例：func.c）
3. 在源文件（main.c）中引入头文件（func.h）

main.c

``` c
#include "func.h"
int main(){
    my_func(1,2);
}
```

func.h

``` c
// 引入其他func.c需要的头文件
#include <stdio.h>
// 声明func的自定义函数
int my_func(int, int);
```

func.c

``` c
#include "func.h"
int my_func(int, int){
    return 1;
}
```

## 带参数的main函数

``` c
/*
int argc:     参数的个数
char *argv[]: 参数的实际字符
copy file1.c file2.c //argv[0]= copy; argv[1]=file1.c
*/
int main(int argc, char *argv[]){}
```

## 头文件引入规则

## 基本数据类型

### 一、单位

- bit [b] 比特（位）：最小单位（一般单片机操作的单位）

- Byte [B] 字节 ：C语言操作的最小单位（sizeof的单位等）；1B=8bit；

- word 字：一个字存储一个 int 类型的数据；

- Kilobyte [KB] K ：一千个字节（B）；1K=1024B

- 计算机一次能处理的数据大小区将计算机区分为32位/64位

    32位计算机：1字=4字节=32位

    64位计算机：1字=8字节=64位

| 说  明               | 字符型    | 短整型         | 整型        | 长整型        | 单精度浮点型 | 双精度浮点型 |
| -------------------- | --------- | -------------- | ----------- | ------------- | ------------ | ------------ |
| 数据类型             | char      | short          | int         | long          | float        | double       |
| 所占大小32位（B）    | 1         | 2              | 4           | 没有明确规定  | 4            | 8            |
| 所占大小64位（B）    | 2         | 4              | 8           | 只规定比int大 | 8            | 16           |
| （以下32位大小可表示 | 的数的范  | 围、十进制）   |             |               |              |              |
| 可表示数的范围       | -128\~127 | -32768~32767   | -2G~2G      |               |              |              |
| unsigned（无符号）   | 0~255     | 0~65535        | 0 到 4G     |               |              |              |
| 二进制计算方式       | $2^8=256$ | $2^{16}=65536$ | $2^{32}=4G$ |               |              |              |

### 二、变量

1. 命名方式
   - 字母数字下划线组成
   - 字母下划线开头
2. C语言区分大小写

#### Ⅰ、静态变量

1. 全局可用：静态变量和全局变量的存储区域是一起的，一旦静态区的内存被分配, 静态区的内存直到程序全部结束之后才会被释放。

2. 静态变量只可声明1次

3. static静态变量程序运行期间只初始化1次，第二次碰见直接跳过static定义

   ``` c
   // a的值为9
   int func(){ 
       static int a = 0; // 只有第一次定义的时候，运行这个
       a+=1;
   }
   
   int main(){
       for(int i=0;i<10;i++){
           func();
       }
   }
   ```

静态变量定义

``` c
/**
原型：
	static 类型名 变量名
说明：
	1、static + 局部变量：改变了局部变量的生存周期，只有第一次定义有效，多次定义无效。
	2、static + 全局变量：使全局变量只能在当前文件（.c）中使用，改变了连接属性
    3、static + 函数：使函数只能在当前文件（.c）中使用，改变了连接属性
*/
static int a; // 静态变量
static int func(void){};// 静态方法
```

#### Ⅱ、常量

1. 整型常量：520,11,1314

   1. 二进制标识0b，例如0b00001010
   2. 八进制标识0，例如0123
   3. 十六进制0x，例如0x10ff

2. 实型常量：3.1414, 444.333

   0.0默认为double类型，而0.0f是float类型

3. 字符串常量（双引号）："Loveme"

   字符串常量必有一个 ' \0 ' 结束符，与字符常量有本质不同

4. 符号常量：#define定义

5. 字符常量（单引号）：

   - 普通：'L'，'O'
   - 特殊含义：'\n','\t'

6. 有符号数：

   最高位是符号位1标识负数，0表示正数

   范围：-128~-127（通常用-0表示-128）

7. 无符号数：unsigned int num 无符号（默认是有符号数）

定义方式

- 通过#define定义的常量是根据值来匹配数据类型
- const 定义的常量是不安全的，可以通过指针来修改（C语言中）
- 字符串常量

```c
const int PI = 3.14  // 程序内定义
#define PI 3.14 #符号常量，宏定义
```

#### Ⅲ、全局变量

- 全局变量会自动初始化为0。
- 当全局变量与局部变量重名时，***局部变量有用***
- 全局变量作用范围：整个工程（不同文件，要用extern声名）

```c
int a = 0; //全局
int main()
{
    ...
}
```

#### Ⅳ、extern

用于声明变量，函数，告诉编译器，这个变量函数已经在后面定义

```c
extern int a;
extern func();
//不同文件声明
extern int a;
int main() { a = 3}
//其他文件定义
int a =4;
```

### 三、作用域

- 全局变量：整个文件，在程序所以位置上都有效，程序结束释放

- 普通变量：{}的范围内，超出既无效

  1. 自动变量：默认变量

     ``` c
     /**
     原型：
     	auto 变量类型 变量名
     注意：
     	1、自动变量定义时不会自动初始化，所以里面的数据是随机的
     	2、自动变量在退出函数后，其内存空间会被释放
     */
     auto int a;
     int a; //简写
     ```

  2. 外部变量

     - 多文件应用中，为了让其他文件可以识别本文件的变量，而使用extern
     - 静态存储区存放

     ``` c
     /**
     原型：
     	extern 变量类型 变量名
     说明：
     	1、外部变量相当于全局变量
     	2、生命周期是程序结束
     */
     extern int a;
     ```

  3. 寄存器变量

     - 常用变量可以声明为寄存器
     - 现代编译器会自动声明寄存器变量，我们不用干预

     ``` c
     /**
     原型：
     	register 变量类型 变量名
     */
     register int a;
     ```

### 四、进制转换

1、十进制转二进制

- 除法运算（求789的二进制数）

  由高位到低位书写：1010100011
  $$
  789/2=394 \to 余1: 第10位（高位）；\\
  394/2=197 \to 余0: 第9位\\
  197/2=98 \to 余1: 第8位\\
  98/2=49\to 余0: 第7位\\
  49/2=24\to 余1: 第6位\\
  24/2=12\to 余0: 第5位\\
  12/2=6\to 余0: 第4位\\
  6/2=3\to 余0: 第3位\\
  3/2=1\to 余1: 第2位\\
  1/2=0\to 余1: 第1位（低位）\uparrow\\
  $$
  
- 1248表格法

  | 11       | 10    | 9     | 8     | 7     | 6     | 5     | 4     | 3     | 2     | 1     |
  | -------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
  | $2^{10}$ | $2^9$ | $2^8$ | $2^7$ | $2^6$ | $2^5$ | $2^4$ | $2^3$ | $2^2$ | $2^1$ | $2^0$ |
  | 1024     | 512   | 256   | 128   | 64    | 32    | 16    | 8     | 4     | 2     | 1     |

  求789的二进制

  1. 789最大可减512（789-512=277），所以最高位第10位（512是第10位，从0开始）为1
  2. 277最大可减256（277-256=21），所以第9位（256为第9位）为1
  3. 21最大可减16（21-16=5），所以第5位（16为第5位）为1
  4. 5最大可减4（5-4=1），第3位为1
  5. 1最大可减1（1-1=0），最后一位为1
  6. 最终得1100010101，再将结果反写得1010100011

2、二进制转10进制

<img src=".\assets\c\二进制转换.jpg" style="zoom:50%;" />

3、二进制转8进制：二进制3位一组转10进制，再将得到得数拼接在一起

4、二进制转16进制：二进制4位一组转10进制，再将得到得数拼接在一起

### 五、数据存储

1、内存中存储正数使用原码（正数三码相等），存储负数使用补码。

2、正数的补码反码原码都相同

3、补码计算方法

- 将原码取反（0变1，1变0，最高位不变，它是符号位）$\to$ 反码
- 反码+1=补码
- 例： -1
  1. 原码：10001
  2. 反码：11110
  3. 补码：11111



## 基本运算符

### 一、++a与a++

- ++a是在a使用前，先进行++操作

  a = 5; n=0

  n = ++a; // a先进行加1操作，a为6，n也为6

- a++是在a使用后，a进行++操作

  a = 5; n=0

  n = a++; // a先进行赋值操作，n为5；a再进行+1操作，a为6
  
- 单独a++与++a的值相同，没有特殊意义，全面理解为a = a+1

### 二、宏常量与宏定义

1、定义方法

``` c
#define 标识符 字符串
#define PI 3.1415926
```

### 三、强制类型转换

1、自动类型转换（由低向高转换）

- $int\to unsigned\ int\to long\to unsigned\ long\to double(float)$
- 自动转换可以理解为在高位添加0，并不影响数值精确的
- 例：int-double，int会被转换为double再计算结果

2、强制转换

- 格式：（类型）表达式

  ``` c
  //a为int，b为double
  //强制转换a变为double
  int b = (double)a
  ```


### 四、逻辑运算符

1、常用逻辑运算符

- 情况一，A B同真同假；&&与 || 的结果与AB相同

  例：AB为真（1）则；A&&B=1

  例：AB为假（0）则；A || B=0

- 情况二，AB一真一假；&&与 || 的结果与符号相同（&&为0，||为1）

  例：AB一真一假；A&&B=0

  例：AB一真一假；A||B=1

```c
&& //两个数同时为真才为真
|| //有1个为真即为真
！ // 取反
^  // 异或操作，相同为0不同为1
```

2、短路求值

- &&为0，||为1

- 只看最左边第一个表达式的结果，表达式结果与逻辑运算符相同退出运算

  情况1：&&（0），左边第一个表达式为0，退出运算

  情况2：||（1），左边第一个表达式为1，退出运算

```c
// &&（0）逻辑与，如果第一个运算为假（0），退出运算（第2个运算短路）
(a = 0) && (b = 1); // a=0假， 退出运算(不执行b=1)
(a = 1) && (b = 1); // a=1真， 继续运算（执行b=1)

// || 逻辑或，如果第一个为真（1），退出运算（第2个运算短路）
(a = 1) || (b = 1); // a=1真， b=1（短路）
(a = 0) || (b = 1); // a=0, b=1, 先运行a=0,假，再运行b=1真，其整体结果为真，a,b都运行
```

### 五、sizeof 运算符

+ 用于计算字符大小（单位：字节B），sizeof是运算符，不是函数

```c
/* 定义方法 */
sizeof(object);
sizeof object; //sizeof是一个操作符，可以省略（）

//于数组，sizeof会计算整个数组的大小
int a[] = {1,2,3,4};
sizeof(a); //16 B, 计算整个数组大小
sizeof(a[0]); //4B，int类型4字节
sizeof(a = a + 1);//a=a+1不参与其他运算，在编译时已经完成计算

//对于结构体，sizeof会计算整个结构体大小
SNode *z;   //定义一个SNode类型的指针变量 z
sizeof(*z); // 打印z对应的结构体大小
sizeof(z);  // 打印z的大小，z是一个指针，固定大小
```

+ **数组做函数参数传递时（特例-数组）**

```c
/*
1、sizeof(数组)，这是一个特例，计算的是整个数组的大小。单位B
2、当在函数传递过程中，是按普通形式计算，变量所占的大小。单位B
*/
void func_01(int a[], int size)
{
    printf(“%d”, a[0]); // 数组a[0]
    printf(“%d”, sizeof(a)); //指针大小（32位4，64位8 ），普通形式
}

int main()
{
    int a[] = {1,2,3}
    int b = sizeof(a); //计算整个数组大小，特例
    func_02(a, 3);
}
```

+ **结构体做函数参数传递时（结构体指针退化为普通指针）**

```c
typeof struct {
    int num;
    int aa[30];
}stu;

//void func_01(stu s);  //这种传递会拷贝一份s给函数，效率低
void func_01(stu *s);
{
    printf(“%d”, s->num);    // 结构体stu的num ,10
    printf(“%d”, sizeof(s)); //会打印指针大小（32位4，64位8 ）

    // 错误计算：
    // int a = sizeof(s->aa)/sizeof(s->aa[0]); // 这样只能计算整个数组的个数，不能计算一共有几个有效数据大小
    //
}

int main()
{
    stu s;
    s.num = 10;
    func_01(s); //调用函数
}
```

+ **计算数组长度 C/C++**

```c
// 计算数组大小
int arr[10] = { 0 };
int len = sizeof(arr) / sizeof(arr[0]);

// 计算字符串，会算上\0
char a[3] = {'a','b','\0'};
int len = sizeof(a) / sizeof(a[0]); //结果为3
```

### 六、位操作符

- 位运算符只能操作int与char类型
- 把字节（1B = 8bit）拆开计算，位域一定小于操作系统的位数（32位/64位）

1、位域：我们可以指定某个成员变量所占用的二进制位数（Bit）

```c
// 位域定义；
// ：后面的数字用来限定成员变量占用的位数
struct Player{
    unsigned int a:1; //1位
    unsigned int b:4; //4位
    unsigned int c:3; //3位
    unsigned int :1; //无名位域，站空
}

// 位段成员必须是 int、unsigned int、signed int、 char
// 位段的成员后面有一个冒号和数字
// 每次开辟空间是4字节，最大不能超过类型大小（int，4字节）
// 位段不能跨平台
struct A {
    int a:2; //a占2个比特位（bit）
    int b:3; //b占3个比特位（bit）
}
```

2、逻辑位运算符

- &（逻辑与）与 | （逻辑或）运算符

  1. 情况一，A B同真同假；&和 | 的结果与AB相同

     AB为真（1）则：A&B=1，A | B=1

     AB为假（0）则：A&B=0，A | B=0

  2. 情况二，AB一真一假；&和 | 的结果与符号相同（&为0，| 为1）

     AB一真一假：A&B=0

     AB一真一假：A | B=1
     $$
     \&\frac{0011}{0001}=0001 \\
     |\frac{0011}{0111}=0111\\
     $$

- ~（取反）：0变1，1变0

- ^（逻辑异或）：相同为0，相反为1

3、移位运算符

- << 左移，乘法 移1位乘2
- \>\> 右移，除法 移1位除2

```c
11001010 << 2 //左移2位 === 00101000
11001010 >> 2 //左移2位 === 00110010

int a = 1;
int a = a << 1; //000 000 01 向左移1位
```

### 七、重定向-shell

- < 重定向标准输入
- \> 重定向标准输出
- 2\> 重定向标准错误输出

```shell
$ ./a.exe > output.txt # 输出内容到output.txt
$
$ ./a.exe 2> error.txt # 输出内容到error.txt
$ ./a.exe > out.txt 2> error.txt # 内容输入到out.txt,错误信息到error.txt
```

### 八、三目操作符

```c
/**
原型
	exp ? exp真 : exp假
*/
int max;
max = a>b?a:b;
```

### 九、逗号表达式

- 从左向右依次计算，没有什么特别的

```c
// 多个数值定义
int a,b,c=0;

// b为2
int b = 1
int d = (a=b+2, c=a-4, b=c+3)
```

### 十、const限定符

只能初始化，不能修改变量里的值 

1、const int *p

- *p是一个常量，不能被修改，但p可以被修改

``` c
int a,b;
const int *p = NULL;
p = &a; //p可以指向任意变量
*p = 12333； //不能修改p指向的内容
```

2、int const *p

- 等价于1（const int *p）

3、int * const p

- p是常量，不能被修改；*p可以被修改

```c
int a;
int *const p = NULL;
p = &a; // p 不能被修改，p不能改变指向的变量；初始化后就不能修改
*p = 1233; // p所指变量的值，可以任意修改
```

### 十一、typedef 类型重定义

1. 在C++中使用using替代typedef

   ``` c++
   typedef int int_name;
   //等价于
   using int_name = int;
   ```

2. 函数指针的定义

   ``` c
   typedef bool (*funcptr)(int, int); // 定义一个类型
   typedef bool fun(int, int);
   // 使用c++
   using funcptr = bool (*)(int, int);
   using fun = bool (int, int);
   
   // 使用，函数作为参数
   void func2(int a, funcptr *fun);
   ```

```c
typedef int A; //重命名int为A
typedef int A, B; // 给int起2个别名,A\B都是int
typedef char* A; //给char *起一个别名
typedef unsigned int u_int //给unsigned int 重命名为u_int

// 声明一个结构体，一个结构体指针
typedef struct {
    int num;
    int aa[30];
}stu, *stu2;

(stu2)malloc(sizeof(stu))
```

## 输入和输出

见C_lib.md文件

## 控制条件语句

### 一、if结构

1、单分支

``` c
/**
原型：
	if(表达式) 条件为真，运行语句；
*/
int A = 3;
if(A>1) printf("AAA");
```

2、双分支

``` c
/**
原型：
	if(表达式A)
	{	A为真，语句B；}
	else：
	{	A为假，语句C；}
*/
int A = 10;
if (A>12){
    printf("B");
}else{
    printf("C")
}
```

### 二、switch结构

``` c
/**
原型：
	switch(表达式)
	{ 
		case 常量1：语句1；break；
		case 常量2：语句2；break；
		default：{默认执行的语言}
	}
*/
switch(op) //op只能是int或char
{
    case '+': //这里必须是常量
        printf("AAA");
        break; //必须加break，不然程序不会停止
    case '-':
        printf("ccccc");
        break;
    default: printf("xxxx");
}
```

### 三、while结构

``` c
/**
原型：
	while (循环控制表达式A)
	{
		A为真，语句；
		break; //强制退出循环
		continue;//退出本次循环，进行下一次
	}
*/
```

### 四、do-while结构

``` c
/**
原型：
	do
	{
		语句A；
		break；//强制退出循环
		continue;//退出本次循环，进行下一次
	}while(循环语句B)
说明：
	语句A一定会执行1次，语句B为真，运行语句A
*/
```

### 五、for结构

``` c
/**
原型：
	for(初始表达式A；循环控制表达式B；增量表达式C)
	{
		语句D；
		break;//强制退出循环
		continue;//退出本次循环，进行下一次
	}
说明：
	1、先运行初始化表达式A,初始数据
	2、执行循环控制语句B，结果为真，运行语句D
	3、执行语句C
	4、执行语句B
*/
```

### 六、goto结构

1. 直接跳出多重循环
2. 直接跳到结束出口，进行退出前的错误处理

## 函数与模块化设计

### 一、定义声明

#### Ⅰ、声明方法：

- 位置一定在函数调用前面，且没有{}
- 无参数函数不建议这样声明：`int func();` 

```c
/* 无参数 */
int func(void);

/* 含参数，不填写变量名 */
int func(int，char, ....);
/* 含参数，有变量名 */
int func(int a，char b, ....);

//不同文件的声名
extern int add(int a, int b);
```

#### Ⅱ、定义方法：

``` c
/* 具体定义函数功能，在{}中编写行为 */
int func(void){ ... };
int func(int a, ....){ ... };
```

### 二、函数值传递

```c
int func(int a, int b){
    printf(“a=%d”, a); //a传递的是值
    b = 10; // 并不会修改main中b的值，这个b自在func中有效
}  

int main()
{
    int a=10, b=20;
    // 不能修改变量的值，因为函数内是重新生成的新变量，与指针传递的不同
    func(a, b);
}
```

### 三、函数指针传递

```c
/* 因为传的是指针，所以要用*来读取值 */
int func(int *a, int *b) {  // int* a代表定义
    //因为a是地址，所以要用*
    printf(“a=%d”, *a); 
    // 这里修改了b的值，main中也会修改
    *b = 10; 
}

int main()
{
    int a=10, b=20;
    // 传指针能修改变量的值，而传变量不能修改
    func(&a, &b); //传地址
}
```

### 四、传数组

1. 数组与其他结构不同，数组名即使地址，传递数组名就等于传地址

#### Ⅰ、传一维数组

- 必须指明数组长度，因为数组传递后，sizeof无法读取数组个数

```c
/* 声明： 2种方法 */
void init(int a[], int num);
void init(int *a, int num);

// 调用
int arr[10] = {0};
init(arr, 10);
```

#### Ⅱ、传二维数组

- COW，ROW都代表具体以定义的数字
- 必须指明数组长度（cowNum, rowNum），因为数组传递后，无法读取数组个数

``` c
/* 定义 */
void init(int a[COW][ROW], int cowNum, int rowNum);
void init(int a[][ROW], int cowNum, rowNum); 
/* 错误定义：必须填写 列 个数 */
void init(int a[][], int cowNum, int rowNum);

/* 调用  */
int arr[3][5] = {{1,2}, {3,4}};
init(arr, 3, 5);
```

#### Ⅲ、传数组指针

``` c
/* 数组指针传递 */
//定义
void init(int *arr[20])
void init(int *arr[])
void init(int **arr)
//二维数组数组指针
void init(int (*a)[ROW], int i, int j);//数组指针传递方法
//调用
int *arr[20] = {0};
init(arr)
```

#### Ⅳ、传数组不常用的方法

``` c
// 若传递&arr应特别设置
void init(int *(*p)[ROW]);
init(&arr);

/* 数组长度不固定 */
// 函数的参数声明改成了(*mat)[3]
void transpose(int (*mat)[3], int row)
{
    a[1][2] = '2';
}
```

### 五、传结构体

#### Ⅰ、函数定义方式

- 优先使用地址传递

``` c
/* 方式一，使用struct关键字 */ 
// 传结构体指针
void func(struct _Player *ptr)
// 传结构体值
void func(struct _Player p)

/* 方式二，使用重命名的结构体变量 */
// 使用typedef定义一个结构体
typedef struct _Player{int a;}Player;
// 传结构体指针
void func(Player *ptr)
// 传值
void func(Player p)
    
/* main中使用方法，方法一二共用*/
int main(){
    func(&Player); //传指针
    func(Player); //传值
}   
```

#### Ⅱ、结构体内调用

```c
void func(struct _Player *ptr, struct _Player p)
{
    /* 传指针方式 */ 
    ptr->a = 100;
    (*ptr).a = 200; //与上面的效果相同
    
    /* 传值方式 */
    p.a = 100;
} 

// 重命名结构体Player
typedef struct _Player{int a;} Player;
int main()
{
    // 使用Player定义1个结构体,1个结构体指针
    player p1, *p2;
    //&p1传指针（推荐），p1传结构体
    p2 = func(&p1, p1);
}
```

#### Ⅲ、返回方法

``` c
/* struct _Player *：指明func返回的是一个结构体 */ 
struct _Player * func(void)
{
    // 返回结构体类型
    return &Player;
} 

// 重命名结构体Player
typedef struct _Player{int a;} Player;
int main()
{
    // 使用Player定义1个结构体,1个结构体指针
    player *p2;
    p2 = func();
}
```

#### Ⅳ、调用结构体数组

``` c
// 方式二
void func(struct _Player *ptr) {
    (ptr + 1)->a = 11;
}
// 方式一，
void func(struct _Player ptr[]) {
    /* 传指针方式 */ 
    ptr[1]->a = 100;
    (*ptr).a = 200; //与上面的效果相同
    
    /* 传值方式 */
    p.a = 100;
} 

// 重命名结构体Player
typedef struct _Player{int a;};
int main()
{
    // 使用Player定义1个结构体,1个结构体指针
    _Player p; //结构体
    _player p1[100];// 结构中数组
    // 因为结构体数组，本身是个数组，所以只传变量名即可
    p2 = func(p1);
}
```

### 六、可变参数

```c
#include <stdarg.h>
/*
va_list   声明
va_start  开始
va_arg    获取参数的值
va_end    关闭
*/

// ...表示参数数目不确定,1\步
int func(int n, ...)
{
    int s, sum;
    va_list vas; //声明一个可变参数类型，2\步
    va_start(vas, n) //va变量， 可变参数的个数，3\步
    for(int i=0; i< n; ++i)
    {
        sum = sum + va_arg(vas, int); //获取vas变量，变量数据类型，4\步
    }
    va_end(vas); //关闭vas类表，5\步
}

int main()
{
    func(3, 1,2,3)
}
```

### 七、传函数（函数做参数） / 回调函数

#### Ⅰ、声明

```c
int (*funp)(int a, int b); // 函数指针

/* 
pfun是一个返回int类型的函数，同时他也是一个参数
func是普通的函数
*/
int func( int (*pfun)(int, int), ...);
int func( int (*)(int, int), ...); //无法调用，没有函数名
```

#### Ⅱ、使用函数参数

``` c
int func(int (*pfun)(int, int), int a) {
    // 函数内使用,同变量，数组使用方法
    (*pfun)(1,2);
}
```

3、调用函数参数

``` c
int func(int (*pfun)(int, int)){...}
int pfun(int a, int b){...} //

int main()
{
    func(pfun)
}
```

4、返回值

``` c
int pfun(int a, int b){...}
int func(int a, int b)
{
    return (*pfun)(int, int); 
}

int main()
{
    //定义一个函数指针
    int *(*a)(int, int) = NULL;
    a = func(1, 2);
}
```

### 6、回调函数

```c
//函数A的指针作为参数传递到函数B，并在函数B内调用，函数A就是回调函数
int A(int a){}
int B(int (*A)(int a))
{
    A(1); //回调函数，在B中调用作为参数传递过来的函数
}

int main()
{
    B(&A);// 将A函数的地址做参数，&A与A完全相同
}  
```

### 3、内连函数

内连函数是一种优化操作，提高程序调用效率，只有在优化编译中才有效果（-o 参数编译），内连函数会增加编译时间，编译器会自动选着函数进行内连，不用手动操作

gcc test.c -O 

```c
// func_01同宏替换一样，效率较高，不会用堆栈
inline void func_01(stu *s);{}

int main()
{
    func_01(s); //调用函数
}
```

## 数组

- **只有数组、带有[]符号的变量，其数组名=首地址。**
- **数组、带有[]在需要输入地址的位置不需要&符号** 

``` c
char a[10];
scanf("%s", a); // 不需要&

/* 结构体传递 */
strcut _a { int b; }
struct _a BB[100]; // 定义一个结构体变量BB
func(struct _a temp[]); // 函数定义
func(BB); // 不需要&（结构体数组），普通结构体推荐传递地址

/* 数组不能直接赋值 */
int a[10] = {0};
int b[10];
b = a; //错误，不能赋值，只可以用指针指向或使用内存函数处理
```

### 一、数组名用途

用途1：整个数组在内存中占用的空间的大小，例如sizeof（arr）

用途2：获取数组在内存中的首地址

- 首地址 = 数组名 = &a[0] ，除此之外还有 **数组的地址** 概念
- &数组名（&arr）：取出的是**数组的地址**（$\neq 数组首地址$），使用数组指针存放

``` c
int arr[10];
/* 数组的地址 */
printf("%p", &arr);

/* 数组首地址，数组内部的操作 */
printf("%p", arr); 
printf("%p", &arr[0]);

/* 打印数组元素 */
printf("%d", arr[0]);

/**
数组的地址与数组首地址的区别
*/
printf("%p", &arr+1); // 会加整个数组的大小
printf("%p", arr+1); // 数组中下一个元素，例a[0]->a[1]
printf("%p", &arr[0]+1); // 数组中下一个元素，例a[0]->a[1]
```

### 二、一维数组

- 数组未初始化，数组内元素是随机的
- 使用static声明，数组会默认初始化为0

```c
/* 
定义
   数组类型 变量名[元素个数]
注意：
	元素个数是总个数，洗标为0-总个数-1
	int a[3]; 共3个元素，下标0-2
*/
int a[3]; 

/* 不固定长度，根据{}中的元素个数确定数组大小 */
int a[] = {0，1};

/* 共声明10个元素，但只有下标0-3定义了元素，其他未设置为随机数 */
int a[10] = {1,2,3,4};

/* 使用宏定义 */
#define SIZE 5
int a[SIZE];
```

### 三、一维数组常见错误定义

``` c
/* 错误定义，n不能是常量 */
const int n = 10;
int arr[n] = {0}; 

/* 错误定义，未指明数组个数*/
int arr[];
```

### 四、二维数组

- 二维数组必须指定 列 元素个数，不然会报错

```c
/*
定义赋值1：二维数组必须指定 列 元素个数，不然会报错
*/
int a[2][3] = {1, 2, 3, 4, .....}
int a[2][3] = {{1,2,3}, {2,3,4}}
int a[][3] = {1, 2, 3, 4, .....}

/* 
定义赋值2：2行3列 
*/
int a[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
}

/*
定义赋值3：将每一行 第1个 元素赋值
*/
int a[2][3] = {
    {1},
    {2}
}
```

### 五、C99支持的语法

```c
/* 变长数组 */ 
int b[a];   
int b[a-1]; 

/* 指定下标初始化 */
int a[10] = {
    [2] = 100,
    [3] = 200
}

/* 二维数组 */
int a[2][3] = {
    [0][0] = 1,
    [0][2] = 2
}
```

### 六、动态数组

## 指针

1. 例如$A\to b$（A指向b），就可以简单理解为A与b等价

### 一、定义 / 取址 / 取值运算符

1、定义指针变量

- 指针定义的时候，强烈建议指向NULL（stdio.h中定义）

``` c
#include <stdio.h>
/* 定义 */
int *p = NULL; 

/* 函数种定义指针 */
void func(int *a)
    
/* 无意义的操作 */
int *p = NULL;
//p本身就是地址变量，只有存放的地址是有实际意义，再对其取地址没有实际意义
printf("%p", &p); 
```

2、取地址操作

- & 取址运算，获取变量地址
- **只能使用指针变量存放地址**，用其他变量类型会出意外错误
- 不同类型的指针变量，**存放不同类型的地址**

```c
/* 取地址运算 */
p = &a;

/* 指针变量存放地址 */
int *p
p = &a;
```

3、取值操作

- \* 取值运算，获取地址的值
- **\* 运算符只能对指针变量操作**，若对普通变量，会出现不可预料的错误
- 区别定义与取值，\*号在定义时是定义功能，其他地方是取值
- [ i ] 也算一种 \*取地址运算，基本相当与 \*(a+i)

``` c
/* 取值运算:必须对 指针类型 变量操作 */
a = *p; 

/* [i] */
int a[10], i=0;
i = a[0];   //与11行等价
i = *(a+0); //与10行等价 
```

4、常见错误使用

``` c
/*---- 错误用法---- */
*p = &a; // 错误用法 
int* p = &a; //这是正确的
p = 1000; // 严禁向指针变量存放非地址数据
printf(*a); //*必须对指针变量使用
a=&b; //普通变量中存放地址,不会错误，但没有意义
/*----------------------*/
```

### 二、指针运算

```c
/* 指针类型确定指针读取的数据大小 */
int arr[10];
int *p = arr;
*(p+1) // 指针向后移动1个位置，相当于 stu[1]
*((char *)p +1) //强转char类型，根据char类型(1字节)确定步长，移动1字节，取值（这个值可能是乱码）

/* 移动整个数组长度 */
int arr[10];
int *p = &arr;
*(p+1) // 移动了整个数组长度，40字节

/* 指针相减，得到指针之间的元素个数（2个指针是同一个类型） */
int *p1 = str[9];
int *p2 = str[0];
int num = p1-p2;
```

### 三、空指针 / 野指针 / void指针

```c
/* 空指针 */
#include <stdio.h> //中有空的定义
int *p = NULL;

/* 野指针，指向位置不确定 */
int *p; //局部变量不初始化，默认时随机的
*p = 20; //非法访问内存
/* 野指针，越界访问 */
int arr[2] = {0};
int *p = arr;
for(int i=0; i<10; i++)
    *(p + i);
/* 野指针，局部变量指针不要返回 */
int *text(){
    int a = 20;
    return &a; //a的生存周期只在text()中
}

/* void指针 */
void *p = &a; //不知道a是什么类型
// 要是修改这个万能指针的化，需要强制转换成指定类型
*（char *)p = ‘a’; //char类型是一个字节
/* 万能指针 */
void* p = &a //万能指针，void
*(int*)p = 100 //当取值得时候要进行类型转换
```

### 四、指针数组

1. 声明

- 比直接使用数组存放更节省空间（因为可以不定长存储）

```c
/*  []优先级高于*  */
// 先得到p[5]，再变成指针，存放指针类型的数组
int *p[5];
```

2、定义/赋值

- 一次申请多个连续的指针变量空间，每一个空间只能存放地址

``` c
//初始化
int a, b, c, d;
int *p[4] = {&a, &b, &c, &d};
```

3、常用情况

``` c
// 常用于字符串
char *p1[3] = {"11111","AAAAA","ccccc"};
printf("%s", p1[1]); 

// 模拟二维数组
int a[] = {1,2,3};
int b[] = {1};
int c[] = {1};
int *p2[3] = {a, b, c}; //abc是一维数组名
//使用，printf对于数组，给地址就可以，变量要直接给变量
printf("%s", p2[1][1]);
```

### 五、数组指针（数组另一种写法）

1、声明

``` c
// 这是一个大小为2的数组指针
// 表示2个元素为一行，一个{}
// 例如 int a={1,2,3,4,5,6,7,8,9}
// int (*p)[2]就将{1,2,3,4,5,6,7,8,9}转换为{1，2}{3，4}{5，6}...
int (*p)[2];
```

2、定义、赋值

``` c
int temp = {1,2,3,4};
//&temp是temp整个数组的指针，与temp、temp[0]数组首元素的地址相同，意义不同
int (*p)[4] = &temp;
p[0];  // 表示数组首元素的地址
*p[0]; // 表示数组的首元素的值，即为数组 temp 的 1
*p[1]; // 表示指向数组的下一行元素的首元素的值，但是temp是一维数组，只有一行，所以指向的地址中的值不确定
**p;   // 表示数组的首元素的值，即为数组 temp 的 1


/* 读取 */ 
p+1; // 跳过一个数组
printf("%d", *((*p)+1) ); //(*p)是找到temp的数组内容，
```

3、二维数组-常用

```c
int a[2][3] = { //必须指明列
    {1,2,3}，
    {3,4,3}
}
int (*p)[3] = a; // 二维数组不用&符
// *(p+1) 相当于a[1], *(*(p+1)+2)相当于a[1][2]
printf("%s", *(*(p+1)+2) ); 
```

### 六、指针访问数组

1、一维数组

``` c
int arr[10] = {1,23,4,5,6,7}
// 指针指向数组
int *p = arr

// 打印数组中arr[0]
print(*p)
// 打印数组中arr[1]
p++;
print(*p)
```

2、二维数组

```c
//正确
int (*p)[3] = array; //必须指明列
int (*p)[2][3] = &array; //太复杂，访问时要多加一个*
print01(&a, 2, 3);
```

### 七、指向函数的指针

1、定义指向函数的指针

- 对于函数，&func与func完全相同

```c
//定义一个名为pfunc的函数指针，未指向任意函数
int (*pfun)(int, int);
```

2、赋值

- &pfun 与 pfun完全相同

``` c
int pfun(int, int){...};

// 方式一；定义时赋值
int (*p)(int, int) = pfun; //推荐
int (*p)(int, int) = &pfun; //与上相同

// 方式二；
int (*p)(int, int) = NULL;
p = pfun; // 推荐
p = &pfun;
```

3、调用方法

``` c
int (*p)(int, int) = func;

//调用
(*p)(10, 20);
p(10, 20); //与4行等价
```

### 八、const修饰指针

1、常量指针

- 指针指向可以修改，指针指向的值不能修改

``` c
// 常量 指针
const int *p = &a
// 例子
*p = 20; //const int 所以p指向的值不能修改
p = &b;  //可以修改 p的值 
```

2、指针常量

``` c
// 指针 常量
int * const p = &a
// 例子
p = &b; //错误，const修饰的是不能修改
*p = 20；//正确
```

3、既修饰指针，又修饰常量

``` c
// 都不可以修改
const int * const p = &a;
```

## 字符串

### 一、特别说明

1. C语言没有提供字符串的存储，所以使用 **数组 + \0** 来存储
2. \0 是字符串的结束标志，占用数组的一个单位，但不计入字符串长度

``` c
// 字符串数组长度 3
// sizeof计算的结果为2（不包含 \0）
char str[3] = {'a', 'b', '\0'}
char str[] = {'a', 'b', '\0'}

/* 字符串不能通过=赋值 */
char a[20];
char b[20];
scanf("%s", a);
b = a; //错误，不能赋值，只能使用字符串函数进行赋值
```

### 二、字符串定义

1、一维数组声明

``` c
/* 需要人工加\0的声明 */ 
char str[] = {'a', 'b', '\0'}
char str[3] = {'a', 'b', '\0'}

/* 系统自动加\0的声明 */
char str[] = {"ab"};
char str[] = "ab";
char str[3] = "ab";
```

2、二维数组声明

``` c
char str[][2] = {"ab", "cd", "ef"};
char str[1][2] = {"ab", "cd", "ef"};
```

### 三、字符串处理函数

见C_lib.md 字符串函数

### 四、字符处理函数

见C_lib.md 字符处理函数

### 五、字符串常量

1、定义方法

- 不允许修改，memcpy也不能修改
- 在 C++ 代码中不会通过编译
- 额外：对于strcap、strcpy等函数不能使用字符串常量

``` c
// 字符串常量"xxxxx"的内容不允许修改，但a的指向可以修改
char *a = "xxxxx";
*a = "2222"; // 错误，修改了“xxxxx”的内容

char *a = "xsss"; // 创建一个字符串常量"xsss", 使用指针a指向它
a = "xxxxxx"; // 创建另一个字符串常量“xxxxxx”，并使用指针a指向它
```

2、字符串常量的偏移

- 字符串常量等价于数组，变量名存放的是字符串常量的第一个元素的地址

``` c
// s存放的是字符串常量数组的第一个地址
// 也就是"abcdef"中a的地址
char *s = "abcdef";
a = a+2; //也可用 a++
```

3、字符串常量与数值

``` c
// 字符串常量会自动加\0结束
// a的长度为4，\0也占一个
char *a = "abc";

// 注意八进制
// \t是转义字符，\017是八进制数
char *a = "\ta\017bc";
```

### 六、字符串指针

- 利用指针声明的字符串是存放在常量区，无法修改值，内存中只存放1份

```c
/* 错误：字符串常量不能被修改 */
*name = "word"; //指针修改禁止

/* 字符串数组可以被修改 */
char str[] = "Hallo";
char *p = str;
*p = 'a';  //数组首地址=str[0]
*(p+i) = 'c'; //相当于str[i] = 'c'
p[1] = 'b';//相当于str[1] = 'b'
```

### 七、string类型

1、C语言没有string类型，只有C++有string类型

2、scanf获取字符串

``` c
# include <stdio.h>
int main(void)
{
    char str[10];  
    printf("请输入字符串：");
     /*输入参数是已经定义好的“字符数组名”, 不用加&, 因为在C语言中数组名就代表该数组的起始地址*/
    scanf("%s", str); 
    /**********************/
    printf("输出结果：%s\n", str);
    return 0;
}
```

### 八、函数传递字符串

共有2种情况，字符串数组，字符串指针

- 字符串数组：`char s[] = "xxxxx";` 
- 字符串指针：`char *s = "xxxxxxx";` 

``` c++
/* 字符数组 */
// 声明
void func_array(char s[]);
// 定义
void func_array(char s[]){
    
}
// 调用
char s[] = "xxxxx";
func_array(s);

/* 字符串指针 */
// 声明
void func_array(char * s);
// 定义
void func_array(char * s) {
}
// 调用
char *s = "xxxxx";
func_array(s);
```

## 结构体

1. 结构体可以相互赋值（相同结构），结构体数组不能相互赋值

   ``` c
   // 普通结构体
   struct _A {
       int a;
   }
   struct _A a,b;
   a.a = 11;
   b = a;
   print("%d",b.a); //打印11
   
   // 结构体数组，本质数组就不能使用‘=’相互赋值
   struct _b {
       int a;
   }
   struct _b cc[100];
   struct _b dd, ee[100];
   dd = cc; // 错误
   ee = cc; // 错误
   ```

   

2. 结构体数组`[]`符号与使用指针效果相同

   ``` c
   // book 是一个Person类型结构体
   struct Person *pson = book;
   
   for (int i = 0; i < len; i++) {
       // pson[i] 等价于 *(pson + i)
       printf("%s\n", pson[i].name);
       // 与6行等价，注意一定是(*(pson+1)).name
       printf("%s\n",(*(pson+1)).name)
   }
   ```

   

3. 关于资源释放

   - 一般情况下，结构体不需要手动释放。如果结构体只包含基本类型（如 `int`、`float` 等）或没有指针成员，其内存由栈或堆自动管理，不需要手动释放。
   - 如果结构体包含动态分配的资源（例如指针、文件句柄等），则需要在结构体的生命周期结束时手动释放这些资源。（析构函数中释放、RALL原则）

   

2、

``` c

```

## 

### 一、结构体对齐

- 使用sizeof获取变量大小，不要自己计算结构体大小

```c
//修改默认对齐数
#pragma pack(2)
#pragma pack() //取消默认对齐
// 小空间的尽量放在一起
struct {
    char a;
    int c;
}
```

### 二、声明 / 定义结构体

1、方法一（局部变量）

``` c
/* 声明，不占用空间 
struct是结构体的关键字，必须要有，
Player是自定义的结构体名称，因为可以定义不同的结构体，结构体没有名称就只能用1次
*/
struct Player{
    int a;
};
/* 定义一个结构体变量，占用空间，局部变量 */
struct Player p1; 
```

2、方法二（全局变量）

``` c
/* 在声明的时候定义2个结构体变量,而且是全局变量 */
struct Player{
    int a;
}p1,p2;
```

3、方法三（无名结构体）

```c
/* 无名结构体，
因为没有结构体名称，所以不能使用这个结构体定义新的变量
*/ 
struct { //这个结构体并没有标明其标签
    int a;
}p1,p2;  //只生成p1, p2这2个可用
```

### 三、typedef重命名

```c
/* 无名结构体，常用 */
// 用typedef重命名，新类型名为Player
// typedef的简单用法可以看出简单的文本替换
// typedef声明的结构体，定义变量可以少写struct
typedef struct { 
    int a;
} Player;
Player p1; // 定义一个Player类型的结构体变量 p1    
Player *p2; // 定义一个指针类型的P2


/* 有名结构体，多写一个名字 */
typedef struct _Player{
    int a;
}Player;
// 与无名定义效果相同
Player p1;
// 因为结构体有名，也可用普通的方法定义
struct _Player p2;


/* typedef定义结构体指针， */
// Player 普通结构体
// p_Player 结构体指针，
typedef struct {
    int a;
}Player, *p_Player; 
Player p1; // p1与p2，p3不同，p1是在栈中
/*
p2、p3分配空间方法：
	p_Player p = new Player; C++
	P_Player p = (p_Player)malloc(sizeof(Player))； C
*/
Player *p2; // 只是一个指针，就占4字节
p_Player p3; // p2等价于p，


/* 结构体定义多个 */
// 其中aaa,bbb,ccc三者都是结构体类型，声明变量时用任何一个都可以，
// 你可以当做取的三个别名，在c++中也是如此。
// 但是你要注意的是这个在c++中如果不写typedef关键字，那么aaa，bbb，ccc将是截然不同的三个对象。
typedef struct
{
	int num;
	int age;
}aaa, bbb, ccc;
```

### 四、初始化

```c
/* 局部变量 */
// 数据类型需要与类型相对应
struct Player{
    int a;
    char b[20];
    int c[10];
}
struct Player p1 = {1, "23444", {1,2,3,4} };

// 使用typedef定义初始化
typedef struct{...} Pla;
Pla p1 = {1, "234444"}

// 指定变量名初始化，C99
struct Player p1 = {.a = 1};

/*全局变量，声明时初始化结构体 */ 
struct Player{
    int a;
    char b[20];
    int c[10]
}p1 = {1, "3434", {1,2,3,4}}
```

### 五、访问 / 赋值

#### Ⅰ、结构体对象

```c
/* 结构体对象， 使用 . 来访问*/ 
// 定义一个结构体
struct Player {
    int a;
}
// 定义一个结构体变量p1
struct Player p1; //定义的结构体不是指针类型
p1.a = 100; //赋值
printf("%d", p1.a); //访问
```

#### Ⅱ、结构体指针

``` c
/* 结构体指针，使用 -> 来访问 */ 
struct Player{
    int a;
};
struct Player *p2; 

p2->a = 100; //赋值
printf("%d", p2->a); //访问
```

#### Ⅲ、同类型结构体赋值

``` c
struct Player p1, p2;
p1 = {1, "22222"};
p2 = p1; //同类型的结构体变量可以直接使用=赋值
```

#### Ⅳ、结构体内的数组或字符串赋值

``` c
// 这里使用了声明的时候定义结构体变量pv
// pv可以直接使用
struct Player{
    int a[20];
    char b[30];
    int c;
}pv;
// 普通变量赋值
pv.c = 100;
// 字符串赋值（字符串只能这么赋值）
strcopy(pv.b, "xxxxx");
// 数组赋值, 
// 定义时可以一起赋值，之后只能一个一个赋值
pv.a[0] = 1;
pv.a[1] = 2;
```

### 六、结构体嵌套

1、结构之间的引用

- 必须有结构体名称，不然无法定义结构体内部结构体

```c
struct _P{
    int a;
}

typedef struct _Player{
    int a;
    struct _P e; // 结构体引用
}Player;
```

2、结构体自引用（只能引用指针）

- 必须有结构体名称，不然无法定义结构体内部结构体

``` c
typedef struct _Player{
    struct _Player e;  //无限递归，错误
    struct _Player *e; //正确，找到和自己同类型的指针，并不是自己
}Player;
```

### 七、结构体数组

- 数组的每一个元素都是结构体

#### 1、普通定义

```c
struct s{
    int a;
}
struct s A[10];

// 赋值方法之一
struct s A[10] = {{1}, {1}, {1}}
// 访问
A[2].a = 10;
```

#### 2、使用typedef定义

``` c
typedef struct {
    int a;
} Player;
Player info[30];  // 使用结构体Player 声明一个30容量的info
info[1].a=1;
```

#### 3、指向结构体数组

``` c
typedef struct{
    int a;
} STD;

/* 结构体数组 */
struct _PPP{
    int a;
} p[20];
// 定义一个结构体指针,并指向一个结构体变量
STD *p1 = p
STD *p1 = &p[0] //与第10行意思相同
```

#### 4、嵌套的结构体数组

``` c
struct _A {
    int _A_a;
}

struct _B {
    // 嵌套一个_A类型的结构体数组，其名字位my_array
    struct _A my_array[100];
}

// 当创建结构体_B时，其内部的结构体_A也可以使用，可看成一般的变量
struct _B CC;
CC.my_array[1]._A_a = 1;
// 若使用指针定义一个结构体体
struct _B *AA;
AA->my_array[1]._A_a = 1;
```

### 八、堆空间开辟结构体

1、使用typedef的结构体

``` c
// 使用typedef
typedef struct{
    int age;
}t;
//开辟堆空间的结构体，sizeof可以直接计算结构体大小
t *p = (t *)malloc(sizeof(t));

// 给结构体内变量申请21个char类型空间
p->name = (char *)malloc(sizeof(char) *21)
strcpy(p->name, “ss”);
```

2、普通结构体

```c
// 使用typedef
struct tec{
    int age;
};
//开辟堆空间的结构体，sizeof可以直接计算结构体大小
struct tec *p = (struct tec*)malloc(sizeof(struct tec));

// 给结构体内变量申请21个char类型空间
p->name = (char *)malloc(sizeof(char) *21)
strcpy(p->name, “ss”);
```

### 九、结构体错误的使用方法

```c
SNode L;
create_head_s(&L);
void create_head_s(SNode* L2)
{
    // 这样是错误的
    //1、函数体外已经声明了一个变量L，L已经是一个结构提，
    //L2 等同于 L，这时再给L2赋值，就会替换掉函数体外的L
    L2 = (SNode*)malloc(sizeof (SNode));
}
```

### 十、联合体(共用体)

```c
// 共用一块内存空间，只保留最后一个赋值
// 共用体根据最大的数据类型长度，确定大小
union name 
{
    int a;
    char b;
}；
union name T; //定义一个共用体变量T
T.a = 100;
T.b = 'a'; //因为是共用体，所以只保存最后数据;

// 验证大小端
int check()
{
    union {
        char a;
        int b;
    }u;
    u.b = 1
    return u.a;//返回1小端
}
```

### 十一、结构体指针

1、结构体指针定义

```c
/* 局部变量，结构体指针 */
struct _Player{
    int a;
}
struct _Player *pt;

/* 全局，结构体指针 */
struct _Player{
    int a;
} *pt;
```

2、结构体指针指向

- 结构体与数组不一样，结构体名不是地址，所以获取结构体地址要用&

``` c
// 定义的结构体
typedef struct {
    int a;
} Player;
// A是一个结构体
Player *p = &A;
```

3、访问

```c
typedef struct{
    int a;
}Player;
// 声明2个变量
player *P;
Player *nowp; //声明一个Player类型的结构体

// 使用.运算符
(*p).a = 100;
// 使用->运算符，指针结构体使用（推荐）
nowp->a = 2222;    // -> 指针的成员操作符与.意思相同
```

## 枚举类型

```c
// 枚举类型的值只能是定义的内容，其他内容错误
// 取值内容是有限的
/* 定义 */
//枚举常量是整型int， 默认是从0开始
enum Name{ ADD, QUERY } 
//枚举常量是整型int， 从10开始
enum Name{ ADD = 10, QUERY } 
 // 自定义
enum Name{   
    ADD=1,    //
    QUERY=3,  // 2
}

/* 使用 */
enum Name A;  //定义一个枚举变量A，A只能取name内定义的值
Name A; //也可这样定义
A = ADD //正确
A = 1000 // 错误，没有1000这个值
//调用时直接用ADD
```
