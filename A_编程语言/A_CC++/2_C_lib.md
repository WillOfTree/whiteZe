# C语言函数库

## 一、IO函数

### printf-格式化打印

- 头文件：#include<stdio.h>

- 字符串输出到 \0

- | 格式符 | 说明                                         |
  | :----: | -------------------------------------------- |
  |   %d   | 十进制整数输出                               |
  |   %u   | 无符号十进制输出                             |
  |   %o   | 无符号八进制输出，不输出前导符：0            |
  |   %X   | 无符号十六进制（大写）输出，不输出前导符：0x |
  |   %x   | 无符号十六进制（小写）输出，不输出前导符：0x |
  |   %c   | 输出1个字符                                  |
  |   %s   | 输出字符串                                   |
  |   %f   | 十进制浮点型输出                             |

```c
/** 
原型：
	printf("字符串")
	printf(格式控制字符，参数列表)
*/
printf("XXXXXX");
printf("%s", ch);  // string 字符数组，特殊，放指针结束到\0

/* 字符数组 */
char a[] = "ABC";
printf("%s", a); // 输出ABC，数组与普通变量不同，变量名就是首地址
printf("%s", a[0]);  // 输出A
printf("%s", &a[0]); // &数组名，取出的是数组地址，输出ABC
```

考试常用

- \+ 显示正负号（默认不显示+号）
- \- 向左对齐（-号数轴左边是负数，正常向右对齐）
  1. 默认：0x10
  2. 向左对齐：0x000010
- 0 使用0补足位数，其他字符均不能补位，不产生效果
- \# 输出字符类型的符号（8进制O，16进制Ox）

``` c
/*
%[正整数][类型] ：输出指定个字符
若正整数小于要输出的字符串长度，则所有设定无效，只正常输出字符
符号位也是 正整数 设定的一部分
*/
printf("\n*s1=%1s*", "ssssss6"); // 直接输出sssss6,
printf("\n*s1=%-1s*", "ssssss6");// -号失效，直接输出sssss6

// b为负数，输出-0023456，而不是00-23456
printf("b=%+8ld\n", b);
```

### scanf-格式输入

- 头文件：#include<stdio.h>

- 返回值：

  成功：指定的数据项

  失败：EOF，在stdio中定义为-1

- | 格式符 | 说明                                                  |
  | :----: | ----------------------------------------------------- |
  |   %d   | 十进制整数                                            |
  |   %o   | 八进制                                                |
  |   %x   | 十六进制                                              |
  |   %c   | 输入1个字符，空白字符、回车、空格、制表符也是有效输入 |
  |   %s   | 输入字符串，空格回车制表符代表输入结束                |

```c
/**
原型：
	scanf("字符控制列表", 地址)
vs2019取消scanf函数错误提示：
	方法1：#define _CRT_SECURE_NO_WARNINGS 1
	方法2：使用scanf_s替换scanf
*/
scanf("%d", &a); 

/* 样例 */
int a;
scanf("%d", &a); // a是一个变量，需要取地址
/* 数组样例 */
int b[10];
scanf("%d", b); // b本身就是字符串数组，变量名就是数组地址
```

考试内容

- 空格、回车、tab都代表输入结束
  
  1. 特殊1：%c会读取空格、回车、tab字符，并不会认为输入结束；
  
  2. 特殊2：%s不会读取空格、回车、tab字符；
  
  3. 特殊3：含有格式符以外的字符：完全符合样式才可以运行
  
     例如：scanf("a=%d,c=%c",&a,&c);

``` c
/*
scanf不能指定精度，只能指定输入多少位
*/
scanf("%6.1f", &a)；//错误
scanf("%6f", &a); //正确，输入的6位有效（包含小数点）
// 输入32.33，只能读取32.3
scanf("%4f", &a); 

/*
%c不需要添加分隔符，会读取 空格
输入：A 空格 B 空格 C
*/
//读取A 空格 B
scanf("%c%c%c", &a,&b,&c);
```

### getchar-字符输入

- 头文件：#include<stdio.h>
- Describe：C语言函数库中专门用于字符输入的函数，每次读取1个字符，回车为为止（回车也会被读取）

``` c
#include<stdio.h>
// 读取1个字符
char ch;
ch = getchar();

// 读取多个字符,需要开辟一个连续空间
char ch[10];
for(int i=0;i<8;i++)
{
    ch[i] = getchar();
}
```

### putchar-字符输出

