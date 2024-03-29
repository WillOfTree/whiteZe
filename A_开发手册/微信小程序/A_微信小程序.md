# 微信小程序开发

1. 注册小程序开发账号（个人账号无法使用微信支付等功能）
   mp.weixin.qq.com

2. 创建项目

## 目录文件说明

### 文件

+ pages 存放所以小程序页面

+ utils 用于存放功能模块的文件夹

+ app.js 小程序入口文件

+ app.json 小程序全局配置文件

+ app.wxss 小程序全局样式文件

+ project.config.json 项目配置文件

+ sitemap.json 配置小程序页面是否允许被索引到

### app.json

```javascript
{
    "pages":[ //记录小程序所以的页面
        "pages/index/index",
    ],
    "window":{ //全局定义小程序所有的页面背景，文字颜色等
        "backgroundTextStyle":"light",
        "navigationBarBackgroundColor": "#fff",
        "navigationBarTitleText": "Weixin",
        "navigationBarTextStyle":"black"
    },
    "style": "v2", //全局定义小程序使用的样式版本
    "sitemapLocation": "sitemap.json"//指明文件的位置
}
```

### sitemap.json

```javascript
{
    "desc": "",
    "rules": [{
        "action": "allow", //允许索引。 disallow不允许的索引
        "page": "*"  //被允许的索引页面
    }]
}
```

### 新建小程序页面

1. 在app.json中的pages字段添加页面路径

2. 保存后微信会自动创建文件

3. 小程序首页默认是读取app.json中pages字段的第一个

## 生命周期

### 应用生命周期(app.js)

```javascript
App({
    onLaunch(){
        // 应用第一次触发，可获取用信息
    },
    onShow(){
        // 当用户看到的时候被触发
        // 对页面和数据进行重置
    },
    onHide(){
        // 应用被隐藏触发
        // 暂停，清除定时器
    },
    onError(err){
        // 应用出错的时候触发
    },
    onPageNotFound(){
        //应用第一次启动，页面没有找到时触发
    }
})
```

### 页面生命周期(page)

注意：区分大小写

```javascript
page({
    data:{}
    onLoad(){
        // 页面加载完成触发
        // 异步请求，初始化页面数据
    },
    onReady(){
        // 监听页面初次渲染完成
    },
    /**
     * 生命周期函数--监听页面显示
     */
    onShow() {    },
    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide() {    },
    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload() {    },
    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh() {    },
    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom() {   },
    /**
     * 用户点击右上角分享
     */
    onShareAppMessage() {  }
})
```

## WXML模板语法

### 标签-text

```html
<text selectable></text> //长按选择复制
```
### 标签-image
``` html
<!-- image标签 
images.ac.cn 一个网络图片服务
mode: 决定属性如何配置图片
    aspectFit，保持宽高比，优先长边
    aspectFill 保持宽高比，优先短边
    widthFix   宽度不变（指定），高度自动调整
- [ ] ![]()lazy-load 惰性加载
--> 
<image src="http地址" mode="" lazy-load>
```

### 标签-swapipe
<!-- swaipe标签 
-->

### 标签-navigator
``` html
<!-- navigator标签
url 要跳转的路径
target: 可跳到其他的小程序
    self 默认值，自己的小程序
    miniprogram 其他的小程序
open-type 跳转方式
    navigate 左上角带有返回按钮， 不能跳tabbar页面
    redirect 不带返回，不能跳tabbar页面
    switchTab 跳转到tabbar
    reLaunch 关闭其他页面，打开某个页面
    exit miniprogram有用
-->
<navigator url="/pages/..." target="" open-type=""></navigator>
```

### 标签-rich-text 

``` html
<!-- rich-text标签
显示代码的标签 
-->
```

### 标签-button

