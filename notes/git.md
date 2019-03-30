<!-- GFM-TOC -->
* [一、环境配置](#环境配置)
    * [gitlab](#gitlab)
* [二、git的使用](#git的使用)
    * [submodule](##submodule）
    * [添加submodules](###添加submodules）
    * [clone带有submodule的仓库](###clone带有submodule的仓库）
    * [修改submodule](###修改submodule）
<!-- GFM-TOC -->


# 一、环境配置

## 1. --winodws
### 1.1 TortoiseGit

TortoiseGit免密码
- PuTTy Key Generator 生成 密钥对；
- TortoiseGit setting-> Git -> Remote 中 putty key 填入保存的私钥文件即可

## 2. linux
### 2.1 git的安装

sudo apt-get install git
git --version

## 3. mac

mac默认带有git环境，不需要配置。

# 二、git的使用

## 1. submodule

### 1.1 添加submodules
git submoduel add ****1.git
git submoduel add ****2.git

### 1.2 clone带有submodule的仓库
git submodule init
git submoduel update

### 1.3 修改submodule
submodule clone之后不在任何分支上，所以修改前需要先切换到要修改的分支上
git checkout master

### 1.4 删除submodule
git没有提供删除submodule的命令，可通过以下几步彻底删除submodule

#### 1.4.1 删除物理文件夹
#### 1.4.2 删除.gitmodules文件中相关内容
#### 1.4.3 删除.git 目录中 config文件相关内容
#### 1.4.3 删除.git 目录中子目录modules中相关目录

git submodule的删除，如果不彻底，在重新添加submodule时很容易出现错误“A git directory for 'rrtcvideo' is found locally with remote”。可按照以上目录逐步进行。


###1.5 用户名配置

解除之前配置的默认用户名
git config --unset user.name
git config --unset user.email

配置新的用户名
git config user.email "xxx"
git config user.email "xxx"



###1.6 git stash 

在多人协同开发的时候，往往会出现push本地修改时，告知先让pull远程仓库代码---这种情况多发生于windows平台的git gui操作.
如果这个时候你直接pull，那很可能你本地的修改就全部丢失了。怎么办呢？git 提供了stash--暂存的功能。步骤如下：
1. git stash
2. git pull 拉取远程仓库代码
3. git stash pop stash{*}
4. git add **
5. git commit -m "xxx"
6. git push 
这样你的本地修改就完美的保留下来了
