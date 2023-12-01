# JekyII使用方式

## 安装方式

### 一、windows

1. 安装Ruby；下载地址：[rubyinstaller.org](https://rubyinstaller.org/downloads/) 

    ``` shell
    # 使用默认选项安装后运行命令
    ridk install
    # 之后就不用安装RubyGames
    # 附加选项必选则
    MSYS2 and MINGW development tool chain
    ```

2. 【非必须】安装RubyGames；下载地址：[Download RubyGems](https://rubygems.org/pages/download) （选择zip下载即可）

    ``` shell
    # 切换到RubyGames目录下运行命令
    # 安装
    ruby setup.rb        
    ```

3. 安装Jekyll（任意目录运行命令都可）

    ``` shell
    # 安装jekyll和bundler
    gem install jekyll bundler
    # 查看jekyll版本号
    jekyll -v    
    ```

### 二、Linux



## 使用方式

### 一、创建原始jekyll项目

运行server命令后默认会打开127.0.0.1:4000

``` shell
# 创建一个默认主题的项目（主题名minima） 
# 这个命令会新建一个目录，目录名就是BLOG
jekyll new BLOG 
# 不使用主题创建项目
jekyll new BLog --blank

# 开发环境使用的命令，若要部署使用jekyll build命令
# 切换到项目根目录
cd BLOG 
# 启动项目
jekyll server 
# 或者(推荐下面命令)
bundle exec jekyll serve
# 自动刷新文章
bundle exec jekyll serve --livereload
```

### 二、添加文章

在项目根目录下的 _posts 目录创建 markdown 文档。

这里注意 md 文档命名要添加 “yyyy-mm-dd”的前缀。
例如：2019-10-11-5分钟搭建博客.md

### 三、部署文档到Github page

使用 `jekyll build` 命令构建网站，并设置url为具体网站

将`_site` 目录下的文件全部上传到github即可

### 四、使用主题

#### Ⅰ、修改配置文件方法

> 这个方法会缺少页面等文件，从而造成页面缺失，但样式是存在的
>
> 使用 jekyll new *** 创建的方法

1. 安装主题：在项目根目录下找到 `Gemfile` 文件，追加要添加的主题（例如jekyll-theme-simplex）

    ``` shell
    # 将默认主题
    gem "minima", "~> 2.5"
    # 修改为想用的主题：jekyll-theme-simplex
    gem "jekyll-theme-simplex"
    ```

2. 运行命令：`bundle install` 安装主题

3. 修改 `_config.yml` 

    ``` shell
    # 将默认主题
    theme: minima
    # 修改为目标主题
    theme: jekyll-theme-simplex
    ```

4. 运行项目：`bundle exec jekyll serve` 

5. 如果主题中缺少layout文件可以通过 `bundle show 主题名` 找到主题目录，并从中复制缺少文件使用

#### Ⅱ、使用Download下载库方法

1. 从jekyll theme 下载主题，并解压

2. 进入目录执行命令：

    ``` shell
    bundle install
    bundle exec jekyll server
    ```

### 五、常用命令

1. `jekyll build`：生成部署服务器的静态文件（这会使用_config.yml中url参数）
2. `jekyll clean`：清除所有生成文件
3. `jekyll new XXXX --blank` ：创建一个空白的 jekyll 站点
4. `jekyll doctor`：输出配置的相关问题
5. `bundle install`：在Gemfile中安装依赖
6. `bundle exec jekyll serve` ：构建站点在本地服务器上（测试开发用）

## 功能使用

### 一、变量说明

#### Ⅰ、全局变量

| 变量       | 说明                                          |
| ---------- | --------------------------------------------- |
| site       | 全站的信息（_config.yml中的数据、全栈变量等） |
| page       | .markdown中开头写的变量信息                   |
| layout     | 布局                                          |
| content    | .markdown文件中写的内容                       |
| pageinator | 分页                                          |
| content    | 主页内容                                      |

#### Ⅱ、site全站信息

| 变量       | 说明                                         |
| ---------- | -------------------------------------------- |
| site.pages | 所有的页面集合，可进一步获取页面信息         |
| site.posts | 所有文章信息，包括文章分类、标题、时间等信息 |
|            |                                              |
|            |                                              |
|            |                                              |

#### Ⅲ、page页面信息

| 变量            | 说明                                |
| --------------- | ----------------------------------- |
| page.content    | 页面内容（.markdown中的正文内容）   |
| page.title      | 页面标题（.markdown中的title属性）  |
| page.categories | 分类（.markdown中的categories属性） |
|                 |                                     |
|                 |                                     |

### 二、文章分类

1. 给文章（post页面）和根目录下的.markdown文件（page页面）添加头信息，设置类别 

    ``` yaml
    ---
    category: dataStruct 
    ---
    ```

3. 修改post.html模板（分类模板）

    ``` html
    <!-- 如果post的category与page的category相同则显示这条信息
    注意：要重启服务，不然有可能会出错-->
    {% if post.category  == page.category %}
    <span>这里是显示post分类与page分类相同的文章列表</span>
    {% endif %}
    ```
    

### 三、显示数学公式

复制代码到页面即可

``` javascript
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({
        tex2jax: {
        skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
        inlineMath: [['$','$']]
        }
    });
 </script>
 <script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>
```



## 错误信息

### cannot load such file – webrick (LoadError)

原因：我们的Ruby版本太高了，3.0.0以上版本需要运行

解决方法：`bundle add webrick` 

### Could not locate Gemfile

原因：缺少Gemfile文件

解决方法：`bundle init`
