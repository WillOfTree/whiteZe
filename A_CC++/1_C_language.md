# 一、补充内容：

1. 对于负数C语言采用补码存放，正数原，反，补相同

2. 0 表示假，非 0 为真

3. 对于a~Z是用ASII码存放数据，使用printf("%c"，105)可直接输出字符 （char就是特殊的int)

4. 对于浮点数（如1.22）如果要强转int会直接丢掉小数部分，**除法也是丢弃小数部分**

5. 对于不同类型的数据进行运算(1+1.0),编译器会先将占用位小的转换为大的（1.0+1.0）

6. 强制转换: (int)1.2

7. ++a 与 a++ 在赋值操作时有区别（j=++i | j=i++)，单独出现时没区别（++i | i++）

8. 作用域：
   
   代码作用域：{}
   
   文件作用域：声明位置～文件末尾
   
   原型作用域：函数声明的参数列表
   
   ​    void func(**int, char, int**);
   
   函数作用域：适合于goto语句
   
   static:文件作用域生效

9. 定义：给一个变量分配空间，声明：未分配空间

10. 单位
    
    bit / 比特位 / bit ：二进制一个数的单位（00000001）
    
    Byte / 字节 / B：8个bit

11. 转义字符 \d - 八进制，\x - 十六进制

12. 除法运算中，运算符左右都是整数，结果也是整数，不依据变量类型。要得到小数则要有一个数时小数。%取余数

13. if else中else与离的最近的if匹配，

14. 0x一位等于4个二进制位

# 二、内存布局

## 链接属性

external：多个文件声明同名标识符是一个，（默认）

internal：单个文件同名标识符

none：

## 存储类型

auto, register, static, extern, typedef

1. auto：代码块中变量默认存储类型，空链接属性（none），代码块作用域，自动存储期
   
   ```c
   auto int a, b;
   ```

2. register：寄存器变量，不是所有的都会存在寄存器中，不能使用取址操作符获取地址
   
   ```c
   register int a = 500;
   int b = a&; //error
   ```

3. static：
   
   修饰局部变量：改变了局部变量的生存周期，只有第一次定义有效，多次定义无效。
   
   修饰全局变量：使全局变量只能在当前文件（.c）中使用，改变了连接属性
   
   修饰函数：使函数只能在当前文件（.c）中使用，改变了连接属性

4. extern：<mark>全局变量默认也是加在上extern</mark>

5. typedef

# 预定义符号

```c
#include <stdio.h>
__FILE__ 进行编译的源文件地址
__LINE__ 文件当前的行号
__DATE__ 文件被编译的日期
__TIME__ 文件被编译的时间
__STDC__ 如果编译时标准c（ansi c），值为1
__FUNCTION__ 当前函数名
```

# 四、变量与常量

## 1、数据类型

C99规定了各个类型的大小关系，但未规定每一数据类型必须有多大，所以，在不同操作系统中各个数据类型大小会不一样，例如：
​    int (4B-32bit)   char(1B-8bit) 
C99默认变量都是有符号位（signed）符号位会占用1bit，无符号（unsigned)

## 2、常量

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

## 3、全局变量

1. 全局变量会自动初始化为0。
2. 当全局变量与局部变量重名时，***局部变量有用***
3. 全局变量作用范围：整个工程（不同文件，要用extern声名）

```c
int a = 0; //全局
int main()
{
    ...
}
```

## 4、extern

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

# 五、特殊函数运算符

## 1、逻辑运算符

```c
&& //两个数同时为真才为真
|| //有1个为真即为真
！ // 取反
^  // 异或操作，相同为0不同为1
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

## 2、sizeof 运算符

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

## 3、内连函数

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

## 4、typedef 类型重定义

优先级高->低

() -- [] -- * --

**起别名**

```c
typedef int A; //重命名int为A
typedef int A, B; //给int起2个别名
typedef char * A; //给char *起一个别名
typedef unsigned int u_int //给unsigned int 重命名为u_int

