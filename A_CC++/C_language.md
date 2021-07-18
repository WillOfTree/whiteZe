# 补充内容：

1. 对于负数C语言采用补码存放

2. 对于a~Z是用ASII码存放数据，使用printf("%c"，105)可直接输出字符 （char就是特殊的int)

3. 对于浮点数（如1.22）如果要强转int会直接丢掉小数部分，**除法也是丢弃小数部分**

4. 对于不同类型的数据进行运算(1+1.0),编译器会先将占用位小的转换为大的（1.0+1.0）

5. 强制转换: (int)1.2

6. ++a 与 a++ 在赋值操作时有区别（j=++i | j=i++)，单独出现时没区别（++i | i++）

7. 作用域：

   代码作用域：{}

   文件作用域：声明位置～文件末尾

   原型作用域：函数声明的参数列表

   ​	void func(**int, char, int**);

   函数作用域：适合于goto语句

   static:文件作用域生效

8. 定义：给一个变量分配空间，声明：未分配空间

# 内存布局

## 生存期

**静态存储期**-程序执行期间一直占用内存，结束后释放（函数运行完释放）

包含：文件作用域，函数，全局变量

**自动存储期**-代码结束时就自动释放

代码域，{}，void func(**int, char**)

## 链接属性

external:多个文件声明同名标识符是一个，（默认）

internal：单个文件同名标识符

none：

## 存储类型

auto, register, static, extern, typedef

1. auto:代码块中变量默认存储类型，空链接属性（none），代码块作用域，自动存储期

   ```c
   auto int a, b;
   ```

   

2. register:寄存器变量，不是所有的都会存在寄存器中，不能使用取址操作符获取地址

   ```c
   register int a = 500;
   int b = a&; //error
   ```

   

3. static:从多文件共享，变但文件共享;当生命一个局部变量时，局部变量会变成整个文件共享

   ```c
   static int a = 100; // 只改变生存期，不会改变作用域
   
   int b()
   {
       static aa = 1000;
   }
   
   int main()
   {
       aa = 500; //error, 静态aa作用域是b，但aa的生存周期是整个文件
   }
   ```

   

4. extern:全局变量默认也是加在上extern

   

5. typedef

## 内存布局规律

1. 代码段：程序执行代码存放的空间，这部分大小在程序运行前就已经确定，有一些常量也存放在这，字符串常量。
2. 数据段：程序已经初始化的全局变量和局部静态变量
3. BSS段：未初始化的全局变量，自动初始化为0

## 堆

程序运行过程中动态分配的内存段，他的大小并不固定可动态扩展或缩小（malloc等函数）

自己申请

## 栈

函数执行的内存区域，函数参数，返回值，局部变量也是这个区域，通常和堆共享一片区域

系统维护，函数调用开始，调用结束结束

# 宏定义与预处理

## 一、宏定义

宏定义只是简单的进行替换，不进行其他操作，在编译之前处理

**替换**-不带参数

```c
#define IP 3.14
#undef IP  //IP宏定义的作用域

```

**替换**-带参数

```c
#define MAX(x,y) ((x)>(y)?(x):(y))

int main()
{
    MAX(x,y)
}
```



**防止头文件（.h）被多次包含**

```c
#ifndef __luck__MainMenu__  //luck项目名称，MainMenu文件名称
#define __luck__MainMenu__
	//声明函数，结构体定义，初始数据声明
#endif
```

**C语言宏定义**

```c
\*C语言宏定义*\
#ifdef __aplusplus
extern “C” {
	#endif
	.....
	#ifdef __aplusplus
}
#endif
```

**宏函数**
不是真正的函数,宏只是进行了文本替换
宏函数在一定场景下效率高

```c
#define MYADD(x,y) ((x)+(y))

int main()
{
	MYADD(a,b); //相当于替换为(a)+(b)
}
```
## 二、预处理

\#：后应跟一个参数，预处理会将这个参数转换为字符串

\##：记号链接符，可将两个参数链接到一起 

预处理是简单文本替换

```c
#define
#define TOA(x, y) x ## y
//可变参数
#define SHO(...) printf(#__VA__ARGS__)
#define SHO(...) printf(# format, ##__VA__ARGS__)
```

## 三、编译

.c文件经过编译变成.o文件，