- 头文件：#include<stdio.h>
- 描述：输出指定字符

``` c
#include<stdio.h>
//ch是字符变量
putchar(ch);
putchar('\n');
```



## 二、字符串函数

### strlen-求字符串长度

```c
/* 头文件 */
#include <string.h>

/* 使用 */
// strlen会一直数到 \0 为止，从而计算字符个数，不包含 \0
char a[] = "Love";
printf("%d", strlen(a)); 
char a[] = {'1', '2'};
printf("%d", strlen(a)); //不确定的个数，a中没有 \0 

/* 返回 */
// 无符号整型 unsigned int
// 因为strlen返回的是无符号整型，所以负数会变成很大的数
strlen("abc") - strlen("abcde") > 0
```

### strcpy-字符串赋值

```c
/* 头文件 */
#include <string.h>

/* 定义 */
//strcpy会以 \0 为拷贝的终止
//会拷贝\0
//将source指向的字符复制到destination指向的变量
char *strcpy(char *destination, const char *source)

/* 使用，将b赋值给a */
strcpy(a, b);
/* 将xxxxx赋值给a */
strcpy(a, "xxxxxx");

/*错误1*/
char a[] = {"1", "2"}
strcpy(b, a);// 错误，a没有结束字符
/*错误*/
char *a = "xxxxx";
strcpy(a, "ab");//a是常量不可修改
```

#### 错误：C6054

详情：可能没有为字符串"XXX"添加字符串零终止符的警告

解决方案：

``` c
// 方案1,在声明的时候初始化全为0, 
// 为什么不添 '\0' 因为ASKII吗中 0 既是'\0'
char A[10] = {0};
// 方案2，后期手动添加
char B[10];
scanf_s("%s", B, 10);
B[9] = 0;
```



### strcat-字符串追加

```c
/* 头文件 */
#include <string.h>

/* 定义 */
//source必须以 \0 结束，source中的 \0 不会拷贝 
//destination必须有足够的空间
//将source指向的字符追加到destination指向的变量
char *strcat(char *destination, const char *source)

/* 使用 */
char arr[20] = "hallo"
strcat(a, "world"); // a为 halloworld
strcat("hallo", "world"); // a为 halloworld

/*错误*/
strcat(a, a); //不能自己追加自己，因为 \0 被去掉了
```

### strcmp-字符串比较

```c
/* 头文件 */
#include <string.h>

/* 定义 */
// 不是比较字符的长度，而是每个字符依次对比，先大的字符大
// 比较的字符ASCII码
// 返回值：
// 0：str1 = str2
// 1: str1 > str2;
int *strcmp(const char *str1, const char *str2)

/* 使用 */
char *str1 = "abc";
char *str2 = "abcd";
```

### strncpy

```c
/* 头文件 */
#include <string.h>

/* 定义 */
// 从source字符串中拷贝num个字符串到destination中
int *strncpy(char *destination, const char *source, size_t num)

/* 使用 */
strcpy(a, b, 5);
```

### strncat

```c
/* 头文件 */
#include <string.h>

/* 定义 */
//destination必须有足够的空间
//将source指向的字符,前n个追加到destination指向的变量
char *strcat(char *destination, const char *source, size_t num)

/* 使用 */
strncat(arr, "hallo", 2);
```

### strncmp

```c
/* 头文件 */
#include <string.h>

/* 定义 */
// 不是比较字符的长度，而是前num个字符依次对比，先大的字符大
// 比较的字符ASCII码
// 返回值：
// 0：str1 = str2
// 1: str1 > str2;
int *strcmp(const char *str1, const char *str2, size_t num)
```

### strstr-在字符串中找其他字符串

```c
/* 头文件 */
#include <string.h>

/* 定义 */
// 在str1中查找str2中指定的字符
// 查找到相同的字符串，返回字符串第位的地址，找不到返回空
int *strstr(const char *str1, const char *str2)

// 使用
char arr1[] = "abcdef";
char arr2[] = "cde";// 要查找的字符
char *ret = strstr(str1, str2);
if(ret == NULL) printf("没找到")
```

### strtok-切割字符串

