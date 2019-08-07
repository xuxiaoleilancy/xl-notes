<!-- GFM-TOC -->
[TOC]
<!-- GFM-TOC -->
[TOC]

# top

## 查看某个进程内部线程占用情况

top -Hp pid

# watch 

## 重复执行某一个命令
watch -n 0 "cat /proc/cpuinfo | grep -i mhz"


# ps
## ps -To 'pid,lwp,psr,cmd' -p pid
## ps -mp pid | wc -l

# intel_gpu_tools
## 实时查看gpu使用情况
intel_gpu_top

## intel_gpu_abrt

## 总结命令行的CPU和GPU等使用情况
intel_gpu_time

# 显卡信息查看

## vga显卡信息查看
lspci | grep -i vga 

```
suirui@suirui:~$ lspci | grep -i vga
00:02.0 VGA compatible controller: Intel Corporation Haswell-ULT Integrated Graphics Controller (rev 09)
```

## 查看详细的信息
lspci -v -s 02:00.0

```
suirui@suirui:~$ lspci -v -s 02:00.0
02:00.0 Network controller: Intel Corporation Centrino Wireless-N 2230 (rev c4)
    Subsystem: Intel Corporation Centrino Wireless-N 2230 BGN
    Flags: bus master, fast devsel, latency 0, IRQ 62
    Memory at f7c00000 (64-bit, non-prefetchable) [size=8K]
    Capabilities: <access denied>
    Kernel driver in use: iwlwifi
```


# 网络相关

## [netstat命令详解](https://www.cnblogs.com/ftl1012/p/netstat.html)

使用示例
```
#查看某个端口的链接
netstat -anlp | grep 9911 

#查看某个ip的链接
netstat -anlp | grep 10.10.7.41 
```

