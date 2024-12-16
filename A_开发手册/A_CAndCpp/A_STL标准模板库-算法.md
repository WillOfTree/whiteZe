# 算法

## 一、functional内建函数对象（谓词）

STL内建了很多函数对象，必须使用functional头文件

### 1、算数仿函数

- 加法：plus
- 减法：minus
- 乘法：multiplies
- 除法：divides
- 取模：modulus
- 取反：negate

``` c++
#include <functional>

/* 取反 */
// 创建取反对象
negate<int> n;
// 使用,输出-50
n(50); 

/* 加法 */
// 只允许同类型相加，所以只要1个int即可
plus<int> n;
// 使用 
n(10, 50);
```

### 2、关系仿函数

- 等于：equal_to
- 不等于：not_equal_to
- 大于：greater
- 大于等于：greater_equal
- 小于：less
- 小于等于：less_equal

``` c++
#include <functional>

/* 大于 */
greater<int>()
```

### 3、逻辑仿函数

- 逻辑与：logical_and
- 逻辑或：logical_or
- 逻辑非：logical_not

``` c++
#include <functional>


```

## 二、遍历算法

- algorithm：头文件中最大的一个，比较交换查找遍历复制等等
- numeric：简单数学运算模板
- function：函数对象

### 1、for_each-遍历

遍历容器的算法

``` c++
#include <algorithm>

// 准备一些数据
vector<int> v;
v.push_back(1);
v.push_back(2);
// ----------

/* 利用普通函数遍历 */ 
// foreach(起始迭代器，结束迭代器，函数名)
for_each(v.begin(), v.end(), oridin);
// 自定义普通输出函数
void ordin(int v){
    cout << v;
}

/* 利用仿函数 */
// foreach(起始迭代器，终止迭代器， 仿函数对象)
// 必须放函数对象-带（）
for_each(v.begin(), v.end(), ordin())
// 自定义仿函数
class ordin{
public:
    void operator() (int val) {
        cout << val;
    }
}

```

### 2、transform-搬运

将一个容器搬运到另一个容器中，搬运过程中可通过仿函数修改数据

``` c++
#include <algorithm>

// 准备一些数据
vector<int> v;
v.push_back(1);
v.push_back(2);
vector<int> target;
// 目标容器必须提前开启空间
target.resize(v.size())
// ----------

/* 利用普通函数遍历 */ 
// transform(容器开始位置, 容器结束位置, 目标容器开始位置, 仿函数）;
transform(v.begin(), v.end(), target.begin(), ordin());
// 仿函数
class ordin{
public:
    // 只有重写()，必须有返回值，因为要把数据放到target容器中
    int operator() (int val) {
        return val;
    }
}
```

## 三、查找算法

### 1、find-查找元素

- 成功返回：指定元素迭代器
- 失败返回：end()迭代器

``` c++
#include <algorithm>
//准备数据
vector<int> v;
//----

/* 内置数据类型 */
// find(开始迭代器，结束迭代器，查找元素)
// 因为返回的是迭代器，使用迭代器定义it
vector<int>::iterator it = find(v.begin(), v.end(), 10);
if(it == v.end()) cout<< 没有找到; 

/* 自定义数据类型 */
// 自定义数据
class Per {
public:
    PP(string name, int age){
        this->name = name;
        this->age = age;
    }
    string name;
    int age;
}
// 存放自定义数据
vector<int> v;
Per p1("nnn", 10);
per P2("ccc", 20);
v.push_back(p1);
v.push_back(p2);

// find(开始迭代器，结束迭代器，查找元素)
// 因为返回的是迭代器，使用迭代器定义it
// 查找自定义数据p2
vector<int>::iterator it = find(v.begin(), v.end(), P2);
if(it == v.end()) cout<< 没有找到; 
```

### 2、find_if-按条件查找

`find_if(起始迭代器，结束迭代器， 函数或谓词)`

