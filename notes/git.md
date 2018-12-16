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

# git的使用

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
