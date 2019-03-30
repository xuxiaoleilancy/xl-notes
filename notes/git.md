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


### 1.5 修改默认用户名

在git commit 之前

git config --unset user.name
git config --unset user.emial

git config user.name "xxx"
git config user.email "xxx"
