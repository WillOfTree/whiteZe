# 字符串函数

```c
// 头文件
#include <string.h>
```

**获取字符串长度-strlen**

不包含\0

```c
size_t strlen(); 

char a[] = "Love";
printf("%u", strlen(a));
```

**拷贝字符串-strcpy / strncpy**

不要妄想使用 “=” 进行字符串赋值

strcpy:

```c
char a[] = "abcd";
char b[] = "";
strcpy(a, b);  //将b赋值到a，会拷贝\0
strcpy(a, "xxxxxx");
```

strncpy:

```c
strcpy(a, b, 5);  //将b赋值到a，且只拷贝5个字符
```

**连接字符串-strcat / strncat**

```c

```

比较字符串-strcmp / strncmp