``` c++
#include <algorithm>
//准备数据
vector<int> v;
//----

/* 内置查找迭代器 */
class greaterFice {
public:
    // 条件是val>5
    bool operator() (int val) {
        return val > 5;
    }
}

vector<int>::iterator it = find_if(v.begin(), v.end(), greaterFice());
if(it == v.end()) cout<< 没有找到; 

/* 自定义迭代器 */
class greaterFice {
public:
    string name;
    int age;
    greaterFice(string name, int age){
        this->name = name;
        this->age = age;
    }
    // 条件是val>5
    bool operator() (greaterFice &val) {
        return val.age > 5;
    }
}
// 创建数据
greaterFice g1("11", 10);
greaterFice g2("22", 20);
// 添加元素进容器
v.push_back(g1);
v.push_back(g2);
// 查找
vector<int>::iterator it = find_if(v.begin(), v.end(), greaterFice());
```

### 3、adjacent_find-查找相邻重复元素

`adjacent_find(开始迭代器，结束迭代器)` 

``` c++
// 查找相邻的重复元素，返回相邻元素的第一个位置的迭代器
// 例如：1991234，中99是相邻重复元素
vector<int>::iterator pos = adjacent_find(v.begin(), v.end());
```

### 4、binary_search-二分查找

``` c++
/* 
bool binary_search(开始迭代器，结束迭代器，查找的元素)
无序序列不能使用
成功返回true，失败返回false
*/
#include <algorithm>
vector<int> v;

binary_search(v.begin(), v.end(), 3);
```

### 5、count-统计元素

``` c++
/* 
count(迭代器开始，结束迭代器， 统计的元素)
*/
#include <algorithm>
vector<int> v;

/* 统计内置数据类型 */
// 统计元素40的个数
int num = count(v.begin(), v.end(), 40);

/* 统计自定义数据类型 */
class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }
    string name;
    int age;
    // 注意这里是重载了==号
    bool operatror == (const Person &p){
        if(this->age == p.age){
            return true;
        }else{
            return false;
        }
    }
}
// 准备数据
vector<Person> v;
Person p1("11", 20);
Person p2("22", 30);
v.push_back(p1);
v.push_back(p2);
// 这个是与vector中元素进行对比的元素
Person P("应该对比的元素", 30);
// 统计
int num = count(v.begin(), v.end(), P)
```

### 6、count_if-按条件统计

``` c++
/* 
count_if(开始迭代器，结束迭代器，谓词)
*/
// 统计内置数据类型
class greaterFice {
public:
    // 统计值val>5的元素个数
    bool operator() (int val) {
        return val > 5;
    }
}
// 准备数据
vector<int> v;
v.push_back(10);
v.push_back(20);
// 查找
int num = count_if(v.begin(), v.end(), greaterFice());

/* 统计自定义数据类型 */
// 自定义数据类型
class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }
    string name;
    int age;
}
// 谓词
class AgeGreater {
public:
    // 统计元素age属性>20的
    bool operatror () (const Person &p){
        return P.age > 20;
    }
}

// 准备数据
vector<Person> v;
Person p1("11", 20);
Person p2("22", 30);
v.push_back(p1);
v.push_back(p2);
// 统计条件
count_if(v.begin(), v.end(), AgeGreater())
```

## 四、排序算法

### 1、sort-排序

`sort(起始迭代器，结束迭代器，谓词)`

- 对容器元素进行排序
- 谓词，可填可不填，不填，默认从小到大排序
- 排序必须是可以随机访问的数据结构才能使用sort

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v;
v.push_back(10);
v.push_back(20);
// 使用
sort(v.begin(), v.end());
// 使用内置谓词排序
#include <functional>
sort(v.begin(), v.end(), greater<int>());
```

### 2、random_shuffle-随机调整

`random_shuffle(起始迭代器，结束迭代器)`

- 对方范围内元素随机调整次序

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v;
v.push_back(10);
v.push_back(20);

// 使用
random_shuffle(v.begin(), v.end());
// 使用随机种子
#include <ctime>
stand((unsigned int)time(NULL));
random_shuffle(v.begin(), v.end());
```

### 3、merge-元素合并

`merge(起始迭代器1，结束迭代器1，起始迭代器2，结束迭代器2，目标容器开始迭代器)`

- 容器元素合并，并存储在另一容器中
- 两个容器必须有序，合并后依然有序

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
vector<int> v2;
// 将v1，v2合并到dec容器中
vector<int> dec;
// 提前给容器分配空间
dec.resize(v1.size() + v2.size());

// 使用
merge(v1.begin(), v1.end(), v2.begin(), v2.end(), dec.begin());
```

### 4、reverse-反转

`reverse(开始迭代器，结束迭代器)`

- 反转指定范围内的元素

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
// 使用
reverse(v.begin(), v.end());
```

