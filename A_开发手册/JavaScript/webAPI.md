# WEB API

## CSS选择器

| 选择器  | css中定义 | 说明                                    | html中使用  |
| ------- | --------- | --------------------------------------- | ----------- |
| .class  | .AAA      | 带有指定class属性的标签                 | class="AAA" |
| #id     | #AAA      | 带有指定id属性的标签                    | id="AAA"    |
| *       | *         | 所以元素                                |             |
| element | div       | html标签名称                            |             |
| ele,ele | div,span  | div与span的标签被选择                   |             |
| ele ele | div span  | 选择div下的span标签                     |             |
| ele>ele | div>span  | 选择div的**孩子**标签，**span的标签**   |             |
| ele+ele | div+span  | 选择div**紧跟着**的span标签（兄弟标签） |             |
| :active | a:hover   | 伪选择器，a标签在鼠标移入的状态         |             |

``` css
// css定义方法
// 选择器 {...}
// 样例
div { color:red; }
.AAA { font: 10px; }
```

## DOM 页面文档对象模型

### querySelector-单个对象

``` javascript
/**
 * 作用：
 * 获取DOM元素对象,默认获取第一匹配的元素，且只能获取一个元素，
 * 若没有获取到任何元素，返回 null
 * 参数：
 * css选择器，详情见百度css选择器
 * */
document.querySelector("css选择器")

// 例题
document.querySelector("div") //通过标签
document.querySelector(".three") //通过class样式
document.querySelector("ul li:last-child") //css样式
document.querySelector("css选择器")
```

### querySlectorAll-多个对象

``` javascript
/**
 * 作用：
 * 获取一组DOM对象,返回一组Nodelist对象（数组）
 * 没有pop，push数组方法，只能通过for遍历获取
 * 参数：
 * css选择器，详情见百度css选择器
 * */
document.querySelectorAll("css选择器")

//例子
document.querySelectorAll("ul li")
document.querySelectorAll("ul li")[1] //获取其中第一个元素数组
// 同时给多个元素绑定事件
let close_btn = document.querySelectorAll(".close")
for(let i=0; i<close_btn.length;++i)
{
    close_btn[i].addEventListener("click", function(){
        this.parentNode.style.display = "none" //关闭当前按钮
    })
}
```

### 其他补充获取元素方法

以下选择器可后接querySelector与querySelectorAll方法进一步查找标签

``` javascript
/**
 * 作用：根据ID获取一个元素
 * */
document.getElementById("ID")

/**
 * 作用：通过标签获取元素
 * */
document.getElementByTagName("div")

/**
 * 作用：通过类名获取元素
 * */
document.getElementByClassName("w")
```

### 设置修改DOM内容

``` javascript
/**
 * 作用：将文本添加进<body></body>之间，识别标签
 * */
document.write("")

// 样例
document.write("Hello world!")
document.write("<h1>AAA</h1>")

/**
 * 作用：
 * 将文本内容添加/更新任意标签位置
 * innerText 不解析标签
 * innerHTML 解析标签
 * */
let d = document.querySelector("div")
d.innerText // 输出标签内的内容
d.innerText = "BBB" //修改标签内的内容
d.innerHTML = "<span>AAA</span>"; //解析标签内容
// 模板字符串
let year = 2020;
d.innerHTML = `今天是：${year}年`
```

### 修改元素属性

``` javascript
// 获取元素，前提
let e = document.querySelector("img")

/**
 * 修改图片属性，对象必须是图片
 * */
e.src = "./image/a.png" //修改图片
e.title = "xxxx";   //修改标题
e.href = "http://xxx.com"; //修改链接

/**
 * 修改style属性样式，所以样式都可使用style.属性进行修改
 * */
e.style.backgroundColor = "red" 
e.style.width = "300px"
e.style.marginTop = "50px"

/**
 * 操作class类内容
 * 属性使用=赋值，方法使用()赋值
 * */
e.className = "BBB"; //将class属性替换为BBB
e.classList.add("ccc"); // 追加添加CCC属性
e.classList.remove("CCC"); // 删除指定CCC属性
e.classList.toggle("CCC"); // 切换CCC，有CCC进行删除，没有进行添加
```

### 修改表单属性

``` javascript
// 获取表单，前提
let f = document.querySelector("form")

/**
 *  <input type="text" value="请输入"></input>
 * */
f.value //直接获取input输入的内容
f.value = "AAA"; //修改input的内容
f.type //获取type的属性
f.type = "password" //修改type的内容

/**
 * //disable 默认不可用
 * <button disable></button>
 * */
f.disable = true //禁用属性，true禁用，false启用

/**
 * // checked 默认勾选
 * <input type="checkbox" checked></input>
 * */
f.checked = false //true勾选，false不勾选
```

