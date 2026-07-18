## 标准IO

## 文件IO

## Stringsteam



## 文件操作

文件类型分为两种

- 文本文件：文件以ASCII码形式存放在计算机中
- 二进制文件：文件以文本的二进制形式存储在计算机中

文件操作三大类

- ofstream：写操作
- ifstream：读操作
- fstream：读写操作

### 一、文本文件

文件操作方式：

- ios::in：  读文件的方式打开
- ios::out： 写文件的方式打开
- ios::ate： 初始位置：文件尾
- ios::app： 追加方式写
- ios::trunc： 如果文件存在，先删除在创建
- ios::binary： 二进制方式
- 多方式打开：ios:out | ios::trunc 使用2种方式

#### 1、写操作

``` c++
/* 导入头文件 */ 
#include<fstream>

/*  创建流对象 */
ofstream ofs;
/* 打开文件 */ 
ofs.open(“路径”, ios::in);
/* 写数据 */ 
ofs<< “想要向文本输入的” << endl;
/* 关闭 */ 
ofs.close();
    
/* 判断打开时候成功 */
// 成功返回1,失败返回0
ofs.is_open();
```

#### 2、读文件

``` c++
/* 导入头文件 */ 
#include<fstream>

/* 创建流对象 */
ifstream ifs;
/* 打开文件 */ 
ifs.open(“路径”, ios::out);
/* 读数据、方式一 */ 
char buf[1024] = {0};
// 读的数据放到buf中
while(ifs >> buf){
    //读取完成后，输出
	couf<< buf <<endl; 
}
/* 读数据、方式二 */ 
char buf[1024] = {0};
while( ifs.getline(buf, sizof(buf)) ){
	couf<< buf <<endl; //读取完成后，输出
}
/* 读数据、方式三 */ 
string buf;
while( getline(ifs, buf) ){
	couf<< buf <<endl; //读取完成后，输出
}

/* 关闭 */ 
ofs.close();

/* 判断打开时候成功 */
// 成功返回1,失败返回0
ofs.is_open();

/* 获取数据，放到buf中，每次读取sizfo(buf)个大小 */
ifs.getline(buf, sizeof(buf))
/* 每次获取1个字符 */
char c = ifs.get();
/**/
ifs.eof()
```

### 二、进制文件

文件类型特定为：ios::binary

二进制写文件不建议使用string类型，会有不可预料的错误

#### 1、写文件

``` c++
/* 导入头文件 */ 
#include<fstream>

/* 创建流对象 */
ofstream ofs;
/* 打开文件 */ 
ofs.open(“路径”, ios::out | ios::binary);
/* 写数据 */
Person p = {'张三', 18}；
// 将p类型强转换为char指针类型
ofs.write((const char *)&p, sizeof(Person))
/* 关闭 */ 
ofs.close();
```

#### 2、读文件

``` c++
/* 导入头文件 */ 
#include<fstream>

/* 创建流对象 */
ifstream ifs;
/* 打开文件 */ 
ifs.open(“路径”, ios::in| ios::binary);
/* 读数据*/ 
if (!ifs.is_open()){
    cout<< "打开失败"
        return;
}
// 用于存放数据
Person p;
// 读取的数据放到p中，大小是sizeof(Person)
ifs.read( (char *)&p, sizeof(Person))

/* 关闭 */ 
ofs.close();
```

## 

### 三、标准输入输出

#### Ⅰ、键盘输出cout

``` c++
// 跳过回车，空格
// 默认按十进制输出
cout << 0b00001010 << endl; //输出10
cout << 0123 <<endl; //输出83
cout << 0xab << endl; //输出171

// 输出8进制
cout << bitset<8>(0b00001010) << endl; // 输出00001010
cout << oct << 0123<< endl; // 0123
cout << hex << 0xab << endl; //输出ab
//刷新缓冲区linux有用
cout.flush()
//放入缓冲区
cout.put(‘a’).put() 
// 
cout.write()
cout.width(20)
cout.fill(“*”)
//卸载10进制显示
cout.unsetf(ios::dec)
//十进制显示
cout.setf(ios::dec)
```

#### Ⅱ、键盘输入cin

``` c++
// cin 输入设备，默认为键盘
char data;
// cin会根据输入的类型自动判断输入类型
cin >> data; //将输入值放入data变量
// 输入多个变量
cin >> num >> data
//获取一个字符，接收换行\n
char c = cin.get() 
//将字符放到buf变量中，获取1024个字符,读取字符串不会拿走\n需要在读取一次
cin.get(buf, 1024)
//读取换行符，并把换行扔掉
cin.getline(buf, 1024)
//忽略一个字符
cin.ignore()
//忽略了n个字符
cin.ignore(n)
//查看，然后再放入缓存区，用cin.get()可获取
cin.peek()
//将字符串返回缓冲区
char c = cin.get();
cin.putback(c); 
```

## 