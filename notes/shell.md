<!-- GFM-TOC -->
[TOC]
<!-- GFM-TOC -->
[TOC]


# 网站

[菜鸟教程-linux shell](https://www.runoob.com/linux/linux-shell.html)

# 条件测试
Shell 里面的中括号（包括单中括号与双中括号）可用于一些条件的测试：

```
//算术比较, 比如一个变量是否为0, 
[ $var -eq 0 ]
//文件属性测试
//一个文件是否存在，
[ -e $var ] 
//是否是目录
[ -d $var ]
//字符串比较
//两个字符串是否相同
[[ $var1 = $var2 ]]

```

[] 常常可以使用 test 命令来代替，具体可参看：Shell 中的中括号用法总结。