```c
/* 头文件 */
#include <string.h>

/* 定义 */
// sep 分割符的集合， str被切割的字符串
// strtok 会改变字符串（将切割的标识符变为\0），所以应做好备份
// 一次调用，切割1次
int *strtok(char *str, const char *sep)

// 使用
char arr[] = "tianxia2_wish@126.com"
char *p = "@.";
strtok(arr, p); //只切一次，tianxia2_wish \0 126.com

// 第二次调用strtok如果str,为空，他会继续切割第一次的字符串
strtok(arr, p); //第一次tianxia2_wish ， 126.com
strtok(NULL, p); //切割为 126, com

// 常用
char temp = "tianxia2_wish@126.com"
char *p = "@.";
char *ret = NULL;
for(ret = trtok(temp, p); ret!=NULL; ret=ssstrtok(NULL, p))
{
    printf("%s", ret)
}
```

## 字符处理函数

- 头文件：#include <ctype.h>

| 函数     | 如果参数符合下列添加返回真 |
| -------- | -------------------------- |
| iscntrl  | 任何控制字符               |
| isspace  | 空白字符\n \f \r等         |
| isdigit  | 0-9                        |
| isxdigit | 十六近制0-9                |
| islower  | a-z                        |
| isupper  | A-Z                        |
| isalpha  | a-z，A-Z                   |
| isalnum  |                            |
| ispunct  |                            |
| isgraph  |                            |
| isprint  |                            |

## 内存函数

为什么要有内存函数，因为字符串库等其他，有缺陷如strcpy不能复制数组

### malloc-堆空间申请动态空间

- 头文件：#include<stdlib.h>

- 说明：

  1、malloc申请的空间内并不是空白的，而是随机内容

  2、malloc创建二维数组，是使用一维数组指向另外的一维数组构成的二维数组

```c
/*
原型：
	void *malloc(size_t size)
*/
// 一般使用方法，不同类型对应不同的指针
int *a = (int *)malloc(10 * sizeof(int));
char *a = (char *)malloc(10 * sizeof(char));
//Player结构体动态分配空间
Player *a=(Player *)malloc(sizeof(Player));

//使用memset初始化内存空间
#include<string.h>
memset(a, 0, 10*sizeof(int)); //用0填充a空间，填充大小为10*sizeof(int)

/*
malloc创建二维数组
*/
//利用二级指针
//1、**arr一定要与malloc的类型一样
//2、sizeof(int*)是创建的箱子里存放什么类型，*10是10个
int **arr = (int**)malloc(sizeof(int*)*10);
for(i=0; i<10; ++i){
    // malloc创建的空间，不能使用[]进行赋值,但可以使用[]取值
    //arr[i] = (int*)malloc(sizeof(int)*10);
    *(arr+i) = (int*)malloc(sizeof(int)*10);
}

//利用数组指针
// 创建一个3行2列的数组
// int(*)[]是数组指针的类型
int (*arr)[2] = (int(*)[])malloc(sizeof(int)*3*2)；
// 直接使用即可
arr[1][2];
```

### free-释放空间

- 头文件：#include<stdlib.h>
- 必须由malloc，calloc，realloc申请的空间的指针

```c
free(a); //a是一个指针，必须是malloc申请的空间
```

### calloc-自动申请N个空间

- 动态申请N个长度为size的空间,并自动初始化为0

```c
/*
void *calloc(size_t N, size_t size)
*/
int *p = (int *)calloc(8, sizeof(int));
```

### realloc-重新分配已分配的空间

- 重新分配的空间大，原数据不会丢失
- 重新分配的空间小，原数据会丢失

```c
/*
void *realloc(void *ptr, size_t size)

ptr  ：已分配空间的指针
size ：空间大小
*/
int *pt = (int *)realloc(ptr, 8*sizeof(int));
```

### memset-内存设置

```c
#include <stdlib.h>

// 定义
// 将指定位置buffer，使用字符c填充，填充个数是num
// num单位字节
void *memset(void *buffer,int c,int count);

/* 例子 */
int *p = NULL;
memset(p, 0, sizeof(int)*10);
```

### memcpy-内存拷贝(不支持重叠)

```c
#include<stdlib.h>

// 定义
// 将source复制到destination中，num定义复制大小
// num单位是字节，需要自己计算字节大小
// 拷贝不重叠的内存空间
void *memcpy(void * destination, const void *source, size_t num)

// 使用
int arr1[10] = {1,2,3,4,5,6,7,8}
int arr2[10] = {0}
//复制20字节，int 1个数4字节，20字节复制5个int
memcpy(arr2, arr1, 20)；

//arr中数据为{1,2,1,2,1,2,1,8}
memcpy(arr+2, arr, 20)
```