.o文件经过连接（与lib库进行关联）变成可执行文件

头文件不参与编译，每一个.c文件叫做编译单元
编译器独立编译每一个.c文件

linux平台下更新链接库lld heal.exe

**编译命令**
```c
gcc 要编译的.c文件 -o file 指定生成输出的文件名  //单文件可直接生产可执行文件
-E 只进行预处理
-S 只进行预处理和编译
-c 只进行预处理，编译和汇编
```

**分步编译分**

1、预处理：宏定义，头文件展开，条件编译等，删除注释，不检查语法 （.i)

```c
gcc -e a.c -o a.i
```
2、编译：检查语法，将预处理后的文件编译成汇编语言(.s)
```c
gcc -s a.i -o a.s
```

3、汇编：生成二进制文件(.o)
```c
gcc -c a.s -o a.o
```
4、链接：将需要使用的库链接到可执行文件中

```c
gcc a.o -o a.exe
```

## 四、多文件联合编程

1、在同一个文件夹中，**所有函数都是全局函数**，所以，在任意文件中定义一个函数，均可以被其他方法调用
2、使用.h文件，.h文件用于声明函数所在的位置

main.h

```c
int a();
int b();
```

main.c

```c
#include "main.h"

int aa;
int main()
{
    a();
    b();
    max();
}
```

A.c

```c
extern int aa;

int max()
{
    aa = aa+ 1; //aa是主文件定义
}
```



3、主函数引用.h文件

编辑器会自动引入文件，对于非编辑器使用命令

```c
gcc -o 可执行程序.exe main.c a.c b.c d.c //其他文件.c  其他头文件.h
gcc main.c a.c b.c d.c 
```





# 变量与常量

## 一、数据类型

C99规定了各个类型的大小关系，但未规定每一数据类型必须有多大，所以，在不同操作系统中各个数据类型大小会不一样，例如：
​	int (4B-32bit)   char(1B-8bit) 
C99默认变量都是有符号位（signed),符号位会占用1bit，无符号（unsigned)

## 二、常量
程序运行中不能被改变的量叫常量
1. 整型常量：520,11,1314
2. 实型常量：3.1414, 444.333
3. 字符串常量："Loveme"
4. 符号常量：#define定义
5. 字符常量：
   - 普通：'L'，'O'
   - 特殊含义：'\n','\t'

**定义方式**
注意：
1、通过#define定义的常量是根据值来匹配数据类型
2、const 定义的常量是不安全的，可以通过指针来修改（C语言中）
3、字符串常量
```c
const int PI = 3.14  // 程序内定义
#define PI 3.14 #符号常量，宏定义

```

## 全局变量

1. 全局变量会自动初始化为0。
2. 当全局变量与局部变量重名时，局部变量有用

```c
int a = 0; //全局
int main()
{
    ...
}
```

## extern

用于声明变量，函数，告诉编译器，这个变量函数已经在后面定义

```c

extern a;
extern func();
```



# 特殊函数运算符

## 一、逻辑运算符

```c
&& //两个数同时为真才为真
|| //有1个为真即为真
！ // 取反
```

短路求值

```c
// 逻辑与，同时为真，其结果为真，如果第一个运算为假，退出运算（第2个运算短路）
(a = 0) && (b = 1); // a=0假， 推出运算(不执行b=1)
(a = 1) && (b = 1); // a=1真， 继续运算（执行b=1)

// 逻辑或，有一个为真即为真，如果第一个为真，推出（第2个运算短路）
(a = 1) || (b = 1); // a=1真， b=1（短路）
(a = 0) || (b = 1); // a=0, b=1, 先运行a=0,假，再运行b=1真，其整体结果为真，a,b都运行
```

## 二、sizeof 运算符
用于计算字符大小（主要因为不同系统，数据类型大小不一样），sizeof是运算符，不是函数

```c
sizeof(object);

//于数组(array)，sizeof(array) 会计算整个数组的大小
sizeof(array); 
	int a[] = {1,2,3,4};
    sizeof(a); //16B, int类型4字节，4个int=16B
    
//对于结构体（struct），sizeof(struct)会计算整个结构体大小\
sizeof(struct);
	SNode *z;
	sizeof(*z); // 打印z对应的结构体大小
	sizeof(z);  //打印z的大小，z是一个指针，固定大小
```

