# STL标准模板库

- 基本全部使用了模板类或者模板函数
- 容器：各种数据结构，vector、list、map等
    1. 序列容器：强调值得排序，每个元素有固定位置
    2. 关联容器：二叉树结构，元素之间没有严格得物理顺序关系
- 算法：各种常用算法
    1. 质变算法：指运算过程中会改变元素得内容，例：拷贝、删除
    2. 非质变算法：不会改变区间元素内容，例：查找、计数、遍历
- 迭代器：容器与算法之间的胶合剂
    1. 输入迭代器：对数据得只读访问
    2. 输出迭代器：对数据只写访问
    3. 前进迭代器：读写操作
    4. 双向迭代器：读写操作
    5. 随机访问迭代器：读写操作
- 仿函数：行为劣势番薯，可作为算法的某种策略
- 适配器：一种用来修饰容器或者仿函数的策略
- 空间配置器：负责空间的配置和管理

## 概述

1. List：链表

   - `forward_list` ：只支持单向遍历。它适用于需要频繁进行前向遍历和插入、删除操作的场景
   - 频繁增删的情况下效率高
   - 元素占用的空间是在堆上分配的，
   - 空间是按需分配的，**不能随机存取**，可双向存取。
   - 如果你的元素个数不确定，并且元素的个数变化的频率比较高，这时候选择使用`std::list`。
1. vector：动态数组

   - 元素占用的空间是在堆上分配的，
   - 大小是可以改变的，每当容器需要扩大时，都会按照相同的系数进行扩大，
   - 内存连续，**可随机存取。**
   - 如果你的元素个数不确定，但是元素个数的变化频率比较低，这时候应选择使用`std::vector`。存取速度上相对与动态数组是没有消耗的。
1. Array：静态数组

   - 元素占用的空间是在栈上分配的
   - **大小固定不变**，内存连续，**可随机存取**。
   - 如果你的元素个数确定且数量不是很大，应使用`std::array`，在存取速度和内存占用上，相对静态数组是没有消耗的，且类型安全。
1. 各个容器优势
   - vector：随机访问，末端插入删除快
   - list：任意位置插入删除
   - deque：支持随机访问，2端插入删除效率高

## string-字符串

1. C风格字符串太过复杂，不适合大程序开发；
2.  string封装了很多实用成员方法，不用考虑内存释放和越界
3. 注意：
   - 没有使用命名空间的时候，可以字节使用std::string定义字符串，vs中而不用引用#include <string>
   - `char* `是一个指针，
   - string是一个类，string内部管理一个`char*`

### 一、函数传递字符串

#### Ⅰ、使用&引用传递

- 传&引用，不对数据进行拷贝
- 本质相当于使用指针

``` c++
void func(std::string & s);// 声明
// 定义，使用&，减少内存拷贝
void func(std::string & s)
{
    cout << s;
}
/* 使用方法 */ 
std::string s_a; //字符串变量声明
func(s_a);
```

#### Ⅱ、普通传递

- 普通传递，拷贝变量，浪费空间

``` c++
void func(std::string s);// 声明
// 定义，使用&，减少内存拷贝
void func(std::string s){ 
    cout << s;
}
/* 使用方法 */
std::string s_a; // 声名
func(s_a);
```

### 二、声明定义

- 头文件：`#include <string>`

``` c++
/* 声明的2种形式 */
string str; //这种一般需要在std命名空间下
std::string str;// 指定std命名空间
/* 定义 */
string str("123"); // 123
string str(3, "1"); // 111
string str = "1234"; // 1234

/* 拷贝构造 */ 
// str2的字符串是str中的内容
const char * str = "hello world";
string str2(str)
```

### 三、常用赋值方法

- string类重写了`=`等符号，使得string变量可以像其他语言一样赋值

  ``` c++
  // 简单例子
  string str;
  str = "aaaaa";
  string str2 = str;
  ```

- string另外提供了assign方法进行赋值，使用效果与上一届相同

  ```  c++
  str.assign("hhh"); //等价于 str = "hhh";
  str.assign(str1); // 等价 str = str1;
  str.assign(10, 'w'); // 等价 str = string(10, "w");
  ```

#### Ⅰ、字符串拼接