### memmove-内存拷贝(重叠)

```c
#include<stdlib.h>

// 定义
// 将source复制到destination中，num定义复制大小
// num单位是字节，需要自己计算字节大小
// 拷贝重叠的内存空间
void *memmove(void * destination, const void *source, size_t num)

// 使用
int arr1[10] = {1,2,3,4,5,6,7,8}
int arr2[10] = {0}
//复制20字节，int 1个数4字节，20字节复制5个int
memmove(arr2, arr1, 20)；

//处理内存重叠
int arr[10] = {1,2,3,4,5,6,7,8}
//arr中的内容变成{1,2,1,2,3,4,5,8}
memmove(arr+2, arr, 20);
//arr中数据为{1,2,1,2,1,2,1,8}
memcpy(arr+2, arr, 20)
```

### memcmp-内存比较

```c
#include<stdlib.h>

// 定义
// num单位字节，比较str1与str2前num个字节
// 相等返回 0
// str1 大，返回大于0的数
// str2 大，返回小于0的数
void *memcmp(const void *str1, const void *str2, size_t num)

//使用
float arr1[] = {1.0, 2.0, 3.0}
float arr2[] = {1.0, 3.0}
// 只比较前4个字节
int ret = memcmp(arr1, arr2, 4);
```

### rand-随机数

- 头文件：#include<stdlib.h>
- 描述：随机产生一个0~RAND_MAX之间的数，RAND_MAX由stdlib中定义；c语言默认产生最大数是32767
- 注意：rand产生的数是伪随机，产生的随机数序列是相同的

``` c
int a = rand();
rand() % 100;//产生0-99之间的数
rand() % 100 + 1; //产生1-100之间的数
```

### srand-随机数种子

- 头文件：#include<stdlib.h>
- 描述：可以更改rand函数产生不同的随机数序列

``` c
srand(1); //设置随机数种子，不同的种子，随机数不同
int a = rand();

#include<time.h>
srand(time(NULL)) //根据时间设置随机种子
```



## 中断与错误信息

### assert-断言中断程序

### strerror-返回错误码

```c
/* 头文件 */
#include <errno.h>
#include <string.h>
/* 定义 */
// strerror是string.h的函数
// 调用库时会出现错误，将错误码转化为错误信息输出
// 错误信息会放到errno变量中，直接打印这个变量即可
// errnum是errno.h的变量，errno是一个全局变量
int *strerror(int errnum)

// 使用
strerror(errno);
printf("%s\n", strerror(0) )
```

### perror-打印错误信息

```c
#include <stdio.h>

// 会自动读取错误码和错误信息
perror("自定义字符")
```

## 六、文件操作

### 操作符

1. r：只读模式，文件必须存在
2. w：写模式，文件不存在创建，从头写入（会覆盖文件）
3. a：追加模式，文件不存在创建，从文章末尾开始
4. r+：读写模式，文件必须存在，从头写入，不是完全覆盖，有几个字符覆盖几个
5. w+：读写模式，文件不存在创建，从头写入，覆盖所有内容
6. a+：读和追加模式，文件不存在创建，在末尾添加
7. b：二进制文件读写，不会对\r\n进行转换，其他会自动进行转换

### fopen-打开文件

```c
// 头文件
#include <stdio.h>
/*
原型：
	FILE *fopen(const char *filename, const char *mode)
参数：
	filename 路径文件名
	mode     打开模式
返回值：
	失败，NULL
	成功，FILE 类型的指针
*/
// 没有路径指与本文件在同一目录
FILE *f = fopen("xxx.txt"， "r"); 
if( f == NULL) printf("打开失败");
```

### fgetc-读取1个字符

```c
// 头文件
#include <stdio.h>
/*
描述：从文件中读取1个字符，读到末尾返回EOF（在stdio.h文件中定义，值为-1）
原型：int fgetc(FILE *stream)
参数：
	stream：fopen返回的文件指针
返回：
	成功，读取的字符
	失败 / 文章末尾，EOF
*/
char c = fgetc(f);
```

### fgets-读取多个字符

``` c
#include<stdio.h>
/*
描述：fgets从文件中读取字符串，并在字符串末尾添加\0,放到string变量中，最多读取n-1个字符
原型：char *fgets(char *string, int n, FILE *stream)
参数：
	string:
	n:
	stream：fopen返回的文件指针
返回值：
	成功，字符串指针
	失败，NULL，需要使用feof或者ferror函数确定错误原因
*/
// 将stream读取的数据放到string中，n表示读取的最大个数
fgets(str, 8, fp);
```