**1、数组做函数参数传递时（数组指针会退化为指针）**

```c
//传递的是指针（因声明是一个指针），所有sizeof(array)只能读取这个指针的大小
void func_01(int a[])
{
	printf(“%d”, a[0]); // 数组a[0],1
	printf(“%d”, sizeof(a)); //会打印指针大小（32位4，64位8 ）
}

// 当函数需要数组大小时，需要多传递1个参数
void func_01(int a[], int size);

int main()
{
	int a[] = {1,2,3}
	func_01(a); //调用函数
    func_02(a, 3);
}
```
**2、结构体做函数参数传递时（结构体指针退化为普通指针）**

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
**计算数组长度C/C++**

//这个如果计算字符串，会算上\0
sizeof(arr) / sizeof(arr[0])

## 内连函数

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

## typedef

优先级高->低

() -- [] -- * --

**起别名**

```c
typedef int A; //重命名int为A
typedef int A, B; //给int起2个别名
typedef char * A; //给char *起一个别名

// 声明一个结构体，一个结构体指针
typeof struct {
	int num;
	int aa[30];
}stu, *stu2;

(stu2)malloc(sizeof(stuo))
```

**简化代码**

比不是起别名

```c
//int (*PTR_TO_ARRAY)[3] 简化为PTR_TO_ARRAY
typedef int (*PTR_TO_ARRAY)[3]; //数组指针别名
PTR_TO_ARRAY array = {1,2,3};

//
typedef int (*PTR_TO_FUN)(void);
void func(void){};
PTR_TO_FUN ptr_to_fun = &func; //使用ptr_to_fun替换int (*PTR_TO_FUN)(void)中的PTR_TO_FUN
(*ptr_to_fun)();


//
typedef int *(*PTR_TO_FUN)()
void func(void){}
PTR_TO_FUN array[3] = {1,2,3}
```



## 枚举类型

特定的数值具有名字

```c
enum Name{ ADD, QUERY } //枚举常量是整型int， 默认是从0开始
enum Name{ ADD = 10, QUERY } //枚举常量是整型int， 从10开始
enum Name{    // 枚举类型的值是根据顺序排列的
	ADD=1,    //
	QUERY=2,  // 2
}
enum Name one;       // 定义一个枚举变量one，one可以是枚举类型其中之一

```

## 位操作符

把字节(1B=8bit)拆开计算，位域一定小于操作系统的位数（32位/64位）

```c
//声明当前结构体，不同元素占用不同的位
struct Player{
	unsigned int a:1; //1位
    unsigned int b:4; //4位
    unsigned int c:3; //3位
    unsigned int :1; //无名位域，站空
}
```

**逻辑位运算符**-对每一个位起作用

```c
&  //两个数同时为真才为真
|  //有1个为真即为真
～  // 取反
^  //异或
```

**移位运算符**

<< 左移,乘法 移1位乘2

\>\> 右移，除法 移1位除2

```c
11001010 << 2 //左移2位 === 00101000
11001010 >> 2 //左移2位 === 00110010

value <<= 1 // value = value << 1;
    
```

## 重定向-shell

< 重定向标准输入

\> 重定向标准输出

2\> 重定向标准错误输出

```shell
$ ./a.exe > output.txt # 输出内容到output.txt
$
$ ./a.exe 2> error.txt # 输出内容到error.txt
$ ./a.exe > out.txt 2> error.txt # 内容输入到out.txt,错误信息到error.txt
```





# 字符串-字符串有函数库(string.h)

字符串：""（双引号表示）
字符： ''(单引号表示)
**编译器会自动在字符串后面添加\0，用于标识字符串结束（与字符不同，字符没有\0）**

字符串(字符串数组)与其他变量（数组）不同，字符串结束于"\0",打印时可直接给字符串(字符串数组)首地址

**声明方法：**

```c
char 名称[N] //声明N个长度的字串

// 赋值方法
char name[4];  //4代表4个容量，不是0～4
name[0] = 'L';
name[1] = 'O';
name[2] = 'V';
name[3] = '\0'; // 防止出现乱码，必填

//错误赋值方法
char name[4];
name = "lov"; //这里name只是一个指向name数组首地址的指针，放不下lov字符
```

**常用声明赋值方法**

