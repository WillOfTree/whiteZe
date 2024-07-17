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

## 容器

### 一、vector-动态数组-单端

- vector与数组不同的地方在于，vector是可以动态扩展的数组，vector的迭代器支持随机访问
- 支持随机访问、他的空间是连续的
- vector在尾部添加移动数据非常快
- 多用于访问，多插入删除使用list

#### Ⅰ、构造方法

``` c++
// 必须包含头文件
#include <vector>

/* 创建一个vector容器 */
// 保存的是int类型，名字是v
vector<int> v1;

/* 利用区间 */
vector<int> v2(v1.begin(), v1.end())
    
/* 用n个elem方式构造 */
// 创造10个100元素
vector<int> v3(10, 100)
    
/* 拷贝构造 */
vector<int> v4(v3)
```

#### Ⅱ、vector赋值

重载了=号

``` c++
vector<int> v1;
// 向vector中存储数据
v1.push_back(a);

vector<int> v2;
// vector与vector之间的赋值方式
v2 = v1;
```

使用assign

``` c++
vector<int> v3;
v3.assign(v1.begin(), v1.end());

// 使用10个a赋值
v3.assign(10, 'a');
```

#### Ⅲ、迭代器说明

``` c++
/* 容器起始位置 */
// itBegin：自定义变量名
// v.begin()：vector内置的方法,v是vector的对象
// vector<int>::iterator：vector内置的方法
vector<int> v;
vector<int>::iterator itBegin = v.begin();

/* 结束迭代器 */
// itEnd：自定义变量名
// v.end()：容器最后一个元素的下一个
vector<int>::iterator itEnd = v.end();
```

#### Ⅳ、vector数据存取

普通操作

``` c++
vector<int> v;
/* 返回索引idx所指的对象 */
// 使用[]，和数组使用方法一样
int a = v[1];
// 使用at
int b = v.at(1);

/* 返回容器中的第一个元素 */
v.front()
/* 返回容器中的最后一个元素 */
v.back()
```

利用迭代器循环遍历方法

``` c++
/* for循环 利用迭代器 */ 
for(
 vector<int>::iterator it=v.begin();it!=v.end();it++
){
    //*it是取值
	cout<< *it<<endl;
}

/* while循环利用迭代器 */ 
while(it != itEnd){
	cout<< *it;
	it++;
}

/* 使用算法中的for_each遍历 */
#include <algorithm>
int myPrint(){
    
}
// myprint回调函数
for_each(v.begin(), v.end(), myPrint);
```

#### Ⅴ、存放自定义数据类型

``` c++
#include <vector>

// 自定义一个数据类型，比如类
class Person{
public:
    Person(string name, int age)(
    	this->m_Name = name;
    )
    string m_Name;
}

// 使用vector保存数据
vector<Person> v;
// 创建Person数据
Person p1("aaaa");
// 向vector中添加数据
v.push_back(p1);
// 遍历vector
for (vector<Person>::iterator it=v.begin(); it!=v.end();it++){\
    // 两种访问模式
    cout <<"姓名"<<(*it).m_name;
    cout <<"姓名"<<it->m_Name;
}
```

#### Ⅵ、存放指针

``` c++
#include <vector>

// 自定义一个数据类型，比如类
class Person{
public:
    Person(string name, int age)(
    	this->m_Name = name;
    )
    string m_Name;
}

// 不同点
// 使用vector保存数据
vector<Person*> v;

// 创建Person数据
Person p1("aaaa");

// 不同点
// 向vector中添加数据
v.push_back(&p1);

// 不同点
// 遍历vector
for (vector<Person*>::iterator it=v.begin(); it!=v.end();it++){\
    // 两种访问模式
    cout <<"姓名"<<(*it)->m_Name;
}
```

#### Ⅶ、vector嵌套

``` c++
#include <vector>
// 嵌套定义
vector<vector<int>> v;
// 创建小容器
vector<int>v1;
vector<int>v2;
//将小容器添加到大容器中
v.push_back(v1);
v.push_back(v2);
// 遍历vector
for (vector< vector<int>>::iterator it=v.begin(); it!=v.end();it++){
    // *it：小容器
    for (vector< vector<int>>::iterator vit=(*it).begin(); it!=(*it).end();vit++){
    	cout <<"姓名"<<(*vit)->m_Name;
    }
}
```

#### Ⅷ、容量方法

``` c++
/* 获取容器的容量 */
// 容量会大于元素个数
v.capacity()
    
/* 返回容器中元素的个数 */ 
v.size()
    
/* 判断容器是否为空 */
// 空返回true
v.empty()
    
/* 重新指定容器长度为 */
// 重新指定容器长度为num，
// 若容器变长则以默认值（0）填充
v.resize(int num);
// 使用指定值(n)填充
v.resize(int num, int n)
```