- C++重写`+=、=`方法

``` c++
string s1 = "xxx";
string s2 = "aaa";

s1 += "cvvv"; // s1=xxxcvvv;
s1 += s2; // s1=xxxaaa
s1 = s1 + s2; // s1=xxxaaa
s1 = s1 + "123"; //s1=xxx123
```

#### Ⅱ、使用append函数方法

``` c++
string str_2 = "abc";
string str = "123";

str.append("x"); //str = 123x 
str.append("abcdefgh", 3); //str=123abc    
str.append(str2); //str=123abc
// 从0位置开始截取3个字符
str.append("xxxbbxxx", 0,3);//str=123xxx  
```

### 四、查找方法

``` c++
string str = "abcdefg";
/* 查找顺序 */
// 从下标0开始，返回最先查找位置的下标，没找到返回-1
str.find("b"); 
// rfind从后向前查找
str.rfind("b");

/* 其他查找 */
str.find("b", 3);// 从指定下标开始查询
```

### 五、替换方法

- `str.replace(替换开始位置，替换字符个数，替换的对象)`
- 若替换的对象>替换字符个数，则会把替换对象全写入，并扩大str大小

``` c++
string str = "xxxz23456";
str.replace(1, 2, "00"); //str=x00z23456
str.replace(1, 2, "@@@");//str=x@@@z23456
```

### 六、插入与删除

- `str.insert(插入位置，插入字符串)` 

  插入位置1，从字符串下标0开始，数到1，1位置上的字符往后退，

- `str.erase(删除索引，删除字符个数)`

``` c++
string str = "abcdef";
string str_1 = "1234";

str.insert(1, "123"); //str=a123bcdef
str.insert(2, str2); //str=ab1234cdef
str.insert(1, 10, 'c');//
str.insert(3, str2);//str=abc1234def

str.push_back("123"); //str=abcdef123

str.erase(1, 2);//str=adef;
str.pop_back(); //删除最后一个字符
```

### 七、字符串截取

- `str.substr(截取位置，截取字符)`

``` c++
string str = "12345678";
// 从下标1开始，截取3个字符（注意substr中截取位置）
string substr = str.substr(1, 3); //substr=234
    
/* 获取用户名 */ 
string str = "tianxia@126.com";
int pos = str.find("@"); // 查找@位置
string name = str.substr(0, pos)
```

### 八、迭代器

- `str.begin()` str第一个元素位置迭代器
- `str.end()` str最后一个元素位置迭代器

``` c++
/* 索引遍历 */
for(int i=0; i<str.size(); i++);
/* 迭代器遍历 */
for(string::iterator iter=str.begin();iter != str.end(); iter++);
/* auto遍历 */
for(auto &a: str);
```

### 其他常用方法

``` c++
str.size();// 字符串大小
str.empty(); //判断是否为空
str.clear(); //清空字符串
str.length(); //字符串长度
str.count('a');//计算str中a的个数
toupper(str); //将字符转换为大写
tolower(str); //转换为小写
str.at(1); //相当于str[1]
str.compare(str2);//比较字符的ASCII的值，相等返回0
```

## Array-数组

- **固定大小数组**，与 C 语言中的数组相比，具有更好的类型安全和内存管理特性。

- 头文件：`#include <array>` 

- `std::array<T, N> array_name;`

  T：存放的类型，N：存放的个数

``` c++
std::array<int, 5> myArray; //声明
// 定义
std::array<int, 5> myArray = {1, 2, 3, 4, 5};
```

常用方法

``` c++
myArray.empty(); //检查是否为空
myArray.size(); //返回大小
myArray.max_size(); //返回最大容量
myArray.front(); //返回第一个元素
myArray.back(); //返回最后一个元素
```

## list-双向循环链表

- **动态大小**：与Array不同，`<list>` 的大小可以动态变化，不需要预先分配固定大小的内存。
- **快速插入和删除**：可以在列表的任何位置快速插入或删除元素
- **双向迭代**：`<list>` 提供了双向迭代器，可以向前和向后遍历元素。
- **不支持随机访问**：不能使用下标访问

### 一、声明定义

- 头文件：`#include <list>`

