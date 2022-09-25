> **c语言常用函数整理**
>
> stdlib\stdio\string\ctype
>
> <p align="right">2020/05/30</p>

# #include <stdlib.h>

## void *malloc(size_t size)

分配一块足以存放大小为size的存储，返回该存储块的地址，不能满足时返回NULL

**返回值**

*success* ：

*FALIE* ：

``` c
char *p = (char *)malloc(sizeof(int) *  10)
```

## void *realloc(void *p, size_t size)

将p所指存储块调整为大小size，重新分配malloc或calloc内存空间，并不会清空内存空间，如果没有足够的内存空间，将重新申请空间（与malloc一样）

**返回值**

*success* ：新块的地址。如能满足要求，新块的内容与原块一致；

*FALIE* ：NULL，此时原块不变。

```c

```

## void free(void *ptr)

释放已分配的内存( malloc、realloc)，ptr是一个指针

**返回值**

*success*：

*FALE*：

``` c
free(p);
```

## int rand(void)

生成一个0到RAND_MAX的随机整数

**返回值**

*success* ：

*FALE* ：

```c

```

## void srand(unsigned seed)

用seed为随后的随机数生成设置种子值

**返回值**

*success* ：

*FALE* ：

```c

```

## 转换数据

---

### double atof(const char *str)

参数 **str** 所指向的字符串转换为一个浮点数（类型为 double 型）
**返回值**
*success* ：转换后的双精度浮点数
*FALIE* ： 0.0

```  c
char str[] = "12344.2222";
float val;
val = atof(str);
```

### int atoi(const char *s)

由串s构造一个整数值

### long atol(const char *s)

由串s构造一个长整数值

# #include<stdio.h>

fgetc(fp) != EOF //读取文件到结尾

fclose(FILE * stream) //关闭

r读取，w创建新文件，a追加，创建新文件 ，+ 可读可写，b二进制读写（windows有效）

```c
FILE  fopen(const char  filename, const char mode);
int fclose(FILE stream);

int fgetc(FILE fp);
int fputc(int c, FILE fp);

char fgets(char buffer, int n, FILE stream);
int fputs(const char \*buffer, FILE \*stream);

char gets(char s);
int puts(const char s);

size_t fread(void pointer, size_t size, size_t num, FILE stream);
size_t fwrite(const void pointer, size_t size,size_t num, FILE stream);

int scanf(const char format, ...);
int printf(const char format, ...);

int fscanf(FILE stream, const char format, ...);
int fprintf(FILE stream, const char format, ...);

int sscanf(char s, const char format, ...);
int sprintf(char s, const char format, ...);
```

## scanf/print格式化

```c
scanf(“%[^\n]”, arr)
scanf(“%d  %d”, &a, &b)
scanf(“%1d”, &a)                     //接收1位数据
scanf(“%1s%2s”, arr, arr2)        //接收指定字符
scanf(“%*s%d”, &a)                  //*忽略字符
scanf(“%*[123456]%c”, &a)     // 忽略123456任意字符
scanf(“%*[a-z]%c”, &a)
```

---

```c
printf(""%.2f", 3.145);       //保留2位小数
printf("%5d", 12);             //一共显示5位数
printf(""%4s", “ab”);     //显示4位数字
printf(""%.4s", “ab”);    //截取
```

# #include <string.h>

## 字符串操作

---

### size_t strlen(cs)

统计字符串长度，到\0结束，不统计\0

**返回值**

*success* ：字符长度

*FALE* ：

```c
char arr[] = "hello";    //5
int len = strlen(arr);    //字符串有效长度，忽略\0
```

### char * strcpy(char *dest, const char *src)

把ct复制到s。要求s指定足够大的字符数组，不会复制\0

### char *strncpy(s,ct,n)

把ct里的至多n个字符复制到s。要求s指定一个足够大的字符数组。如果ct里的字符不够n个，就在s里填充空字符。

### char *strcat(char * dest, const char *src)

把ct里的字符复制到s里已有的字符串之后。s应指定一个保存着字符串，而且足够大的字符数组。

char arr1[] = “hello”;

char arr2[] = “word”;

strcat(arr1, arr2) //这里数组下标越界，需要修改arr1的数组大小

strncat()有限追加

strncat(arr1, arr2, 3)

有限追加会将\0加入

 ### char *strncat(s,ct,n)

把ct里的至多n个字符复制到s里已有的字符串之后。s应指定一个保存着字符串，而且足够大的字符数组。

### int strcmp(const char *s1, const char *s2)

比较字符串cs和ct的大小，在cs大于、等于、小于ct时分别返回正值、0、负值。

比较字符串，比较的是ASCII吗，相等会返回0，不同的操作系统，返回值不同，比较\0之前的所有有效字符

### int strncmp(cs,ct,n)

比较字符串cs和ct的大小，至多比较n个字符。在cs大于、等于、小于ct时分别返回正值、0、负值。

### char *strchr(const char *ch, int c)

在cs中查寻c并返回c第一个出现的位置，用指向这个位置的指针表示。当cs里没有c时返回值NULL

查找字符第一次出现的位置

char *p = trrchr(arr, “l”); //p的结果为从l到\0的字符

失败返回NULL

### char *strrchr(cs,c)

在cs中查寻c并返回c最后一个出现的位置，没有时返回NULL

### size_t strspn(cs,ct)

由cs起确定一段全由ct里的字符组成的序列，返回其长度

### size_t strcspn(cs,ct)

由cs起确定一段全由非ct里的字符组成的序列，返回其长度

### char *strpbrk(cs,ct)

在cs里查寻ct里的字符，返回第一个满足条件的字符出现的位置，没有时返回NULL

### char *strstr(cs,ct)

在cs中查寻串ct（查询子串），返回ct作为cs的子串的第一个出现的位置，ct未出现在cs里时返回NULL

### char *strerror(n)

返回与错误编号n相关的错误信息串（指向该错误信息串的指针）

### char *strtok(s,ct)

在s中查寻由ct中的字符作为分隔符而形成的单词，会修改原始字符串

char a[] = “www.baidu.com”;

char *p = strtok(a, “*”)

p // www

while(p!=Null)

{

p = strtok(NULL, “.”); //

}

## 内存操作

----

### void *memcpy(s,ct,n)

从ct处复制n个字符到s处，返回s

**返回值**

```c

```

### void *memmove(s,ct,n)

从ct处复制n个字符到s处，返回s，这里的两个段允许重叠

**返回值**

```c

```

### int memcmp(cs,ct,n)

比较由cs和ct开始的n个字符，返回值定义同strcmp

**返回值**

```c

```

### void *memchr(cs,c,n)

在n个字符的范围内查寻c在cs中的第一次出现，如果找到，返回该位置的指针值，否则返回NULL

**返回值**

```c

```

### void *memset(s,c,n)

将s的前n个字符设置为c，返回s

**返回值**

```c

```



# #include <ctype.h>

*主要是一些类型转换检测的方法*

---

## int isalnum(c)

c是字母或数字字符

## int isspace(c)

c是空格、制表符、换行符

## int isalpha(int)

c是字母字符

## int isdigit(c)

c是数字字符