#### Ⅸ、插入和删除

``` c++
/* 尾插 */ 
// 向容器中插入数据10
v.push_back( 10 )

/* 删除最后一个元素 */
v.pop_back()
    
/* 插入元素 */
// 注意：第一个元素是vector的迭代器
// 在v的头部添加数据
v.insert(v.begin(), 10)
// 在头部插入2个1000元素
v.insert(v.begin(), 2, 1000)
    
/* 删除 */
// 注意：第一个元素是vector的迭代器
v.erase(v.begin())
// 从begin删除到end
v.erase(v.begin(), v.end())

/* 删除所有元素 */
v.clear()
```

#### Ⅹ、互换容器

- 利用互换容器可以收缩内存空间

``` c++
/* 基本使用 */
vector<int> v1;
vector<int> v2;
// 存放元素
v1.push_back(1);
v1.push_back(2);
v2.push_back(3);
v2.push_back(4);
// 交换
v1.swap(v2);

/* 收缩容器空间 */
// vector<int>(v1)：匿名对象
vector<int>(v1).swap(v1)
```

#### ⅩⅠ、预留空间

因为vector是动态开辟空间，使用预留空间可以减少vector重新开辟空间的次数

``` c++
vector<int> v;
// 预留空间10000000
v.reserve(10000000)
```

### 二、deque-动态数组-双端

- 支持随机存取
- 在头部和尾部插入删除非常快

#### Ⅰ、构造函数

``` c++
#include<deque>

// 定义方式与vector相同
deque<int> d;
deque<int> v2(v1.begin(), v1.end());
// 创造10个100元素
deque<int> v3(10, 100);
/* 拷贝构造 */
deque<int> v4(v3);
```

#### Ⅱ、赋值操作

与vector容器操作类似

``` c++
// 重载了=号
deque<int> v1;
// 向容器中存储数据
v1.push_back(a);

// deque与deque之间的赋值方式
deque<int> v2;
v2 = v1;

/* 使用assign */
deque<int> v3;
v3.assign(v1.begin(), v1.end());
// 使用10个a赋值
v3.assign(10, 'a');
```

#### Ⅲ、容量方法

``` c++
/* 返回容器中元素的个数 */ 
v.size();
    
/* 判断容器是否为空 */
// 空返回true
v.empty();
    
/* 重新指定容器长度为 */
// 重新指定容器长度为num，
// 若容器变长则以默认值（0）填充
v.resize(int num);
// 使用指定值(n)填充
v.resize(int num, int n);
```

#### Ⅳ、插入删除

#### 两端插入删除

``` c++
#include<deque>
deque<int> v;

/* 插入 */
// 尾插：向容器中插入数据10
v.push_back(10);
// 头插
v.push_front(10);

/* 删除 */
// 尾部删除一个元素
v.pop_back();
// 头删
v.pop_front();
```

#### 插入元素

``` c++
#include<deque>
deque<int> v;

/* 头部插入元素 */
// 注意：第一个元素是deque的迭代器
// 在v的头部添加数据
v.insert(v.begin(), 10);
// 在头部插入2个1000元素
v.insert(v.begin(), 2, 1000);
// 在一个区间插入元素
// 在v容器中开始位置，插入v2的开始元素到v2的end
v.insert(v.begin(), v2.begin(), v2.end());
```

#### 删除元素

``` c++
 #include<deque>
deque<int> v;

/* 删除 */
// 注意：第一个元素是vector的迭代器
v.erase(v.begin())
// 从begin删除到end
v.erase(v.begin(), v.end())

/* 删除所有元素 */
v.clear()
```

#### Ⅴ、迭代器

- 普通迭代器：iterator
- 逆序迭代器：reverse_iterator
- 只读迭代器：const_iterator

``` c++
// deque迭代器
deque<int>::iterator it = d.begin();
// 不可修改的迭代器,常量迭代器
deque<int>::const_iterator it = d.begin();
```

#### Ⅵ、数据存取

``` c++
deque<int> v;
/* 返回索引idx所指的对象 */
// 使用[]，和数组使用方法一样
int a = v[1];
// 使用at
int b = v.at(1);

/* 返回容器中的第一个元素 */
v.front()
/* 返回容器中的最后一个元素 */
v.back()
```

#### Ⅶ、数据排序

利用了排序算法sort

``` c++
#include<deque>
#include<algorithm>
deque<int> d;
// 默认从小到大
// 只要支持随机访问，即可使用sort排序
sort(d.begin(), d.end())
```