```c
//字符串，编译器会自动添加 \0
char name[] = "holle";
char name[10] = "halle";
//字符串数组，手动添加\0
char name[] = {'h','o','l','l','e'，'\0'}; 
char name[10] = {'h','o','l','l','e'，'\0'}; 

//字符串常量定义方式，无法改变
char name[] = "hallo";          

// 字符指针变量,可以改变
char *name = "Hallo";
```

**字符串就是特殊数组**

```c
int main()
{
    char a[128];
    scanf("%d", a); // 字符串就是特殊数组，没有用&，
}
```

**字符串赋值**

一般使用string库，进行字符串操作。

# 数组

数组名是数组一个元素的地址

1. 当访问一个数组名时，打印的是数组首地址，数组第一个元素的地址，a[0]。这3个是一样的，默认选项

## 一维数组
定义：
```c
// 数组类型 名称[个数]
int a[3]; //共定义3个元素，下标为0～2
a[3]; //访问错误，共3个元素，下标0～2 
    
//访问数组元素
b = a[1];

// 不固定长度，根据定义的元素确定数组大小（1个0）
int a[] = {0}
// 未定义的默认都为0
int a[10] = {1,2,3,4}
//C99 指定下标初始化
int a[10] = {
    [2] = 100,
    [3] = 200
}
```

循环与数组关系
```c
for(int i=0; i<10; ++i);
```
**可变数组定义**

```c
int main()
{
    int a;
    scanf("%d", &a)
    int b[a];   //C99 支持
    int b[a-1]; //C99
    /*getchar() 对于某些会多读取一个换行符*/
}
```

## 二维数组

二维数组必须指定列元素个数，不然会报错

定义：

```c
int a[2][4];
a[0][0] = 1;
a[0][1] = 2;
```

```c
int a[1][3] = {1, 2, 3, 4, .....}
//2行3列
int a[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
}

//将每一行第一个元素赋值
int a[2][3] = {
    {1},
    {2}
}

//c99, 指定元素赋值
int a[2][3] = {
    [0][0] = 1,
    [0][2] = 2
}
```

## 输出

对于数组输出，直接给首地址即可，

```c
int a[] = "ABC";
int b = 123;

printf("%d", b); //输出123,

printf("%s", a); //输出ABC，字符串与普通变量不同，可以不用&,他有自己的结束符号
printf("%s", a[0]);  //输出A
printf("%s", &a[0]); //输出ABC
```



# 指针

1. 在同一个编译器下，一个指针变量所占用的内存空间是固定的（32位系统16位），但是一个类型的大小是不固定的（int-4B，char-1B)，这时指针要根据不同的类型读取不同的字节(B) 
2. 指针大小
   无论是什么类型得指针，存的都是地址，内存地址都是无符号整形，都是4字节大小
3. 指针变量存放非地址数据没有实际上的意义

## 声明

```c
int *p;
char *p;

// 指针声明时，一定要指向一个具体的位置，空指针有可能会出现未知错误
int *p = &a;

//错误样列
int *p;
p = 7; // vs2008会提示The variable 'p' is being used without being initialized.即使用了未初始化的变量p。
```
## 取址 / 取值运算符
& 取址运算，获取变量地址

\* 取值运算，获取地址的值（在声明中是定义一个指针，int *p）

*[]也算一种\*运算，基本相当与\*(a+i)*

```c
p = &a  // p中放的是a的地址，（也可以放直接123456，当使用*p时，就会去读取123456地址所在的数据）
*p = 15 // 将P指向的指针，赋值为15
c = *p  //将指针p中的值 赋值给c， c=15
b = &a  // 将地址赋给b,但b不是指针变量，不能使用*
/* 错误用法-溢出
*p=&a // 这里会溢出，不知道指到哪里了 */
    
void * p = &a //万能指针，void
*（int *)p = 100 //当取值得时候要进行类型转换

*必须是指针类型才能使用
int p, b=5;
p=&b; //a中存放地址
printf(*p); //语法错误，只有指针类型才能使用 *
printf(p); // 打印b的地址
```

## 指针运算

指针步长由指针类型决定（char 1B,int 4B)

指针类型的主要作用是确定从内存中根据指针类型确定读取几个字节

当指针指向变量时，可对指针进行加减运算,不是简单的地址加一而是下一个元素