### 定时功能

``` javascript
/**
 * // 单位毫秒，1000毫秒=1秒
 * setInterval 永久循环
 * */
setInterval(function(){...}, 1000) //匿名函数调用方法

//指定运行AA方法，加（）是调用，所以不加（）
function AA(){...}
setInterval(AA, 1000); 

// 关闭定时
let timer = setInterval(AA, 1000);
clearInterval(timer)
```

### 事件

``` javascript
// 获取元素
let e = document.querySelector("button")

/**
 * <button></button>,L1已经被抛弃
 * */
e.onclick = function(){..}

/**
 * 添加事件，L2~L3
 * AAA: 触发条件，click单击，mouseover鼠标经过
 * func: 要执行的函数
 * */
e.addEventListener("AAA", func)
e.addEventListener("click", function(){
    alert("被点击")
})

// 常用事件
e.addEventListener("click", func) //点击事件
e.addEventListener("mouseenter", func) //鼠标移入
e.addEventListener("mouseleave", func) //鼠标移出
e.addEventListener("mouseover", func) //鼠标移入,会有事件冒泡
e.addEventListener("mouseout", func) //鼠标移出，会有事件冒泡
e.addEventListener("focus", func) //获取焦点
e.addEventListener("focus", func) //获取焦点
e.addEventListener("blur", func) //失去焦点
e.addEventListener("keydown", func) //键盘按下
e.addEventListener("keyup", func) // 键盘抬起
e.addEventListener("input", func) // 输入事件
```

### 查找DOM节点方法

``` javascript
// 获取元素
let e = document.querySelector("div")

/**
 * 查找父节点，找不到返回null
 * */
e.parentNode // 获取父节点
e.parentNode = "xxx" //父节点赋值，基本没用
e.parentNode.parentNode //获取爷爷节点

/**
 * 查找孩子节点,返回的是一个数组
 * */
e.childNodes //获取子节点，包括文本，注释节点；不常用
e.children //所有孩子节点
e.children[0] //第一个孩子

/**
 * 查找兄弟节点，相邻的节点
 * */
e.nextElementSibling //下一个节点
e.previousElementSibling //上一个节点

/**
 * 创建节点
 * */
document.createElement("标签名")
let mdiv = document.createElement("div") //创建一个div标签
mdiv.className = "current" //给创建的div标签添加属性

/**
 * 追加节点,在获取的指点节点后添加孩子节点div
 * */
e.appendChild("div")
e.appendChild(mdiv) //添加自己创建的节点

/**
 * 插入节点，在指定元素之前
 * */
e.insertBefore("元素名", "在某个元素前面")
e.insertBefore("span", mdiv) // 在创建的mdiv标签前添加<span>标签
e.insertBefore(mdiv, mdiv2) // 在创建的元素mdiv2前添加自创建的mdiv标签

/**
 * 克隆节点
 * R 为真，克隆时包含后代节点一起
 * R 为假，不克隆后代节点
 * */
let c = e.cloneNode(R) //对e 这个获取的对象进行克隆
doucment.body.appendChild(c) //将克隆的节点插入指定位置

/**
 * 删除节点，一定时从父元素中删除孩子节点
 * */
e.removeChild(元素)
// 例子
let a = document.querySelector("button")
e.removeChild(a) //删除a的孩子节点button

```

## 时间对象

``` javascript
/**
 * 
 * */
let data = new Date()  // 当前时间
let data = new Data("2022-5-8 18:28:30") //指定时间

/**
 * 
 * */
data.getFullYear() //获取年
data.getmonth()  //获取月份,取值范围时0~11，要加1
data.getdata() //获取日
data.getHours() //获取时
data.getMinutes() //获取分
data.getSeconds() //获取秒
data.getDay() //获取星期几, 0是星期天

/**
 * 时间戳，单位毫秒
 * */
let t = data.getTime() //获取当前时间戳
let t = +new Date() //获取当前时间戳
let t = Date.now()
let t = data.getTime("2020-8-1 12:00:00") //获取指定时间的时间戳
let t = +new Date("2020-8-1 12:00:00") //获取指定时间的时间戳
let t = Data.now("2020-8-1 12:00:00") //获取指定时间的时间戳

/**
 * 转换时间
 * */
// count 时间戳
let h = parseInt(count / 60 / 60 % 24)
h = h < 10? "0" +h: h //转换为 00 形式

let m = parseInt(count / 60 % 60)
let s = parseInt(count % 60 )
```

