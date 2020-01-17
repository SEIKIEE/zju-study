#include <linux/unistd.h> 
#include <sys/syscall.h> 
#include <stdio.h> 
#define __NR_mysyscall 333 
int main()
{
    syscall(__NR_mysyscall);
}