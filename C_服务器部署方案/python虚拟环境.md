# python虚拟环境

## pipenv

### 一、安装

``` shell
pip install pipenv
```

 ### 二、命令

``` shell
# 必须进入项目目录才能pipenv install命令
# 创建一个环境
pipenv install 
# 进入虚拟环境
pipenv shell        
# 安装库
pipenv install 库名    
# 删除库
pipenv uninstall 库名   
# 部署时会自动安装依赖
pipenv install  
# 退出
exit() 
```

## virtualenv

用于创建独立的Python环境，多个Python相互独立，互不影响，它能够：

1. 在没有权限的情况下安装新套件
2. 不同应用可以使用不同的套件版本
3. 套件升级不影响其他应用
4. 虚拟环境不需要和项目在同一个目录

### 一、安装

``` shell
# ubunto系统安装
sudo apt install python-virtualenv
# 使用pip安装（推荐）
pip install virtualenv
```

### 二、使用方法

``` shell
# 创建虚拟环境目录envs，可自定义，随意位置
mkdir envs
cd envs

# 创建虚拟环境，
# 不指定目录，会在当前目录创建
virtualenv 虚拟环境名称
# 指定目录，python版本
virtualenv 目录 --python=python3.9
# 以当前目录名创建虚拟环境
virtualenv .

# 默认情况下，虚拟环境会依赖系统环境中的site packages，
# 就是说系统中已经安装好的第三方package也会安装在虚拟环境中，
# 如果不想依赖这些package，那么可以加上参数 
# --no-site-packages建立虚拟环境
virtualenv --no-site-packages [虚拟环境名称]
```

### 三、进入虚拟环境

``` shell
# 创建虚拟环境env后 
# 运行虚拟环境中bin/activate激活环境
# /envs/bin/是目录
source /envs/bin/activate

# 删除虚拟环境，直接删除文件即可
rm -rf /envs
```

### 四、退出虚拟环境

``` shell
# 离开当前虚拟环境
deactivate

#如果没有启动虚拟环境，系统也安装了pip工具，那么套件将被安装在系统环境中，为了避免发生此事，可以在~/.bashrc文件中加上：
export PIP_REQUIRE_VIRTUALENV=true
# 或者让在执行pip的时候让系统自动开启虚拟环境：
export PIP_RESPECT_VIRTUALENV=true
```

### 六、常见错误

#### 1、错误信息：not on PATH

主要原因是python是系统级应用（root账号安装），而安装virtualenv的时候没有使用root账户

>  WARNING: The script virtualenv is installed in '/home/tree/.local/bin' which is not on PATH.
>   Consider adding this directory to PATH or, if you prefer to suppress this warning, use --no-warn-script-location.

解决方案：

``` shell
# /home/tree/.local/bin 是提示的virtualenv的安装路径
echo 'export PATH=/home/tree/.local/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

## Virtualenvwrapper

Virtaulenvwrapper是virtualenv的扩展包，用于更方便管理虚拟环境

l **需要先安装virtualenv**

pip install virtualenv

### 1、安装

\#sudo easy_install virtualenvwrapper

**pip install virtualenvwrapper**

**-------------------------------------------------------**

此时还不能使用virtualenvwrapper，默认virtualenvwrapper安装在/usr/local/bin下面，实际上你需要运行virtualenvwrapper.sh文件才行。

（1）创建目录用来存放虚拟环境**.virtualenvs**

***.virtualenvs\******目录可以自定义($HOME)\***

***.bashrc\******没有创建文件\***

l mkdir $HOME/.virtualenvs

l 在~/.bashrc中添加行：

export WORKON_HOME=$HOME/.virtualenvs

l 在~/.bashrc中添加行：

**#****这里目录位置要进行确认find / -name virtualenvwrapper.sh**

source **/usr/local/bin/**virtualenvwrapper.sh

（2）运行： source ~/.bashrc

### 2、命令

workon/lsvirtualenv#列出虚拟环境列表

mkvirtualenv [虚拟环境名称] #新建虚拟环境

\#创建指定版本的虚拟环境

mkvirtualenv -p [python3][路径] tensorflow 

workon [虚拟环境名称] #启动/切换虚拟环境

rmvirtualenv [虚拟环境名称] #删除虚拟环境

deactivate #离开虚拟环境

## PYthon环境安装

1、安装python3

ln -s /python3目录 /usr/bin/python 替换系统中默认的python2

2、使用python3安装pip

##  pip收集包信息命令

``` shell
# 安装包
pip install xxxx  
# 记录依赖
pip freeze > requirements.txt 

# 先进入虚拟环境
# 安装requirement.txt中记录的依赖
pip install -r requirements.txt 
```

### 

　

 