``` html
<!-- button标签
size 改变大小 type 改变颜色 plain 镂空 loading 加载
contact 直接打开客服对话
share 转发当前小程序
getPhoneNumber获取当前用户的手机号
    1.手机号是加密的，需要后台进行解密
getuserInfo 获取当前用户信息
launchapp 在小程序中直接打开
opensetting 打开授权页面
-->
<button open-type="getPhoneNumber" bindgetphonenumber="getnum">
```

### 标签-icon

``` html
<!-- icon标签 
图标标签
-->
```

### 标签-radio

``` html
<!--  
radio标签必须要和父元素 radio-group使用
bindchage 绑定的事件
-->
<radio-group bindchage="">
    <radio value="AAA">111</radio>
</radio-group>
```

### 标签-checkbox

``` html
<!-- checkbox标签

-->
<checkbox-group bindchange="">
    <checkbox value="" wx:for="" wx:key="id"> xxx </checkbox>
</checkbox-group>

<!-- swaipe标签 
-->
```

### 标签-navigator传值

```javascript
/**
 * HTML
 * navigator的属性url后拼接?id(参数名字)=要传递的值 
 * */
<navigator url=”/pages/index/a?courseUuid=11”></navigator>

/**
 * 取值
 * options 是包含url地址中参数的对象，可以直接 点 获取
 * */
onLoad:function(option){
    let a = options.courseUuid
}
```

### 标签-for

``` javascript
/**
 * wx:for="{{数组}}"
 * wx:for-item="循环项的名称"
 * wx:for-index="循环项的索引"
 * wx:key
 * */ 
<view wx:for="{{mlist}}" wx:for-item="item" wx:for-index="index">
    索引：{{index}}--{{item.msg}}
</view>
```

### 标签-block

```html
/* 占位标签,相当注释 */
<block></block>
```

### 标签-if

```html
方式一
<block wx:if="{{true}}">
    <view>显示</view>
</block>
<block wx:elif="{{true}}">
    <view>显示</view>
</block>
<block wx:else>
    <view>显示</view>
</block>
方式二
<view wx:if="{{true}}" ></view>
<view wx:elif="{{true}}" ></view>
<view wx:else >显示</view>
```

### 获取form表单的值

```javascript
//（1）填写表单点击调用方法
<form bindsubmit="back_houtai">
    
//（2）标签添加 name
<input name="name"></input> // 标示key
<view name="type">{{picker}}</view>// 标示key

//（3）js
back_houtai (event) {
    console.log(event）
}
```

### 获取view\text等的值

```javascript
通过设置data-变量名传值
（1）添加data属性
<view data-name=”{{ss}}” bindtap=”fun_c”></view>
(2)js获取
fun_c (event) {
    console.log(event) // event中包含name的数据
}
```

## 小程序组件使用

### 组件生命周期

``` javascript
Component({
  lifetimes: {
    attached: function() {
      // 在组件实例进入页面节点树时执行
    },
    detached: function() {
      // 在组件实例被从页面节点树移除时执行
    },
      created: function(){
          //在组件实例刚刚被创建时执行
      },
      ready: function(){
          //在组件在视图层布局完成后执行
      }
  }
})
```



### 组件-创立

共用部分分离，类似laout布局
注意：父组件向子组件传递值后，系统会复制一份到子组件，并不改变原数据，当需要改变源数据的时候，
    需要子组件触发父方法

```javascript
/**
 * 1. 创建组件
 *    组件必须文件js、wxss、json、wxml四个文件
 * 2. 声明这是组件
 * */
// 组件.wxml 创立标签
<navbotto> ... </navbottom>
// 组件.json
{"component": true,}

/**
 * 3. 定义组件
 *    使用component方法代替page方法
 * */
// 组件.js
Component({
    properties: {},
    data: { // 组件内部数据，自存在与组件中 },
    methods: { // 组件方法
        customMethod () {}
    }
})

/**
 * 4.使用组件
 *   在要使用组件的页面，添加组件位置与标签
 *   
 * */
// 父.json
"usingComponents": {
    "navbottom": "/pages/Component/nav-bottom/index" //组件位置
}
// 父.wxml
<navbottom></navbottom>
// wx:if控制组件是否显示
<addinfo wx:if="true"></addinfo>
<home wx:if="{{AA}}"></home> 
```