```c
int stu[2] = {1,2};
int *p;

int a = *(p+1) //相当于 stu[1];
    
int *p = stu; //stu是个数组
*p // 指向下标为0的数据
*(p+1) // 指针向后移动2个位置，指向下标为1的数据
*((int *)p +1) //强转int类型，根据int类型确定步长，移动1步，取值
```

## 指针变量左值与右值

数组名只是一个地址，指针是一个左值

数组一定要用[]形式进行操作（或*(p+1)形式），直接对地址是不可以进行++操作

```c
int main()
{
    char *p[] = "ABCDEF";
    while(*p++ != '\0') // 报错
    {
        count++;
    }
}

int main()
{
    char *p[] = "ABCDEF";
    char *p2 = p; 
    while(*p2++ != '\0') // 可以
    {
        count++;
    }
}
```

## 数组与指针

### 指向数组的指针

```c
int stu[2] = {1,2};
int *p;

// 方法1、数组变量名就是地址,
// 特别注意,这里p实际上指向的是stu数组的第一个元素1(stu[0])
p = stu  
// 方法2、stu[0]存放的是首元素，so，要使用 &stu[0]
p = &stu[0]  
```

### 指针数组-本质数组

指针数组是一个数组，每一个数组存放一个指针变量

| 下标 |   0   |   1   |   2   |
| :--: | :---: | :---: | :---: |
|  值  | int * | int * | int * |

```c
int *p[5] //指针数组,[]优先级高于*
    
//初始化
int a, b, c, d;
int *p[4] = {&a, &b, &c, &d};

//常用于字符串
int *p[3] = {
    "11111",
    "AAAAA",
    "ccccc"
};
//使用，printf对于数组，给地址就可以，变量要直接给变量
printf("%s", p[1]); 
```

### 数组指针-本质指针

指向数组的指针

| 下标 |  0   |  1   |  2   |
| :--: | :--: | :--: | :--: |
|  值  | int  | int  | int  |

```c
int （*p）[5] // 指针指向的一个5位数组
    
//初始化
int temp = {1,2,3,4};
int (*p)[4] = &temp; //p是一个指向数组的指针，所以要数组的地址的地址

printf("%s", *(*p+1)); //*p是找到temp的数组内容，
```



### 二维数组

```c
int a[2][3] = { //必须指明列
    {1,2,3}，
    {3,4,3}
}
int (*p)[3] = a; // 二维数组不用&符

printf("%s", *(*p+1));    //a[1]
printf("%s", *(*p+1)+2)); //a[1][2]

```

指针访问二维数组

```c
int main()
{
    int a[2][3] = {
        {1,2,3},
        {4,5,6}
    }
    
    //错误示例
    int **p = a; 
    // 因为**p的指针跨度为4,a的指针跨度为4*3
    printf("%d", *(*(p+1)+2)); // 错误，指针跨度不一样
    
    //正确
    int (*p)[3] = array; //必须指明列
    int (*p)[2][3] = &array; //太复杂，访问时要多加一个*
    
    printf("%d", *(*(a+1)+2)); //a[1][2]
}
```



## 字符串与指针

### 字符指针变量

```c
// 字符指针变量
char *name = "Hallo";

for(i=0;i<10;++i)
{
    //相当于 *(name+i)
    printf("%c", name[i]);
}
```

## 指向指针的指针

```c
int main()
{
    int a = 520;   // a->520;
    int *b = &a;   // b->&a, a->520;
    int **c = &b;  // c->&b, b->&a, a->520
}
```



```c
int main()
{
    char *cbooks[] = {
        "111111", //这里本质上是一个数组
        "222222"
    };
    
    char **A;
    char **B;
    
    A = &cbooks[0]; //cbooks[0]为111111, &cbooks[0]为111111第一个字符的地址（也是11111数组的首地址）
    B[0] = &cbooks[1];
   	
    printf("%s", *A); //A中存放的是11111的地址，所以进行取值操作
    printf("%s", *B[0]); //B[0]中也是存放的地址
}
```

## 常量与指针

```c
int main()
{
    int temp = 000;
    const int A = 123; // A不可修改
    const int *p = &A; 
    int * const PP = &temp //常量指针，pp不可修改
    const int * const ppp = &A; //都不能修改
    
    *p = &temp; //*p不可修改，本质修改的是A
    p = &temp; //p可修改
    *pp = 222; //*PP可修改，本质是temp可修改
    pp = &temp; //错误，pp不可修改
}

```