``` c++
// 声明
list<int> m; 

// 定义
list<int> m1(m.begin()， m.end());
list<int> m2(m);
// 创建10个1000
list<int> m3(10, 1000);
```

### 二、赋值操作

- 重写了`=`操作符

``` c++
list<int> L;
list<int> L2;

// 将beg，end区间的数据拷贝给L2
L2.assign(L.begin(), L.end())
//将10个aaa拷贝给L2
L2.assign(10, 'aaa')
//重载等号操作
L2 = L;
```

### 三、添加删除

``` c++
/* 插入元素 */
L.push_back(elem);// 尾插
L.push_front(elem); // 头插

/* 删除元素 */
L.pop_front(); // 删除元素，开头
m.pop_back();// 删除元素，尾

// 删除list区间元素
m.arase(m.begin(), m.end());
// 删除pos位置元素,返回下一个元素
m.arase(pos);
// 删除与elem匹配的元素
m.remove(elem);

/* 插入元素 */ 
// 在pos位置添加元素，返回元素位置
m.insert(pos, elem);
// 在pos位置添加n个elem元素，无返回
m.insert(pos, n, elem);
// 在pos位置添加list迭代器元素
m.insert(pos, L.begin(), L.end());
```

### 四、自定义类型排序

``` c++
list<int> L;

// 自定义排序规则
L.sort(my_compare);
// int是可修改的
bool my_compare(int v1, int v2){
    // 降序：v1>v2，升序：v2>v1;
    return v1 > v2;
}
```

### 五、迭代器

- 普通迭代器：`list<int>iterator it;` 
- 不可修改的迭代器：`list<int>::const_iterator it;`
- 迭代器支持双向访问：`it++`和`it--`
- 迭代器支持随机访问：`it = it + 1`

``` c++
for (list<int>::iterator it = L.begin(); it != L.end(); ++it) 
{
    // 双向访问
    it++;
    it--;
    // 随机访问
    it = it + 1;
}
```

### 其他常用方法

``` c++
L.sort();// 默认从小到大，升序,只支持随机访问的容器
L.reverse();//反转排序
L.front();// 访问链表的第一个元素
L.back();// 访问链表最后一个元素
L.size();// 返回容器中的元素个数
L.empty();// 判断是否为空
L.clear();// 清空数据
L.swap(L2);// 交换L2与L

/* 重新指定容器长度，容器变短会删除元素 */
// 重新指定容器长度为num
L.resize(num);
// 重新指定容器长度为num，容器变长使用elem填充
L.resize(num, elem)
```

## vector-动态数组-容器

- **vector变长数组（节省空间）、支持随机访问**
- vector在尾部添加移动数据非常快
- 多用于访问，多插入删除使用list

### 一、声名定义

- 头文件：`#include <vector>`

``` c++
/* 声名 */
vector<int> v1;//保存的是int类型，名字是v
vector<string> v2;//保存string类型

/* 定义 */
vector<int> v(3); // 000
vector<int> v(3, 5); // 555
vector<int> v{1,2,3}; // 123
vector<int> v3(2, 100); // {100,100}
```

### 二、迭代器

``` c++
/* 索引遍历 */
for(int i=0; i<v.size(); i++)
{
    cout << v[i]
}
/* 迭代器遍历 */
for(vector<int>::iterator iter=v.begin();iter != v.end(); iter++);
/* auto遍历 */
for(auto &a: v)
{
    cout << a;
};
```

### 三、赋值方法

- C++重写了`=`方法，使得vector赋值与普通变量赋值一样
- 使用`assign`方法进行赋值

``` c++
vector<int> v;
v.assign(3, 'a');// v=aaa; 使用3个a赋值
v.assign(123); //v=123;
```

### 四、插入和删除

``` c++
v.insert(2, 3, 1000);// 在下标2的位置插入3个数，每个数都是1000
v.insert(1, 10); // 在下标1的位置插入元素10
v.push_back(10);// 向容器中插入数据10

/* 删除 */
v.pop_back(); //删除最后一个元素
v.erase(v.begin());// 注意：第一个元素是vector的迭代器
v.erase(v.begin(), v.end());// 从begin删除到end
v.erase(2, 4); //删除下标2到下标4的元素
```

### 其他常用方法

