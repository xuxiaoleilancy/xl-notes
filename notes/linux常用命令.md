# 一、常用命令

## top

### top -Hp pid


## watch 

### watch -n 0 "cat /proc/cpuinfo | grep -i mhz"


## ps
### ps -To 'pid,lwp,psr,cmd' -p pid
### ps -mp pid | wc -l

## intel_gpu_top