### 三、map-散列表

- map不允许右重复的key元素，multimap允许有重复的key值
- map中存储的是pair类型数据
- pair第一个元素为key，第二个元素为value
- 所有元素都会根据键值自动排序
- **根据key快速找到value值**

#### Ⅰ、构造方法

``` c++
#include <map>

// 第一元素key，第二个value
map<int, int> m;
// 拷贝构造
map<int, int> m1(m);

// 插入,一个匿名pair元素
m.insert(pair<int, int>(1, 10))
```

#### Ⅱ、大小交换

``` c++
#include <map>
map<int, int> s1;

// 返回容器中元素的数目
s1.size();
// 判断是否为空
s1.empty();
// 交换容器
s1.swap(s2);
```

#### Ⅲ、插入删除

``` c++
map<int, int> m;

/* 插入元素 */
// 第一种
m.insert(pair<int, int>(1, 1111));
// 第二种插入函数    
m.insert(make_pair(2, 20));
m.insert(map<int, int>::value_type(3,20));
// map重写了[], 如果没有会自动创建，多用于访问
m[4] = 40;
         
// 清空所有元素
m.clear();

// 删除值为key的元素，可传值
m.erase(key); 

// 删除pos迭代器所指的对象
// s1.erase(s.begin())
m.erase(pos);
// 删除区间内的所有元素
m.erase(beg, end);
```

#### Ⅳ、查找和统计

``` c++
map<int, int> m;
map<int, int> m2;
m.insert(pair<int, int>(1, 1111));

// 获取一个元素
int a = m[1];
// 使用find
map<int, int>iterator pos = m.find(1);
if (pos != m.end()) cout << "NO";

// 统计元素个数,对map而言意义不大（结果只能为1或0）
s1.count(30);
```



## 七、set/multiset容器-红黑树

- set不允许有重复数据，multiset允许重复元素
- 会自动排序

### 1、构造赋值

``` c++
#include <set>

// 声明
set<int> s1;
// 拷贝构造
set<int> s2(s1);
```

### 2、大小交换

``` c++
#include <set>
set<int> s1;

// 返回容器中元素的数目
s1.size();
// 判断是否为空
s1.empty();
// 交换容器
s1.swap(s2);
```

### 3、插入删除

``` c++
set<int> s1;

// 插入值,只有1种插入方式
s1.insert(elem); 

// 清空所有元素
s1.clear();

// 删除值为elem的元素，可传值
s1.erase(elem); 

// 删除pos迭代器所指的对象
// s1.erase(s.begin())
s1.erase(pos);
// 删除区间内的所有元素
s1.erase(beg, end);
```

### 4、查找和统计

``` c++
/* 
return：成功返回当前元素迭代器，失败返回end()
判断是否找到：if(pos != s1.end()){}
*/
// 使用迭代器接收位置
set<int>::iterator pos = s1.find(elem);
// 获取元素
*pos;

// 统计元素个数,对set而言意义不大（结果只能为1或0）
s1.count(30);
```

### 5、排序

set存放内置数据类型

``` c++
class MyCompare {
public:
    // 重载了（）运算符
    bool operator() (int v1, int v2) {
        // 由大到小排序
		return v1 > v2;
    }
}

// 指定排序规则，set默认升序排序
set<int, mycompare> s1;
```

修改自定义数据类型

``` c++
class Person {
public:
    // 初始值
    string name;
    int age;
    Person(sting name, int age){
        this->name = name;
        this->age = age;
    }
}

class MyCompare {
public:
    // 重载了（）运算符
    bool operator() (const Person v1, const Person v2) {
        // 按Person元素的age排序
		return v1.age > v2.age;
    }
}
// 指定排序规则，set默认升序排序
set<Person, MyCompare> s1;

// 创建person对象
Person p1("xx", 30);
// 插入容器
s1.insert(p1);
```

#### 迭代器

``` c++
// set<int>::iterator it=s.begin()
set<int>::iterator it;

```



## 六、list-双向循环链表

- 动态分配（**不会造成内存浪费和溢出**）-提供双向迭代器（只支持后移和前进）
- 不支持随机访问
- 可以在任意位置快速插入删除

### 1、构造方法

``` c++
#include <list>

// 构造方法
list<int> m; 
// 赋值m的数据
list<int> m1(m.begin()， m.end());
list<int> m2(m);
// 创建10个1000
list<int> m3(10, 1000);
```

#### assign方法