### 组件-父向子传递数据

```javascript
/**
 * 通过标签属性传递
 * */
// 父页面-定义数据
<Tabs aaa="1111"></Tabs>
<tabs tab="{{dat}}"></tabs>

// 子组件接收数据
component({
    properties: { 
        aaa: { // 声明要传递的变量名
            type: string, // aaa的类型
            value: "" // aaa的默认值
        }
    },
})

// 子组件直接使用变量 aaa
<view>{{aaa}}</view>
```

### 组件-子触发父函数+传递数据

```javascript
/**
 * 子组件使用triggerEvent触发
 * */
// 子组件添加方法
component({
    methods：{
        myfangfa(){ // 自定义方法名-组件定义的方法
            //this.triggerEvent("触发父类的方法", "{传递的数据}")
            this.triggerEvent("itemChange", "{AA:111}")
        }
    }
})

// 父组件 .wxml
<Tabs binditemChange="fathefunc"></Tabs>
// 父组件 .js
page({
    fathefun(){  } // 被触发的方法
})
```

### 组件-父触发子方法

```javascript
/**
 * 
 * */
// 父类wxml
// 给要触发的组件添加id
<loading id="loading"></loading>

//父类.js
a = this.selectComponent("#loading")
a.loadProgress()

//子类.js
methods:{
    loadProgress() {} //要触发的方法
}
```

### 自定义-slot

slot标签就是一个占位符，父组件调用子组件的时候再传递标签

```javascript
/**
 * slot插槽（占位），用于承载组件引用时提供的子节点
 * name用于标识slot
 * 默认组件会出现再slot标签内
 * */
// 子组件
<slot></slot>

// 父组件
// block中的数据将传递到子组件slot的位置上
<tabs>
    <block wx:if="{{t.isactive}}">t的isactive是真显示这一块</block>
    <block wx:elif="tt"></block>
</tabs>

/**
 * 指定位置slot
 * */
// 子组件
<slot name="custom1"></slot>
// 父组件
<navbottom>  // 组件
    <view slot="custom1">我将填写到name=custom1的组件位置</view>
</navbottom>
```

### 组件使用全局样式

``` javascript
/**
 *
 **/
// .js
Component({
	options: {
		addGlobalClass: true  //这里是设置项
	},
	data: {}
})
```



## 模块功能

## 返回更新上一页数据

``` js
/**
业务流程：从A页面到B页面，再由B返回A页面，返回时更新A页面数据
不要在 App.onLaunch 的时候调用 getCurrentPages()，此时 page 还没有生成
*/ 
// A页面
page({
    data:{},
    //自定义方法
    btndelt(){
        // 获取页面栈，主要这个函数写错会出现未定义错误，
        // getCurrentPages可以在任意地点调用
        let pages = getCurrentPages()
        // 当前页面对象
        let current = pages[pages.length - 1]
        // 获取上一页
        let prepage = pages[pages.length - 2]
        // 调用上一页中的方法
        prepage.dosth(A,b)
    }
})

// B页面
page({
    data:{},
    //自定义方法
    dosth(a,b){
        console.log("做些事情")
    }
})
```

### 获取多个input输入数据

``` javascript
/**
 *
 **/
// wxml
<view wx:for="{{test}}">
     <textarea data-index="{{index}}" bindinput="textareaBInput" ></textarea>
</view>

//js
page({
    data: {
        inputvalue:[]
    },
    textareaBInput(e){
        // data-index 用于区别不同的input
        index = e.currentTarget.dataset.index;
        // 保存到data变量中
        this.data.inputvalue[index] = e.detail.value
    }
})
```



### 分页逻辑与数组拼接

