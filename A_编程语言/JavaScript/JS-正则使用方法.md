# JS正则使用方法

## 语法

1、创建正则表达式对象
2、使用regOBJ进行正则匹配

``` javascript
// 创建正则表达式
// 说明：/是限定正则表达式的字符
let 变量名 = /正则表达式/
```

## regOBJ方法

``` javascript
/**
 * test(str)
 * 说明：
 *    判断字符串str是否匹配表达式，返回一个。
 * 返回: 
 *    布尔值，匹配返回true，不匹配返回false
 * */
let reg = /前端/
let re = reg.test("AAA前端AAA")

/**
 * exec(str)，
 * 说明： 
 *     搜索查找指定的字符串,包含第一次出现的位置等信息
 * 返回:  
 *     成功返回数组，失败返回null
 * */
let reg = /java/
let re = reg.exec("javascript")
```

## 修饰符

``` javascript
/**
 * g：代表可以进行全局匹配。
 * i：代表不区分大小写匹配。
 * m：代表可以进行多行匹配。
 * 上面三个参数，可以任意组合，代表复合含义，当然也可以不加参数。
 * */
// 例子
let reg=/abc+f/g;
```