## 五、拷贝和替换

### 1、copy-复制

`copy(起始迭代器，结束迭代器，目标迭代器)`

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
// 目标迭代器
vector<int> dec;
dec.resize(v1.size());
// 使用
copy(v1.begin(), v1.end(), dec.begin());
```

### 2、replace-替换

`replace(起始迭代器，结束迭代器，旧元素，新元素)`

- 替换容器中的所有元素

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
// 使用，将20替换成200
replace(v.begin(), v.end(), 20, 200)
```

### 3、replace_if-条件替换

`replace_if(起始迭代器，结束迭代器，谓词，新元素)`

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;

// 自定义谓词
class Greater30 {
public:
    // 大于等于30的元素返回给replace_if，让器替换
    // 返回真，替换这个元素
    bool operator() (){
        return val >= 30;
    }
}
// 使用, 将大于等于30的元素替换成3000
replace_if(v.begin(), v.end(), Greater30, 3000);
// 使用谓词-仿函数不能提供大于某个数
#include <functional>
replace_if(v.begin(), v.end(), Greater30, 3000);

```

### 4、swap-交换

`swap(起始迭代器，结束迭代器，)`

- 必须是同类型的容器

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
vector<int> v2;
// 使用
swap(v1, v2);
```

## 六、算数生成

### 1、accumulate-累加

`accumulate(开始迭代器，结束迭代器，起始累加值)`

- 计算指定区间内容器元素的累加总和

``` c++
#include <numeric>
#include <vector>
// 准备数据
vector<int> v1;

// 使用，一般从0开始加起
accumulate(v1.begin(), v2.end(), 0);
// 从1000开始加起
accumulate(v1.begin(), v2.end(), 1000);
```

### 2、fill-添加元素

`fill(开始迭代器，结束迭代器，向容器中填充的值)`

- 向容器中填充元素

``` c++
#include <numeric>
#include <vector>
// 准备数据
vector<int> v1;
// 初始化空间，并不赋值
v1.resize(10);
// 使用，向容器中填充200
fill(v1.begin(), v1.end(), 200);
```

## 七、集合算法

### 1、set_intersection-交集

`set_intersection(开始迭代器1，结束迭代器1，开始迭代器2，结束迭代2，目标容器的迭代器)`

- 返回一个迭代器的结束位置

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
vector<int> v2;
// 目标容器
vector<int> dec;

// 人工计算2个容器中较小的容器大小
dec.resize(v2.size());
// 使用min算法
#include <algorithm>
dec.resize(min(v1.size(), v2.size()));

// 使用，返回值是迭代器结束位置
vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), dec.begin());
// 遍历，结束位置使用返回的itEnd，而不使用dec.end()，因为差集不一定是全的
for_each(dec.begin(), itEnd);
```

### 2、set_union-并集

`set_union(开始迭代器1，结束迭代器1，开始迭代器2，结束迭代2，目标容器的迭代器)`

- 求集合1，集合2的并集并放到目标容器中
- 两个集合必须是有序序列

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
vector<int> v2;
// 目标容器
vector<int> dec;
// 最特殊情况，没有交集，就是2个容器合并
dec.resize(v1.size() + v2.size());

// 使用，返回值是迭代器结束位置
vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), dec.begin());
// 遍历，结束位置使用返回的itEnd，而不使用dec.end()，因为差集不一定是全的
for_each(dec.begin(), itEnd);
```

### 3、set_difference-差集

`set_difference(开始迭代器1，结束迭代器1，开始迭代器2，结束迭代2，目标容器的迭代器)`

- 求容器1，容器2的差集，差集放到目标容器中
- 2个集合必须是有序序列

``` c++
#include <algorithm>
#include <vector>
// 准备数据
vector<int> v1;
vector<int> v2;
// 目标容器
vector<int> dec;
// 最特殊情况，没有交集，取容器大的大小
dec.resize(max(v1.size(),v2.size()));

// 使用，返回值是迭代器结束位置
vector<int>::iterator itEnd = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), dec.begin());
// 遍历，结束位置使用返回的itEnd，而不使用dec.end()，因为差集不一定是全的
for_each(dec.begin(), itEnd);
```