``` javascript
/**
 * 服务器返回的数据要包含总条数，这样可以计算当前页是否为最后一页
 **/

/**
 * 数组拼接
 **/ 
this.setData({
    // ... 是新语法，数组解构
    // this.data.goodsList是之前的数据
    // res.goods是新请求的数据
    goodsList: [...this.data.goodsList, ...res.goods]
})
```



### 获取自定义数据/ this使用

``` javascript
/**
 *
 **/
page({
    data:{}
    queryData:{}, // 自定义的数据，使用this获取
    onLoad:function(){
    	this.queryData	
	},
    myfunc(){},
    myfunc2(){
         this.myfunc() //调用自定义方法,myfunc
         this.data.A; // 获取data中的数据
    }
})
```

### 本地缓存

先判断本地数据是否存在和是否过期而决定是否重新请求数据

``` javascript
/**
 * 常用方法
 * 以Sync结尾都是异步方法。同步方法和异步方法的区别是：
 * 同步方法会堵塞当前任务，直到同步方法处理返回。
 * 异步方法不会塞当前任务。
 * 一般选用异步方法
 **/
// 保存
wx.setStorageSync('key', 'value') 
// 读取
// 当数据不存在或获取失败，返回假，成功返回真
wx.getStorageSync('key')

/**
 * 不常用方法
 **/
// 1、插入
wx.setStorage({ //异步
  key:"key",
  data:"value"})
//2、读取
wx.getStorage({
  key: 'key',
  success (res) { // 可不添加
    console.log(res.data)
}})

/**
 * 3、删除
 **/
wx.removeStorage 
wx.removeStorageSync

/**
 * 清空
 **/
wx.clearStorage //异步
wx.clearStorageSync //同步

/**
 * 获取缓存信息
 **/
wx.getStorageInfo 
wx.getStorageInfoSync
```

### 事件绑定

```javascript
/**
 * 绑定事件
 * bindtap - 点击事件
 * bindinput - 输入事件，输入内容
 **/

// 双向绑定
//bindinput input绑定事件
//<input type="text" bindinput="myinput"/>
page({
    data: {
        num: 0
    },
    myinput(e){
        e.detail.value //input输入框的数据
        // 修改 data中num的数据
        this.setData({
            num: e.detail.value
        })
    }
})

// bindtap 当定点击事件
// 无法在wxml中直接传参数
// <button bindtap="mybutton"></button>
// 给点击事件传递参数
// <button bindtap="mybutton" data-operation="{{1}}">
page({
    data: {
        num: 0
    },
    mybutton(e){
        // 通过e获取自定义属性的传值
    }
})
```

### 数据绑定

```javascript
// wxml
// 字符串类型的数据
<view>单字符串：{{info}}</view>

// 自定义属性
<view data-AAA="bb"></view>
<checkbox checked="{{ischeck}}"></checkbox>

// .js文件中
page({
    data: {
        // 字符串类型的数据
        info: "init data",
        // 列表渲染
        mlist: [{msg: "xx"}, {msg: "x2"}],
        // 自定义属性
        bb: true,
        ischeck: false, //控制check
    }
})
```

### 页面跳转

``` javascript
```



### 登录返回

```javascript
// 返回前一页
wx.navigateBack({
    delta: 1
})
```

### 使用UI文件

```css
// 从colorUI目录下复制colorui目录到项目根目录
// app.wxss添加：
@import "colorui/main.wxss";
@import "colorui/icon.wxss";
@import "colorui/animation.wxss";
```

### 使用自定义字体图标

``` javascript
```

### 获取公用参数/ app.js参数

``` javascript
App({
      onLaunch() { // 展示本地存储能力},
      // 全局公用属性，必须填写在onLaunch方法下面
      globalData: {
     		"AAA": "aaa"
      }
})
    
// 调用方法
let app = getApp();
var a = app.globalData.userPhone
// 临时改变
app.globalData.AAA = userPhone
```



### module方法导出