## 函数与指针

```c
// 函数指针
//int (* pfun)(int a)； // 定义一个函数指针
// 指针函数
int *pfun(int a);
    
//指向一个函数
pfun = func;   // 指向一个函数func， 函数名=函数的地址
pfun = &func;  // 指向一个函数func

//调用
pfun（10）;    // 调用函数，可能是一个变量
(* pfun)(10); // 调用, 明确是一个函数指针
    
int *funaddr = （int*）4199952  //4199952是一个函数的入口地址
void(* myfunc)(参数列表) = funaddr
myfunc(); //调用函数
```

**函数指针做参数**

```c
int func(int (*pfun)(int, int), ...);
int func(int (*)(int, int), ...);
```

**函数指针做返回值**-不全

```c
int (*func(int))(int a, int b)
{
    return (* pfun(int, int ));
}

int main()
{
    int (*fp)(int ,int);
    fp = func(1);
}
```

## void指针

```c
void *p = &a; //不知道a是什么类型

// 要是修改这个万能指针的化，需要强制转换成指定类型
*（char *)p = ‘a’; //char类型是一个字节
```

## 空指针

NULL一般是一个宏定义,当指针不知道指向哪时，指向NULL

```c
#defind NULL ((void *)0)

int *p = NULL;
```

# 函数

## 定义声明：

```c
int func(); //声明，一定在前面
int func(void);
int func(int，....);

int func(){};
int func(void){};
int func(int a, ....){};

extern int add(int a, int b);
```

## 传值

```c
int func(int a, int b){
	printf(“a=%d”, a); //a传递的是值
}  
//函数需要值传递
int main()
{
	int a=10, b=20;
	func(a, b);
}
```

## 传指针
```c
// 地址传递-可以将值带回, 如果a传递的不是地址（&），编译器会报错
int func(int *a, int *b) { // int* a代表定义
	printf(“a=%d”, *a); //因为a是地址，所以要用*
}
int main()
{
	int a=10, b=20;
	func(&a, &b); //取地址
}
```

## 传数组

1. 本质还是传递数组的首地址，在函数内修改数据，主函数也会修改
2. func函数内无法使用sizeof计算大小，需要新添加参数，确定数组大小

```c
// void func_01(int *a, int size) //对于数组，与下面相同
void func_01(int a[], int size)
{
	printf(“%d”, a[0]); // 数组a[0],1
}

int main()
{
	int a[] = {1,2,3}
	func_01(a, 3); //调用函数
	// func_01(&a); //等同于上面
}
```

## 可变参数

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

# 内存管理函数

## 内存池

自己维护的内存，使用单链表记录释放的内存空间(不释放)，当有合适大小的内存，重新使用

## malloc-申请动态空间

在堆中申请内存

```c
/*
void *malloc(size_t size)
申请size类型指针，返回一个void类型的指针，申请的空间数据是随机的
*/

#include<stdlib.h>

//空间存放指针
int *a;
//申请空间，存放到a
a = (int *)malloc(10 * sizeof(int));
//Player结构体动态分配空间
Player * None=（Player *）malloc(sizeof(Player));

//初始化内存空间
// 内存相关操作是mem开头
#include<string.h>
memset(a, 0, 10*sizeof(int)); //用0填充a空间，填充大小为10*sizeof(int)

//释放空间，是一个指针
free（None） 
```

## free-释放空间

必须由malloc,calloc,realloc申请的空间的指针

```c
free(a); //a是一个指针，必须是malloc申请的空间
```



## calloc-自动申请N个空间

动态申请N个长度为size的空间,并自动初始化为0

```c
/*
void *calloc(size_t N, size_t size)
*/
int *p = (int *)calloc(8, sizeof(int));
```

## realloc-重新分配空间

重新分配的空间大，原数据不会丢失

从新分配的空间小，原数据会丢失

```c
/*
ptr 堆空间指针
void *realloc(void *ptr, size_t size) 
*/
int *pt = (int *)realloc(p, 8*sizeof(int));
```



# 结构体

1. 为什么必须使用结构体类型,不用数组

   数组大小，类型是一样的，对于即想存int,又想存char是做不到的