## 事件对象

事件有两个阶段，捕获阶段和冒泡阶段
冒泡：如果存在嵌套的DIV中都绑定了事件，当最里面的事件触发，会依次促发父类事件
事件委托：给父级添加事件，这样点击孩子属性就可以触发孩子事件

``` javascript
// 获取元素
let e = document.querySelector("div")
/**
 * e.addEventListener("click", function(event){})
 * 中的event就是事件对象
 * */
e.addEventListener("click", function(event){})

/**
 * event常用属性
 * */
event.type //当前事件类型
event.clientX //光标相对于游览器可见窗口的位置
event.clientY 
event.offsetX //光标相对于当前DOW元素的位置
event.offsetY
event.key //用户按下的字母

/**
 * 阻止事件流动，阻止事件冒泡
 * */
e.addEventListener("click", function(event){
    event.stopPropagation() //停止事件冒泡
})

/**
 * 事件委托：提高性能，不用给每一个孩子节点添加事件
 * 通过target获取当前触发元素
 * 
 * <ul>
 *  <li></li><li></li>
 * </ul>
 * */
let l = document.querySelect(ul)
// 给父级添加事件
l.addEventListener("click", function(event){
    e.target // 当前点击的对象
    e.target.style.color = "red"; //样例
})
```

## 位置定位-scroll

``` javascript
/**
 * 滚动事件
 * */
window.addEventListener("scroll", function(){}) // 给窗口添加滚动事件
document.addEventListener("scroll", function(){}) //给当前页面添加滚动事件

// 获取滚动距离
window.addEventListener("scroll", function(){
    this.scrollTop // 看不到顶部距离
    this.scrollLeft // 看不到的左边距离
})
// 获取
let d = document.querySelector("div")
d.scrollWidth //overflot 显示的内容宽度
d.scrollHeight // overflot 显示的内容高度
```

## 元素位置-offset

``` javascript
/**
 * 包含padding margger大小
 * */
let d = document.querySelector("div")
d.offsetWidth // div的宽度大小
d.offsetHeight
d.offsetTop  // 只读
d.offsetLeft // 只读
```

## 元素位置-client

``` javascript
/**
 * 当前可视区域大小,不包含边框等等
 * */
let d = document.querySelector("div")
d.clientWidth // div的宽度大小
d.clientHeight
d.clientTop  // 
d.clientLeft // 

/**
 * 窗口尺寸改变时触发
 * */
window.addEventListener("resize", function() {})
```

## BOM 游览器对象模型

BOM游览器对象包含window
window内包含navigator,location,document,history,screen属性

### window对象

``` javascript
/**
 * 加载事件，也可以针对某个元素添加load事件
 * */
window.addEventListener("load", function(){A}) //加载完成执行A
document.addEventListener("DOMContentLoaded", function(){}) //当所有元素加载完成后促发，不等待样式表，图像

/**
 * 延迟函数, 只能执行1次
 * */
let timer = setTimeout(function(){}，T)

let timer = setTimeout(function(){
    console.log()
}, 5000)
clearTimeout(timer)
```

### location对象

``` javascript
// href属性
location.href = "http://www.baidu.com" //跳转到指定页面
console.log(location.href) // 当前页面的url地址
// search属性
location.search //获取 url地址中？后面的部分
// hash
location.hash //获取地址中的hash值，url中#后面的字符
//reload
location.reload() //刷新页面
location.reload(true) //强制刷新
```

### navigator对象

主要记录了游览器自身的相关信息

``` javascript
navigator.userAgent //游览器的版本及平台
```

### histroy对象

``` javascript
// 后退1个页面
history.back()
// 前进1个页面
history.forward() 
// 前进/后退 n个页面
history.go(1)  // 前进1个页面
history.go(-1) // 后退1个页面
```

### swiper插件 

swiper 常用于移动端网站的特效插件
min的是进行压缩后的

### 本地存储

``` javascript
/**
 * localStorage
 * 生命周期永久
 * */
localStorage.setItem(key, value)
localStorage.setItem("key", "AAA") //保存
localStorage.getItem("key") //获取
localStorage.removeItem("key") //删除

//存多个数据
let o = {
    key: "xxx", key2:"xxx"
}
// json属性和值都是双引号保存
// 保存
localStorage.setItem("obj", JSON.stringify(o))
// 取出
JSON.parse(localStorage.getItem("obj"))

/**
 * sessionStorage
 * 生命周期为游览器窗口关闭，用法与localStorage相同
 * /
```