``` c++
list<int> L;
list<int> L2;

// 将beg，end区间的数据拷贝给L2
L2.assign(L.begin(), L.end())
//将10个aaa拷贝给L2
L2.assign(10, 'aaa')
//重载等号操作
L2 = L;
// 交换L与L2
L2.swap(L);
```

### 2、添加删除数据

``` c++
#include<list>
list<int> m;

/* 添加元素 */
// 尾插
m.push_back(elem);
// 头插
m.push_front(elem); 

/* 删除元素 */
// 删除元素，开头
m.pop_front(elem); 
// 删除元素，尾
m.pop_back(elem);
// 清空数据
m.clear();
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

### 3、list大小操作

``` c++
list<int> L;

// 返回容器中的元素个数
L.size();
// 判断是否为空
L.empty();

/* 重新指定容器长度，容器变短会删除元素 */
// 重新指定容器长度为num
L.resize(num);
// 重新指定容器长度为num，容器变长使用elem填充
L.resize(num, elem)
```

### 4、数据存取

链表不支持随机访问，没有[]访问方式

``` c++
list<int> L;

// 访问链表的第一个元素
L.front();
// 访问链表最后一个元素
L.back()
```

### 5、反转和排序

sort只支持随机访问的容器

``` c++
list<int> L;

/* 反转排序 */
L.reverse();

/* 排序 */
// 默认从小到大，升序
L.sort();
```

自定义类型排序

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

### 迭代器

``` c++
// 普通迭代器
list<int>iterator it;
// 不可修改的迭代器，const list<int> L
list<int>::const_iterator it;

list<int> L;
// 起始迭代器
L.begin();
// 结束迭代器
L.end();

/* 验证迭代器支持随机访问 */
list<int>::iterator it = L.begin();
// 双向访问
it++;
it--;
// 随机访问
it = it + 1;
```

### 5、排序

map存放内置数据类型（使用关系仿函数更简单）

``` c++
class MyCompare {
public:
    // 重载了（）运算符
    bool operator() (int v1, int v2) {
        // 由大到小排序
		return v1 > v2;
    }
}

// 指定排序规则，set默认升序排序
map<int, int, mycompare> m1;
// 使用关系仿函数
map<int, int, less<int>()> m1;
```

修改自定义数据类型

``` c++
class Person {
public:
    // 初始值
    string name;
    int age;
    Person(sting name, int age){
        this->name = name;
        this->age = age;
    }
}

class MyCompare {
public:
    // 重载了（）运算符
    bool operator() (const Person v1, const Person v2) {
        // 按Person元素的age排序
		return v1.age > v2.age;
    }
}
// 指定排序规则，set默认升序排序
map<Person, Person, MyCompare> s1;

// 创建person对象
Person p1("xx", 30);
// 插入容器
s1.insert(pair<int, Person>(1,p1));
```

### 迭代器

``` c++
for(
	map<int, int>::iterator it = m.begin();
    it != m.end();
    it ++
){
   	cout<< "key=" (*it).first;
    cout<< "value=" it->second;
}
```



## string-字符串

C风格字符串太过复杂，不适合大程序开发； string封装了很多实用成员方法，不用考虑内存释放和越界

- char* 是一个指针，
- string是一个类，string内部管理一个char*

注意：没有使用命名空间的时候，可以字节使用std::string定义字符串，vs中而不用引用#include <string>

### 函数传递字符串

``` c++
/* 传&引用，不对数据进行拷贝 */
// 声明
void func(std::string & s);
// 使用&，减少内存拷贝
void func(std::string & s){
    cout << s;
}
// 调用
std::string s_a;
func(s_a);

/* 普通传递，拷贝变量，浪费空间 */
// 声明
void func(std::string s);
// 使用&，减少内存拷贝
void func(std::string s){
    cout << s;
}
// 调用
std::string s_a;
func(s_a);
```

### 1、字符串定义方法

``` c++
// 头文件
#include <string>
//可以使用std::string定义字符串vs中
 
/* 默认构造 */
// str是个字符串变量
string str;

/* 拷贝构造 */ 
// str2的字符串是str中的内容
const char * str = "hello world";
string str2(str)
    
/* 使用相同的字符创建字符串 */
// 使用10个a字符创建字符串
string str4(10, 'a')
```

### 2、赋值方法

string类重写了=号等符号

``` c++
// 方法1
string str1;
str = "aaaaa";
// 同理方法
string str3 = “abcd”;
string str3 = string(“123”)
    
// 方法2，将已付值得str1赋值给str2
string str2 = str1;
// 方法3, 单个字符赋值
string str3 = 'a';
```

string另外提供了assign方法进行赋值

``` c++
// 将字符串赋值给str
string str;
str.assign("hhhhhhh");