2. 对于结构体内部变量使用，对象一律用.  指针用->,并不是指结构体内部定义类型，而是指结构体类型

   ```c
   struct A {
       int a;
       struct A *b;
   }
   int b;
   
   struct A AA; //结构体对象
   AA.a = 100;
   AA.b = &b;
   
   struct A *BB; //结构体指针
   BB->a = 100;
   BB->b = &b;
   ```

   

3. dd

​	



## 结构体对齐

结构体定义的数据位置不同，大小也不同
创建结构体一定按照由小到大定义
char - short - int - long - double - float
结构体变量，结构体数组，结构体指针
没有直接接打印结构体得方法，如果是指针指向一个结构体，这个指针变量保存得是结构体第一个元素得地址，
栈空间使用方法一

## 声明结构体

不占用空间，注意：结构体内的属性与结构提无关

```c
struct Player{
	int a;
}


// 结构体内属性类型与结构体无关
struct Player{
	int a;
    char b[20];  
}p1;
scanf("%d", &p1.a); // a是一个变量，需要取地址
scanf("%d", p1.b); // b本身就是字符串数组，变量名就是数组地址


// 使用typedef声明结构体，
typedef struct { // 用typedef创建新类型,新类型名为Player
	int a;
}Player
// typedef声明的结构体，定义变量可以少写struct
Player p1;

```

## 定义结构体变量

定义时会占用空间

```c
// 使用Player结构体声明新变量p1
struct Player p1; 

// 直接在声明的时候定义 p1,p2
struct Player{
	int a;
}p1,p2 

// 只生成p1, p2结构体，因为没有名称
struct { //这个结构体并没有标明其标签
	int a;
}p1,p2

// struct定义结构体
typedef struct _Player{
	int a;
}Player;
Player p1;
p1.a = 1;    // 给结构体的属性赋值

```

## 赋值与访问

**初始化**

```c
// 数据类型需要与类型相对应
struct Player p1 = {1, "23444"};
// 指定变量名初始化，C99
struct Player p1 = {.a = 1};

// typedef定义的结构体初始化
Player p1 = {1, "23333"};

// 声明时初始化结构体
struct Player{
	int a;
    char b[20];
}p1 = {1, "3434"}
```

**赋值**

```c
// 定义变量p1
struct Player p1;
// p1赋值
p1.a = 100;


```

**访问**

使用特殊的运算符 . 与 ->

. ：结构体对象

-> : 结构体指针

```c
// 结构体对象
struct Player p1;
printf("%d", p1.a);

// 当结构体指针
struct Player *p2;
printf("%d", p2->a);
```

## 结构体嵌套

必须有结构体名称，不然无法定义结构体内部结构体

```c
struct _P{
    int a;
    int b;
}

typedef struct _Player{
	int a;
	char *b;
	struct _Player *d;  //结构体名主要用于在结构体内定义
    struct _P e;
}Player;
char *p = NULL;
Player PP = {1, p, p2, {1, 2}};

// 访问结构体中的结构体
pp.e.a = 100
pp->d.a = 100
```

**结构体自身指针定义**

```c
typedef struct _Player{
	int a;
    struct _Player e; //无限递归，错误
    struct _Player *e; //正确，指向自己的结构体指针
}Player;

Player p1 = NULL;
p1.a = 100;
p1->e;
```



## 结构体指针

结构体与数组不一样，结构体名不是地址，所以获取结构体地址要用&

```c
// 定义声明
typedef struct _Player{
	int a;
}Player;
// 定义*p变量
struct _player *pt;
Player *p;

//结构体名与数组名不同
// 数组名在表达式中会被转换为数组指针，而结构体变量名不会，无论在任何表达式中它表示的都
// 是整个集合本身，要想取得结构体变量的地址，必须在前面加 &
player p_temp;
pt = &p_temp;
```

**访问**

```c
typedef struct _Player{
	int a;
	char *b;
	struct _Player *d;  //结构体名主要用于在结构体内定义
}Player;
// 声明2个变量
player *P;
Player *nowp; //声明一个Player类型的结构体

// 使用.运算符
(*p).a = 100;
// 使用->运算符，指针结构体使用（推荐）
nowp->a = 2222;    // -> 指针的成员操作符与.意思相同
```