### fputc-写入1个字符

``` c
#include<stdio.h>
/*
描述：每次写入1个字符
原型：int fputc(int c, FILE *stream)
参数：
	c：写入的字符
	stream：fopen返回的文件指针
*/
fputc("b", fp);
```

### fputs-写入多个字符



### feof-判断是否到了结尾

``` c
#include<stdio.h>
/*
原型：int feof(FILE *fp)
返回值：
	非0，文件位置指向文件结束符（EOF)
	0, 未到结尾
*/
while(!feof(fp)){...}
```

### fscanf-按格式读取

### fprintf-按格式输入

``` c
//格式化输出
// format 格式
int fprint(FILE *stream, const char *format[,argument]...)
fprintf(f,"%d %s %f",a,b,c)
//格式化输入
fscanf(f,"%d %s %f", &a, &b, &c)
```

### fread-按块读取

### fwrite-按块写入

### fseek-随机读取

``` c
// 文件随机读写
// 根据文件指针的位置和偏移量定位文件指针
int fseek(FILE *stream, long int offset, int origin)
```

### fflush-刷新缓冲区

### fclose-关闭文件

```c
#include <stdio.h>
/*
原型：
	int fclose(FILE *stream)
参数：
	steam：由fopen返回的文件指针
*/
// 结束后才能清空缓冲区
fclose(f);
f=NULL
```

### 例子

```c
#include <stdio.h>
int main()
{
    int ch;
    //打开文件
    FILE *f = fopen("xxx.txt"， "r"); //定义一个文件指针
    if( f == NULL); //没有路径指与本文件在同一目录
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

### 位置指针

### 标准输入输出

1. 标准输入流(stdin)-键盘
2. 标准输出流(stdout)-屏幕
3. 标准错误流(stderr)-屏幕

```c
#include <stdio.h>
int main()
{
    FILE *f;

    if(f = fopen("xxx.txt"， "r") == NULL)
    {
        fputs("打开失败", stderr); //标准错误输出流
    }      

}
```

## stddef.h

### offsetof-偏移量计算

```c
#include <stddef.h>

//计算c1相对于s的偏移量
offsetof(struct s, c1)
```

## 算法函数

### qsort-快排

```c
/** 
Function Name: qsort() 
Describe: 快速排序
Parameter:
    base    指向要排序的数组的第一个元素的指针。
    nitems  base数组中元素的个数。
    size    base数组中每个元素的大小，以字节为单位,sizeof即可。
    compar  用来比较两个元素的函数。
*/ 
#include <stdlib.h>
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))

/** 
Function Name:  compar()
Describe: 快速排序中自定义的比较函数
Parameter:
    const void *a 快排的标准数,i指针
    const void *b 快排的比较数，j指针
return: 正序a-b, 逆序b-a
**/
int cmp(const void *a, const void *b) 

//使用方法
int a[] = {1,3,5,6,34,0};
qsort(a, 6, sizeof(int), cmp);

int cmp(const void *a, const void *b)
{
    int a1 = *(int *)a; //必须得强制转换为int，void无法进行计算
    int b1 = *(int *)b;

    return a-b;
}
```

### bsearch-二叉树查找

```c
/** 
Function Name: bsearch() 
Describe: 二叉排序查找方法
Parameter:
    key -- 要查找的元素的指针，类型转换为 void*。
    base -- 进行查找的数组的第一个对象的指针，类型转换为 void*。
    nitems -- base 所指向的数组中元素的个数。
    size -- 数组中每个元素的大小，以字节为单位。
    compar -- 用来比较两个元素的函数。
**/
#include <stdlib.h>
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))

//例
int *item;
int key = 32;

/* 使用 bsearch() 在数组中查找值 32 */
item = (int*) bsearch (&key, values, 5, sizeof (int), cmpfunc);
```

## 科学计算-math

### fmin

``` c
/**
Function Name: fmin() 
Describe: 返回2者较小的数
Parameter:
    A -- 元素A
    B -- 元素B
*/
fmin(A,b)  // 返回A，b中小的数,int类型
fminl(A,B) // 返回A，B中，小的数，double类型
fminf(A,B) // 返回A，B中，小的数，float类型
```

### sqrt-开方函数

## 系统函数

### system-DOS清屏

``` c
system("cls"); //清屏命令
```