// 声明一个结构体，一个结构体指针
typedef struct {
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
//使用ptr_to_fun替换int (*PTR_TO_FUN)(void)中的PTR_TO_FUN
PTR_TO_FUN ptr_to_fun = &func; 
(*ptr_to_fun)();


//
typedef int *(*PTR_TO_FUN)()
void func(void){}
PTR_TO_FUN array[3] = {1,2,3}
```

## 6、位操作符

把字节（1B = 8bit）拆开计算，位域一定小于操作系统的位数（32位/64位）

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

<< 左移，乘法 移1位乘2

\>\> 右移，除法 移1位除2

```c
11001010 << 2 //左移2位 === 00101000
11001010 >> 2 //左移2位 === 00110010

int a = 1;
int a = a << 1; //000 000 01 向左移1位
```

## 7、重定向-shell

< 重定向标准输入

\> 重定向标准输出

2\> 重定向标准错误输出

```shell
$ ./a.exe > output.txt # 输出内容到output.txt
$
$ ./a.exe 2> error.txt # 输出内容到error.txt
$ ./a.exe > out.txt 2> error.txt # 内容输入到out.txt,错误信息到error.txt
```

## 8、三目操作符

```c
exp1 ? exp2 : exp3
exp1为真，运行exp2，
exp1为假，运行exp3
```

## 9、逗号表达式

```c
//从左向右依次计算，整个表达式的结果是最右边的值
int d = (a=b+2, c=a-4, b=c+2)
// b为3
```

# 六、字符串数组

字符串：""（双引号表示）
字符： '' (单引号表示)
**编译器会自动在字符串后面添加\0，用于标识字符串结束（与字符不同，字符没有\0）**

字符串（字符串数组）与其他变量（数组）不同，字符串结束于"\0"，打印时可直接给字符串（字符串数组）首地址

**声明赋值方法**

```c
// 赋值方法
char name[2];  //2代表2个容量，不是0～2
name[0] = 'L';
name[1] = '\O';
// 错误赋值方法
char name[4];
name = "lov"; //这里name只是一个指向name数组首地址的指针，放不下lov字符

/*  -----常用方法---- */
// 字符串常量，无法改变,编译器会自动添加 \0
char name[] = "holle";
char name[10] = "halle";
// 字符串数组，必须手动添加 \0，不然会打印出乱码 
char name[] = {'h','o','l','l','e'，'\0'}; 
char name[10] = {'h','o','l','l','e'，'\0'}; 
// 字符指针变量,可以改变
char *name = "Hallo";
```

**字符串赋值 / 字符串求长度**

求长度时应使用strlen()函数进行，不能使用sizeof运算符

字符串赋值建议使用函数库，不然要一位一位的赋值

# 七、数组

```c
/*
数组名：a[0]的地址、数组首元素地址。
&数组名：取出的是数组的地址，并不是首地址，使用数组指针存放
*/
/* 整数组的地址 */
printf("%p", &arr);
printf("%p", &arr[0]);
/* 取出首元素地址 */
printf("%p", arr); //arr数组名
printf("%p", arr[0]);
//--------------区别
printf("%p", &arr+1);//会加整个数组的大小
printf("%p", arr+1); // 数组中下一个元素，例a[0]->a[1]
```

## 1、一维数组

```c
//共定义 3 个元素，下标为 0～2
int a[3]; 
// 不固定长度，根据定义的元素确定数组大小（1个0）
// 注意：{}中有几个元素，设置几个元素，其他未设置为空
int a[] = {0}
// 未定义的默认都为0
int a[10] = {1,2,3,4}
//C99 指定下标初始化
int a[10] = {
    [2] = 100,
    [3] = 200
}
```

**变长数组**-数组的n是变量

```c
// 一定时C99才可以
int b[a];   //C99 支持 
int b[a-1]; //C99
/* 错误定义，n不能时常量 */
const int n = 10;
int arr[n] = {0}; 
```

## 2、二维数组

```c
//定义赋值1：二维数组必须指定列元素个数，不然会报错
//注意：{}中有几个元素，设置几个元素，其他未设置为空
int a[1][3] = {1, 2, 3, 4, .....}
//定义赋值2：2行3列
int a[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
}
//定义赋值3：将每一行第一个元素赋值
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

## 3、柔性数组

```c
//C99中允许结构体最后一个元素时未知大小的数组，这就是柔性数组
// sizeof不包含柔性数组大小
// 除柔性数组外，还应有一个变量
// 柔性数组大小使用molloc创建
struct a {
    int b; //必须有一个成员
    int a[];// 大小未知，柔性数组
}
struct a {
    int b;
    int a[0];// 写法二、大小未知，柔性数组
}

// 使用,int大小+柔性数组的大小
struct a *ps = malloc(sizeof(struct a)+10*sizeof(int))
ps->b = 100;
for(i=0;i<10;i++)
{
    ps->a[i] = i
}
// 增加柔性数组
ps = realloc(ps, sizeof(struct a)+20*sizeof(int))
```

# 八、指针

指针类型选择：根据你想怎么操作指针

## 1、定义 / 取址 / 取值运算符

& 取址运算，获取变量地址

\* 取值运算，获取地址的值（**在声明中是定义一个指针,例：int* p = a**）

*[] 也算一种\*运算，基本相当与\*(a+i)*

```c
/* 定义 */
//由类型关键字与*共同组成定义，其他任何时候都为取值运算
int* p; 
int a = 10; //普通定义

/* 取地址运算 */
p = &a;
/* 取值运算 */
a = *p; 

/*---- 错误用法---- */
* p = &a; // 错误用法 
int* p = &a; //这是正确的
p = 1000; // 严禁向指针变量存放非地址数据
printf(*a); //*必须对指针变量使用
a=&b; //普通变量中存放地址,不会错误，但没有意义
/*----------------------*/
```

## 2、指针运算

```c
/* 指针类型确定指针读取的数据大小 */
int *p = stu; //stu是个数组
*p // 指向下标为0的数据
*(p+1) // 指针向后移动2个位置，指向下标为1的数据，相当于 stu[1]
*((int *)p +1) //强转int类型，根据int类型确定步长，移动1步，取值

/* 指针相减，得到指针之间的元素个数（2个指针是同一个类型） */
int *p1 = str[9];
int *p2 = str[0];
p1-p2
```

## 3、指针变量左值与右值

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

## 5、空指针 / 野指针 / void指针

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

## 6、指针数组

```c
/*  []优先级高于*  */
// 先得到p[5]，再变成指针，存放指针类型的数组
int *p[5] 

//初始化
int a, b, c, d;
int *p[4] = {&a, &b, &c, &d};

// 常用于字符串
int *p1[3] = {"11111","AAAAA","ccccc"};
printf("%s", p1[1]); 
// 模拟二维数组
int a[] = {1,2,3} ;
int *p2[3] = {a, b, c}; //abc是一维数组名
//使用，printf对于数组，给地址就可以，变量要直接给变量
printf("%s", p2[1][1]);
```

## 7、数组指针

```c
/* 定义 */
int (*p)[5] 
/* 初始化 */
int temp = {1,2,3,4};
//&temp是temp整个数组的指针，与temp、temp[0]数组首元素的地址不同
//所以要用特别的类型存放数组指针
int (*p)[4] = &temp; 
/* 读取 */ 
p+1; // 跳过一个数组
printf("%d", *((*p)+1) ); //(*p)是找到temp的数组内容，
```

**二维数组-常用**

```c
int a[2][3] = { //必须指明列
    {1,2,3}，
    {3,4,3}
}
int (*p)[3] = a; // 二维数组不用&符
// *(p+1) 相当于a[1], *(*(p+1)+2)相当于a[1][2]
printf("%s", *(*(p+1)+2) ); 
```

指针访问二维数组

```c
    //正确
    int (*p)[3] = array; //必须指明列
    int (*p)[2][3] = &array; //太复杂，访问时要多加一个*
    print01(&a, 2, 3);
```

## 8、常量字符串

```c
/* 定义，不能修改，内存中只存放1份 */ 
char *name = "Hallo";
const char *name = "Hallo"; //一些编译器是要加const
/* 修改 */
*name = "word"; //指针修改禁止
name = "xxxxxx"; //可以修改
/* 打印 */
printf("%s", name);
printf('%c', *name); // 会打印H，name中放的是首地址

//相同，str1,str2中都是放的H的首地址
char *str1 = "H";
char *str2 = "H";
//不同，str3,str4是重新开辟了空间
char str3[] = "H";
char str4[] = "H";
```

## 9、指向指针的指针

```c
int main()
{
    int a = 520;   // a->520;
    int *b = &a;   // b->&a, a->520;
    int **c = &b;  // c->&b, b->&a, a->520
}

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

## 10、常量与指针

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

## 11、函数与指针

```c
注意：函数名 = &函数名；与数组不同
/*----------函数指针-存放整个函数的指针，本质是函数 */ 
//定义
int (* pfun)(int, int)；
//赋值，func是一个函数名
pfun = &func;
pfun = func; //&func与func完全相同
//调用-3种调用方法
(*pfun)(10, 20); //(*pfun)中的*没有实际意义也可以写(*********pfun)
pfun(10, 20);//func === pfun
func(10, 20);//常用

/*错误写法*/
// 相当于把pfun函数的返回值进行解引用操作
int *pfun(int a);
```

## 12、结构体指针

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

# 九、函数

## 1、定义声明：

```c
//声明，一定在前面，没有{}
int func(); //
int func(void);
int func(int，....);

//定义，带{}
int func(){};
int func(void){};
int func(int a, ....){};

//不同文件的声名
extern int add(int a, int b);
```

## 2、传值

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

## 3、传指针

```c
// 地址传递-可以将值带回, 如果a传递的不是地址（&），编译器会报错
int func(int* a, int* b) { // int* a代表定义
    printf(“a=%d”, *a); //因为a是地址，所以要用*
}
int main()
{
    int a=10, b=20;
    func(&a, &b); //取地址
}
```

## 4、传数组

指针大小在传递的时候，不区分类型，大小都是固定的4或8

```c
/*----------------- 一维数组------------ */
//定义
void init(int a[]);
void init(int *a); //一级指针传参
//调用
int arr[10] = {0};
init(arr);
/* 数组指针传递 */
//定义
void init(int *arr[20])
void init(int *arr[])
void init(int **arr)
//调用
int *arr[20] = {0};
init(arr)

/*------------------ 二维数组------------ */
//注意ROW要显式表示，不能隐藏
//定义
void init(int a[COW][ROW]);//正确
void init(int a[][ROW]); //正确
void init(int (*a)[ROW], int i, int j);//数组指针传递方法
// 错误
void init(int a[][]);
//调用1
int arr[3][5] = {{1,2}, {3,4}};
init(arr);

/*----------------------其他------------*/
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

## 9、传结构体

```c
typedef struct _Player{int a;}Player;

struct _Player *func(struct _Player *ptr, struct _Player p)
{
    // 指针
    ptr->a = 100;
    (*ptr).a = 200; //与上面的效果相同
    //结构体变量
    p.a = 100;
    // 返回结构体类型
    return ptr;
} 

int main()
{
    player p1, *p2;
    //&p1传指针（推荐），p1传结构体
    p2 = func(&p1, p1);
}
```

## 5、可变参数

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

## 6、传函数 / 回调函数

```c
/*------------------- 传函数 */
// 定义，函数做参数
int func(int (*pfun)(int, int), ...);
int func(int (*)(int, int), ...); //无法调用，没有函数名
//调用
int func(int (*pfun)(int, int), int a)
{
    pfun(1,2); //函数内调用
}

/*------------------ 函数返回一个函数指针*/
int func(int a, int b)
{
    return (*pfun)(int, int); //返回指针
}

int main()
{
    int (*fp)(int ,int);
    fp = func(1);
}  
```

## 6、回调函数

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

# 十、自定义类型

## 结构体

### 1、结构体对齐

```c
//修改默认对齐数
#pragma pack(2)
#pragma pack() //取消默认对齐
// 小空间的尽量放在一起
struct {
    char a;
    char b;
    int c;
}
// 
```

### 2、声明 / 定义结构体

```c
// 方法一 ----------------------------------------
/* 声明，不占用空间 */
struct Player{
    int a;
}
/* 定义，占用空间，局部变量 */
struct Player p1; 

// 方法二 ------------------------------------------
/* 在声明的时候定义,而且是全局变量 */
struct Player{
    int a;
}p1,p2 

// 方法三 ------------------------------------------
/* 无名结构体 */ 
struct { //这个结构体并没有标明其标签
    int a;
}p1,p2  //只生成p1, p2这2个可用
```

### 3、typedef重命名

```c
/* 无名结构体，常用 -------------------------------------------*/
typedef struct { // 用typedef重命名，新类型名为Player
    int a;
}Player
// typedef声明的结构体，定义变量可以少写struct
Player p1;

/* 有名结构体，多写一个名字 ------------------------------------*/
typedef struct _Player{
    int a;
}Player;
Player p1 = {1, "23333"};/* typedef定义的结构体初始化 */ 
```

### 4、初始化

```c
/* 局部变量 */
// 数据类型需要与类型相对应
struct Player p1 = {1, "23444"};
// 指定变量名初始化，C99
struct Player p1 = {.a = 1};

/*全局变量，声明时初始化结构体 */ 
struct Player{
    int a;
    char b[20];
}p1 = {1, "3434"}
```

### 5、访问 / 赋值

```c
/* 结构体对象，使用 . 来访问 */ 
struct Player p1; //定义的结构体不是指针类型
p1.a = 100; //赋值
printf("%d", p1.a); //访问

/* 结构体指针，使用 -> 来访问 */ 
struct Player *p2; //定义的结构体是一个指针类型
p1->a = 100; //赋值
printf("%d", p2->a); //访问
```

### 5、结构体嵌套

```c
//结构体引用---------------------------------------------
// 必须有结构体名称，不然无法定义结构体内部结构体
struct _P{
    int a;
}

typedef struct _Player{
    int a;
    struct _P e;        // 结构体引用
}Player;

//结构体自引用-------------------------------------------
typedef struct _Player{
    struct _Player e;  //无限递归，错误
    struct _Player *e; //正确，找到和自己同类型的指针，并不是自己
}Player;
```

### 7、结构体数组

```c
//
typedef struct _player{
    int a;
}P[10]; //声明时定义

typedef struct _player{
    int a;
}Player;

struct Player info[30]  // 使用结构体Player 声明一个30容量的info
info[1].a=1;
```

### 10、堆空间开辟结构体

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

### 12、结构体错误的使用方法

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

## 联合体(共用体)

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
enum name A  //定义一个枚举变量A，其值只能取name内定义的值
//调用时直接用ADD
```

## 位段

```c
// 位段成员必须是 int、unsigned int、signed int、 char
// 位段的成员后面有一个冒号和数字
// 每次开辟空间是4字节，最大不能超过类型大小（int，4字节）
// 位段不能跨平台
struct A {
    int a:2; //a占2个比特位（bit）
    int b:3; //b占3个比特位（bit）
}
```