``` c++
vector<int> v;
v.swap(v2);// 交换,利用互换容器可以收缩内存空间
v.clear(); // 删除所有元素
v.capacity();//v可容纳元素的个数
v.size();//返回容器中元素的个数
v.empty();//判断容器是否为空
v.resize(int num);//重新指定容器长度为num，默认值（0）填充
v.resize(int num, int n);// 使用指定值(n)填充
v.back();//最后一个元素
v.front();//第一个元素
v.at(1);// 等价于v[1]

// 排序
sort(v.begin(), v.end());
// 预留空间10000000，因为vector是动态开辟空间，使用预留空间可以减少vector重新开辟空间的次数
v.reserve(10000000);
```

## deque-双端队列

- 支持随机存取
- 在头部和尾部插入删除非常快

### 一、声明定义

- 头文件：`#include<deque>` 
- 定义方式与vector相同

``` c++
deque<int> d;
deque<int> v3(3, 100);// {100,100,100}
deque<int> v4(v3); //拷贝构造
```

### 二、赋值操作

- 与vector容器操作类似

``` c++
deque<int> v1;
deque<int> v2;

v2 = v1; // 从写了=
v2.assign(v1.begin(), v1.end()); //相当于v2=v1
v2.assign(10, 'a');// 使用10个a赋值
```

### 三、插入删除

- insert参数只能是迭代器
- erase参数只能是迭代器

``` c++
deque<int> v;

v.push_back(10);// 尾插：向容器中插入数据10
v.push_front(10);// 头插
// 只删除元素，并不返回元素
v.pop_back();// 尾部删除一个元素
v.pop_front();// 头删

/* 不常用方法 */
v.insert(v.begin(), 10); // 在v.begin()位置插入 10
v.erase(v.begin());
v.erase(v.begin(), v.end());// 从begin删除到end
```

### 四、迭代器

- 普通迭代器：iterator
- 逆序迭代器：reverse_iterator
- 只读迭代器：const_iterator

``` c++
// deque迭代器
deque<int>::iterator it = d.begin();
// 不可修改的迭代器,常量迭代器
deque<int>::const_iterator it = d.begin();
```

### 其他常用方法

``` c++
d.front(); //返回容器中的第一个元素
d.back(); // 返回容器中的最后一个元素
//d.at(1); // 相当于 d[1]
d.clear();//删除所有元素
d.empty();//判断是否为空
d.size();//容器中的元素个数
d.max_size(); //可容纳的最大元素个数
v.resize(int num); // 重新指定容器长度为num，
v.resize(int num, int n);// 重新设置容器长度，使用指定值(n)填充

// 排序 #include<algorithm>
sort(d.begin(), d.end());
```

## map/multimap-散列表

- map不允许右重复的key元素，multimap允许有重复的key值
- map中存储的是pair类型数据
- pair第一个元素为key，第二个元素为value
- 所有元素都会根据键值自动排序
- **根据key快速找到value值**

### 一、声明定义

- 头文件：`#include <map>` 
- `std::map<key_type, value_type> AA;` 

``` c++
map<int, int> m;// 第一元素key，第二个value
map<int, int> m1(m);// 拷贝构造
```

### 二、赋值方法

``` c++
map<String, int> mp;

mp["info"] = 100;
```

### 三、插入删除

- insert的元素类型必须是pair类型

``` c++
m.insert(pair<int, int>(1, 1111)); // 插入(1, 1111)
m.insert(make_pair(2, 20));// 第二种插入函数
m.insert(map<int, int>::value_type(3,20));

m.erase(key); // 删除值为key的元素
m.erase(iter); // 在循环中删除iter迭代器指定的元素
m.erase(m.begin(), m.end);// 删除区间内的所有元素
```

### 四、查找

- find返回迭代器，没有找到返回mp.end()迭代器

``` c++
int a = m[1];// 获取key为1的值
map<int, int>iterator pos = m.find(1); // 使用find
```

### 五、迭代器

``` c++
/* 迭代器遍历 */
for(map<String, int>::iterator iter=mp.begin();iter != mp.end(); iter++)
{
    iter.first; //获取Key
    iter.secend; //获取value
}
/* auto遍历 */
for(auto &a: mp)
{
    a.first; //获取Key
    a.secend; //获取value
}
```

