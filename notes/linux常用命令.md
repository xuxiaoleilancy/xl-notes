<!-- GFM-TOC -->
* [top](#top)
    * [查看某个进程内部线程占用情况](#查看某个进程内部线程占用情况)
* [watch](#watch)
    * [重复执行某一个命令](#重复执行某一个命令)
* [ps](#ps)
    * [ps -To](#ps -To)
    * [ps -mp](#开机检测程序)
* [intel_gpu_tools](#intel_gpu_tools)
    * [实时查看gpu使用情况](#实时查看gpu使用情况)
    * [intel_gpu_abrt](#intel_gpu_abrt)
    * [总结命令行的CPU和GPU等使用情况](#总结命令行的CPU和GPU等使用情况)
<!-- GFM-TOC -->

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