``` javascript
/**
 * 新建功能文件文件util.js
 **/
// 正常编写函数
function geturl(){
      const url = "https://cctv.cc/glaucoma/"
      return url;
}

// 导出方法
module.exports = {
    // 调用的方法名 ： util中的方法名
  	formatTime: formatTime,
  	geturl:geturl
}

/**
 * 调用方法
 **/
// 引用方法
var util = require("../../utils/util.js");
// 调用
var url = util.geturl();
```



### export方法导出

```javascript
/**
 * 1. 写插件.js
 * request - 导出的方法名称
 * params - request函数需要的参数
 * */
// 插件js
export const request=(params) => {}


// 使用插件的js
// request是导出的方法名称，地址一定要写相对地址
import { request } from "../../utils/request.js";

// 使用方法
request({url:"xxxx", data: {}, method: "get"}).then(result=>{
    // 数据返回的方法
})
```

### wx.request网络请求

```javascript
/**
 * 原始方法：wx.request({})
 * */
wx.request({
    url: "地址",
    data: {},
    method: "get",
    dataType: "json",
    // 这个方法一定要写text,不然会有可能获取不到返回值
    // 甚至时promise.then都无法顺利执行
    responseType: "text",
    success: (result) => {
        // 请求成功返回数据
    },
    fail: () => {// 失败事件}
})

/**
 * 取消异步请求
 * request - 导出的方法名称
 * params - request函数需要的参数
 * */
export const request=(params) => {
    const baseUrl = "xxxxxxxx";
    return new Promise((resolve, reject) =>{
        wx.request({
            ...params, // 解构方法
            url: baseUrl + params.url,
            sucess: (result) => {
                resolve(result);
            },
            fail: (err)=>{
                reject(err);
            }
        })
    })
}
```

### 登录功能

1. 登录准备工作

   + code 用户登录凭证，wx.login()获取
   + encryptedData 用户信息密文， getUserProfile获取
   + iv 加密算法偏移量， getUserProfile获取
   + rawData 用户信息原始数据 getUserProfile, JSON.stringify获取
   + signature sha1得到的字符串 getUserProfile获取

2. 基本流程

   + 先获取用户信息（getUserProfile)
   + 保存用户信息
   + 使用wx.login获取code
   + 将所有数据发送到后台服务器，换取Token
   + 服务器端需要配置appid,secret,jscode这3个参数，其中appid,secret是通过小程序后台获取的

3. 页面butten按钮设置-获取用户信息

   ```javascript
   /**
    * // wxml登录是固定写法，必须这么写
    * <button open-type="getUserInfo" @getuserinfo="onGetUserInfo">
    *
    * 新写法：
    * <button bindtap="getUserProfile"></button>
    * */
   methods: {
       getUserProfile(e) {
           if(e.detail.errMsg === "getUserInfo:fail auth deny")
               return " 你取消了登录授权 "
   		// 获取用户信息
           wx.getUserProfile({
               // 声明获取用户个人信息后的用途，后续会展示在弹窗中，请谨慎填写
               desc: '用于完善会员资料', 
               success: (res) => {
                   this.setData({
                       userInfo: res.userInfo,
                       hasUserInfo: true
                   })
                   
                   // 保存个任务信息
                   wx.setStorageSync("userinfo", e.detail.userInfo)
               }
           })
           
           
           // 跳回首页
           wx.nagigateBack({
               delta:1
           })
       }
   }
   ```

### setData

``` javascript
8、setData
setData会更新页面中的数据
设置第N个数据
this.setData({
“data_str[1].name”: “myname”
})
设置第N个数据，但需要变量
let a = “data_str[“ + num + “].name” // 设置key
this.setData({
[a]: “myname”
})
```

### 使用es7的async语法

``` javascript
/**
 * 解决回调问题
 **/
```

### 下拉刷新功能

(1) wxml给页眉（tab）设置style

// 这是设置，下拉tab固定在页眉

style="position: fixed;width:100%;z-index:1000;top:0rpx"

(2) json添加

"enablePullDownRefresh": true

(3) js添加触发事件

onPullDownRefresh: function () { },

### 支付功能