// 将字符串前n个字符赋值给字符串
string str;
//将前2个字符赋值给str
str.assign("xxxxxxx", 2);

// 通过其他字符串赋值
string str1;
string str2 = "1aaaa";
str1.assign(str2)
    
// 使用10个w给str赋值
string str;
str.assign(10, 'w');
```

### 3、字符串拼接

重写+=方法

``` c++
// 方法一，追加字符串
string s1 = "xxx"
// 使用+=号
s1 += "cvvv";

// 方法二，追加字符
string s1 = "xxx"
// 使用+=号
s1 += "c";

// 方法二，string类型拼接
string s1 = "xxx";
string s2 = "aaaa";
// 将s2加到s1后面
s1 += s2;
```

使用append函数方法

``` c++
// 尾部追加
string str;
str.append(“xxxx”) 
    
// 将xxxxbbbb前4个字符拼接到str后
string str;
str.append("xxxxbbbb", 4)
    
// 将str2添加到str1后面
string str1;
string str2;
str.append(str2)
    
// 截取字符添加
string str;
// 从0位置开始截取3个字符
str.append("xxxxbbxxx", 0,3)
```

### 4、查找替换

查找方法

``` c++
string str = "abcdefg";
// 查找从0开始，返回最先查找位置的下标，没找到返回-1
str.find("b"); 
// 从指定下标开始查询
str.find("b", 3);
// rfind从右往左查找，find从左往右查找
str.rfind("b");
// 字符串大小
str.size()

str.substr(0, 3)//返回从0开始的3个字符串
const char * p = s.c_str(); //转换为C风格字符串
string s2(p) //转换为string类型的字符串
//隐式类型能从const char * 转换为string.但不能从string转换为const char*
toupper(a) //将字符转换为大写
tolower(a) //转换为小写
注意
string a = “123456”;
a[1] =’a’//这样修其中的字符
a = ‘1234567890’;//这里字符过长，内存重新分配
```

替换方法

``` c++
string str = "xxxz23456";
// 从下标1开始，替换2个字符，
str.replace(1, 2, "11");
// 若参数3的个数>参数2的个数，会把参数3全写进去
// 结果：x111z23456
str.replace(1, 2, "111");
```

### 5、字符串比较

比较字符的ASCII的值，相等返回0；>返回1；<返回-1

``` c++
string str1 = "xxx";
string str2 = "bbb";
// 字符串根据ASCII码对比
str.compare(str2)
```

### 6、字符串存取

``` c++
string str = "helloworld"
// 使用[],修改某个字符
str[1] = 'c'
char c = str[2];

// 使用at
str.at(1) = 'c'
char c = str.at(2);
```

### 7、字符串插入删除

``` c++
string str = "xxxxx";
// 在指定位置插入
str.insert(1, "aaa");

// 插入string类型字符串
string str2 = "bbb";
str.insert(1, str2);

// 在下标10的位置插入个c
str.insert(1, 10, 'c');
// 删除下标1开始的，5个字符
str.erase(1, 5);
```

### 8、字符串截取

``` c++
string str = "aaaaaaa";
// 从下标1开始，截取3个字符
string substr = str.substr(1, 3)
    
// 获取用户名
string str = "tianxia@126.com";
int pos = str.find("@");
string name = str.substr(0, pos)
```

## 四、stack-栈

- 先进后出的容器（**不允许有遍历行为**）-没有迭代器

``` c++
#include<stack>

// 构造方法
stack<T> a; 
// 拷贝构造
stack(a);

// 添加元素
a. push(10);
// 删除元素，弹出一个数据
a. pop();
// 访问栈顶元素-不弹出
a. top(); 

// 读取stack大小， 
// while(s.size() !=0 )
a. size();
// 判断是否为空
a.empty();
```

## 五、queue-队列

- 先进先出（**只能再队尾添加，队头删除**）-没有迭代器

``` c++
#include<queue>
// 构造方法
queue<int> a;

// 队尾添加元素
a.push(10);
// 对头弹出
a.pop();

// 判断是否为空
a.empty();
// 查看队头元素
a.front();
// 查看队尾元素
a.back();
```

## 九、pair对数组

- 返回多个数据

``` c++
// 定义
//pair<type, type>p(value1, value2);
pair<string, int> p("tom", 100);
// 获取第一个元素
p.first;

pair<string, int> p2 = make_pair("tom" , 10);
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

函数对新可以做参数传递

## 概念谓词

- 仿函数返回类型是布尔类型
- operator() 接收一个参数，一元谓词
- operator() 接收二个参数，二元谓词

## 