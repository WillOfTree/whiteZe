# ES6语法

## 基本语法

### 一、const与let

1. const必须初始化，不可重复赋值
2. let可以不初始化

## export

### 一、export const与default

1. export const可以导出多个
2. export default只能有一个默认导出

``` javascript
// 导出时名称是 `PI`，导入时必须同名
import { PI } from './utils.js';

// 导出时未命名，导入时可自定义名称
import CustomName from './utils.js';
```



```javascript
// 📁 utils.js
const APP_NAME = 'MyApp';
export default APP_NAME;  // 导出


// 📁 main.js
import appName from './utils.js';  // 导入（名字可以任意取）
// 导出多个
import { PI, double } from './math.js';    // 必须用{}且名字固定
```

## 箭头函数

- 比普通函数更简洁，没有自己的`this` 
- 格式：`const A = (callback) => {}` 
- 格式：`()=>{}` 等价于匿名函数`function {}` 

```javascript
// 传统函数
function add(a, b) { return a + b; }

// 箭头函数等价写法
const add = (a, b) => { return a + b; };
const add = (a, b) => a + b;  // 单行可省略return和{}
```

## 回调函数

- **本质**：把一个函数作为参数传给另一个函数
- 格式：`A.b(err => {})` 

```javascript
// 1. 定义主函数,callback是调用的其他函数
const mainFunction = (callback) => {
  callback(data); // 执行回调函数，并传入数据
};

// 2. 其他函数
const myCallback = (result) => {
  console.log("回调函数收到结果:", result);
};

// 3. 使用
mainFunction(myCallback);
```

## 动态添加方法

- **本质**：JavaScript对象可以随时扩展，给对象添加属性或方法
- 格式：`A.b = (err) => {}`

``` javascript
// 创建一个空对象
const logger = {};

// 动态添加-普通方法
logger.error = function(msg) {
  console.error('[ERROR]', msg);
};

// 动态添加-箭头函数方法
logger.warn = (msg) => {
  console.warn('[WARNING]', msg);
};

// 使用
logger.error('系统崩溃!'); // 输出 [ERROR] 系统崩溃!
logger.warn('内存不足');  // 输出 [WARNING] 内存不足
```