### 六、函数传递字典

- 注意：return不能返回函数内创建的对象

``` c++
#include <map>
std::map<std::string, int> a;
// 方法一
void test(std::map<std::string, int> *a)
{
    (*a)["TEST"] = 100;
}

// 方法二,引用传递
void test(std::map<std::string, int> &a)
{
    a = 100;
}
```

### 其他常用方法

```c++
mp.size();// 返回容器中元素的数目
//mp.empty();// 判断是否为空
mp.swap(s2);// 交换容器
mp.clear();// 清空所有元素
mp.count("k");// 统计key为k的个数
```

##  set/multiset容器-红黑树

- set不允许有重复数据，multiset允许重复元素
- 会自动排序

### 一、声明定义

- 头文件：`#include <set>`

``` c++
set<int> st;
set<int> s2(s1);// 拷贝构造
```

### 二、插入删除

``` c++
st.insert(1); // 插入值1,只有1种插入方式

st.erase(1); // 删除值为1的元素
st.erase(iter);// 删除迭代器所指对象
```

### 三、查找

- 查找返回的是迭代器，找不到返回`st.end()`迭代器

``` c++
set<int>::iterator pos = st.find(1);
set<int>::iterator pos = st.lower_bound(x); //二分法查找大于等于x元素中最小的一个
set<int>::iterator pos = st.upper_bound(x); //二分法查找大于x元素中最小的一个元素
```

### 其他常用方法

``` c++

st.size();// 返回容器中元素的数目
st.empty();// 判断是否为空
st.swap(st2);// 交换容器
st.clear();// 清空所有元素
```

## stack-栈

- 先进后出的容器（**不允许有遍历行为**）-没有迭代器
- 所有操作都在栈顶进行
- 头文件：`#include <stack>`

``` c++
/* 声明 */ 
stack<int> sk; 

sk.push(10);// 添加元素
sk.pop();// 删除元素，弹出一个数据
sk.top(); // 访问栈顶元素-不弹出

sk.size();// 读取stack大小， 
sk.empty();// 判断是否为空
```

## queue-循环队列

- 先进先出（**只能再队尾添加，队头删除**）-没有迭代器
- 头文件：`#include <queue>`

``` c++
/* 声明 */ 
queue<int> q;

q.push(10);// 队尾添加元素
q.pop();// 队头弹出

q.size(); //队列大小
q.empty();// 判断是否为空
q.front();// 查看队头元素
q.back();// 查看队尾元素
```

## priority_queue-优先队列-堆

- 相当于大根堆或小根堆
- 头文件：`#include <queue>`

``` c++
/* 声明 */ 
priority_queue<int> q;//大根堆
priority_queue<int, vector<int>, greater<int>> q;//小根堆

q.push(10);// 堆中添加元素
q.pop();// 删除堆顶元素
q.top();//返回堆顶元素

q.size(); //堆大小
q.empty();// 判断是否为空
```

## pair-容器

- 头文件：`#include <utility>` 
- `pair<type, type>p(value1, value2)`

``` c++
// 声名
pair<string, int> p;

// 定义
pair<int, int> p(1, 100);
pair<string, int> p("tom", 100);
pair<string, int> p = make_pair("tom" , 10); //与上一个等价

// 获取元素
p.first;
p.second;
```

## 函数对象

- 重载函数调用操作符的类，其对象为函数对象
- 函数对象使用重载 （）时，行为类似函数调用，也叫仿函数

函数对象在使用时，可以像普通函数那样调用，也可有参数，可以有返回值

``` c++
class MyAdd{
public:
    // 重载()
    int operator() (int v1, int v2) {
        return v1 + v2;
    }
}

MyAdd m;
// 调用，普通函数调用
m(10, 10);
```

函数对象超出普通函数对象，函数对新有自己的状态

``` c++
class M_print{
public:
    // 重载()
    int operator() (string t) {
        cout << test;
        this->count++;
    }
    // 自定义状态
    int count;
    M_print(){
        // 初始化
        this->count = 0;
    }
}

M_print m;
// 调用，
m("xxxxxxx");
// 内部状态
m->count;
```
