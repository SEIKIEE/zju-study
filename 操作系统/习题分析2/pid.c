#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
       pid_t pid;
printf("it is first fork\n");
pid = fork();
printf("%d\n",getpid());

if (pid == 0) { /* child process */
printf("in the children process\n");
fork();
printf("%d\n",getpid());
printf("t\n");
}
printf("the last fork\n");
pid = fork();
printf("%d\n",getpid());
}

/*
output:
2460
2459
in the children process
2459
t
the last fork
2459
2462
2461
t
the last fork
2461
2463
*/