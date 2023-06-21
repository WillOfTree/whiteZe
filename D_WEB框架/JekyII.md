# JekyII使用方式

## 安装方式

### 一、windows

1. 安装Ruby；下载地址：[rubyinstaller.org](https://rubyinstaller.org/downloads/) 

2. 安装RubyGames；下载地址：[Download RubyGems](https://rubygems.org/pages/download) （选择zip下载即可）

    ``` shell
    # 切换到RubyGames目录下运行命令
    # 安装
    ruby setup.rb        
    ```
    
3. 安装Jekyll（任意目录运行命令都可，因为他是安装在rubyGames目录下）

    ``` shell
    # 安装jekyll  
    gem install jekyll  
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

## 功能使用

### 一、文章分类



## 错误信息

### cannot load such file – webrick (LoadError)

原因：我们的Ruby版本太高了，3.0.0以上版本需要运行

解决方法：`bundle add webrick` 

#### Could not locate Gemfile

原因：缺少Gemfile文件

解决方法：`bundle init`