## 结构体数组

每一个数组都是结构体

```c
typedef struct _player{
	int a;
}P[10]; //声明时定义

typedef struct _player{
	int a;
}Player;

struct Player info[30]  // 使用结构体Player 声明一个30容量的info
info[1].a=1;
```



## 结构提传递

```c
typedef struct _Player{
	int a;
	int b;
}Player;
player p1, p2;

p1.a = 1;
p1.b = 2;
// 前提，结构提类型完全一样才能赋值
p2 = p1; 


```

## 结构体函数

**传递结构体变量**-效率低，结构体太大

```c
typedef struct _Player{
	int a;
	int b;
}Player;
player p1;

// 返回一个结构体类型
// 传递一个结构体类型
struct _Player func(struct _Player ptr)
{
    ptr.a = 100;
    return ptr;
} 

int main()
{
    player p1, p2;
    p2 = func(p1);
}
```

**传递结构体指针**-推荐

```c
typedef struct _Player{
	int a;
	int b;
}Player;


// 返回一个结构体类型
// 传递一个结构体类型
struct _Player *func(struct _Player *ptr)
{
    ptr->a = 100;
    (*ptr).a = 200; //与上面的效果相同
    return ptr;
} 

int main()
{
    player p1;
    player *p2;
    
    p2 = func(&p1);
}

```



## 堆空间开辟结构体

```c
// 使用typedef
typedef struct 
{
	char *name;
	int age;
}t;
//开辟堆空间的结构体，sizeof可以直接计算结构体大小
t *p = (t *)malloc(sizeof(t));


// 使用结构体名称
struct tec
{
	char *name;
	int age;
}t; 
// 对比组，t是一个声明时定义的结构体
t.name = (char *)malloc(sizeof(char) *21);
t.age = 100;

//开辟堆空间的结构体，sizeof可以直接计算结构体大小
struct tec * p = (struct tec *)malloc(sizeof(struct tec));
struct tec * p = (struct tec *)malloc(sizeof(t));
// 给结构体内变量申请21个char类型空间
p->name = (char *)malloc(sizeof(char) *21)
strcpy(p->name, “ss”);


```

结构体数组

```c
struct tec
{
	char *name;
	int age;
}t;

// 开辟3个连续空间的结构体
struct tec * d = (struct tec *)malloc(sizeof(t) * 3);
d[0]->name = (char*)malloc(sizeof(char) * 21)
strcpy(p[0]->name, “ss”);
```



## 联合体

共用一块内存空间，只有最后一个值赋值时准确的

共用体根据最大的数据类型长度，确定大小

```c
union name
{
	int a;
    int b;
}；
union name T; //定义一个共用体变量T
T.a = 100;
T.b = 200; //因为是共用体，所以只保存最后数据，200;

union name T = {520};
union name T2 = T;
union name T3 = {.a = 200};
    

```

## 结构体错误的使用方法

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

# 文件操作

## 操作符

1. r：只读模式，文件必须存在，从头写入
2. w：写模式，文件不存在创建，从头写入
3. a：追加模式，文件不存在创建
4. r+：读写模式，文件必须存在，从头写入，不是完全覆盖，有几个字符覆盖几个
5. w+：读写模式，文件不存在创建，从头写入，覆盖所有内容
6. a+：读和追加模式，文件不存在创建，在末尾添加
7. b：二进制文件读写，不会对\r\n进行转换，其他会自动进行转换

## 打开文件

```c
#include <stdio.h>
int main()
{
    FILE *f;
    int ch;
    
    if(f = fopen("xxx.txt"， "r") == NULL); //没有路径指与本文件在同一目录
    	printf("打开失败");
    
    // EOF 宏定义结束
    while((ch = getc(f)) != EOF) //ch为什么是int,不是char,因为getc函数问题
    {
        putc(ch);
    }
    
    // 结束后才能清空缓冲区
    fclose(f);
}
```

## 位置指针

## 文件流

1. 标准输入流(stdin)
2. 标准输出流(stdout)
3. 标准错误流(stderr)

```c
#include <stdio.h>
int main()
{
    FILE *f;
    int ch;
    
    if(f = fopen("xxx.txt"， "r") == NULL)
    {
        fputs("打开失败", stderr); //标准错误输出流
    }	  
  
}
```

