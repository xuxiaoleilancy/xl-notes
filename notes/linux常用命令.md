<!-- GFM-TOC -->
* [top](#top)
    * [top -Hp](#top -Hp)
* [watch](#watch)
    * [watch -n](#watch -n)
* [ps](#ps)
    * [ps -To](#ps -To)
    * [ps -mp](#开机检测程序)
* [intel_gpu_tools](#intel_gpu_tools)
    * [intel_gpu_top](#intel_gpu_top)
<!-- GFM-TOC -->

# top

## top -Hp pid

# watch 

## watch -n 0 "cat /proc/cpuinfo | grep -i mhz"


# ps
## ps -To 'pid,lwp,psr,cmd' -p pid
## ps -mp pid | wc -l

# intel_gpu_tools
## intel_gpu_top