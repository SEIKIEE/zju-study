# pthread.h

1)     线程控制方面的函数有：pthread_attr_init、pthread_create、pthread_join、pthread_exit

| 函数              | 功能                                                         |
| ----------------- | ------------------------------------------------------------ |
| pthread_attr_init | 初始化一个线程对象的属性                                     |
| pthread_create    | 四个参数：第一个参数是指向线程标识符的指针，type: `pthread_t*`；第二次参数设置线程属性，NULL则使用默认属性；第三个参数是线程运行函数的起始地址，type: `(void*)(*)(void*)`；第四个参数是运行函数的参数，type: `void*` |
| pthread_join      | 用来等待一个线程的结束，线程间同步的操作，共两个参数：第一个参数为线程标识符，即线程id，type: `pthread_t`；第二个参数retval为用户定义的指针，用来存储线程的返回值，type:`void**` |
| pthread_exit      | 显式退出进程                                                 |

2）	互斥锁机制函数：pthread_mutex_init、pthread_mutex_lock、pthread_mutex_unlock、pthread_mutex_destroy

互斥锁保证只有一个进程访问该对象。

锁类型结构ptread_mutex_t

| 函数                  | 功能                                               |
| --------------------- | -------------------------------------------------- |
| pthread_mutex_init    | 在C语言的多线程编程中，实现互斥锁的初始化          |
| pthread_mutex_lock    | 获取互斥锁                                         |
| pthread_mutex_unlock  | 释放互斥锁                                         |
| pthread_mutex_destroy | 注销一个互斥锁，参数为**pthread_mutex_t** **mute*x |

```C++
/* mutex.c */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

/* 全局变量 */
int gnum = 0;
/* 互斥量 */
pthread_mutex_t mutex;

/* 声明线程运行服务程序. */
static void pthread_func_1(void);
static void pthread_func_2(void);

int main (void)
{
 /*线程的标识符*/
  pthread_t pt_1 = 0;
  pthread_t pt_2 = 0;
  int ret = 0;

  /* 互斥初始化. */
  pthread_mutex_init(&mutex, NULL);
  /*分别创建线程1、2*/
  ret = pthread_create(&pt_1,  //线程标识符指针
                       NULL,  //默认属性
                       (void*)pthread_func_1, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror ("pthread_1_create");
  }

  ret = pthread_create(&pt_2, //线程标识符指针
                       NULL,  //默认属性
                       (void *)pthread_func_2, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror ("pthread_2_create");
  }
  /*等待线程1、2的结束*/
  pthread_join(pt_1, NULL);
  pthread_join(pt_2, NULL);

  printf ("main programme exit!/n");
  return 0;
}

/*线程1的服务程序*/
static void pthread_func_1(void)
{
  int i = 0;

  for (i=0; i<3; i++) {
    printf ("This is pthread_1!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁 */
    /* 注意，这里以防线程的抢占，以造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep (1);
    /*临界资源*/
    gnum++;
    printf ("Thread_1 add one to num:%d/n", gnum);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit(NULL);
}

/*线程2的服务程序*/
static void pthread_func_2(void)
{
  int i = 0;

  for (i=0; i<5; i++)  {
    printf ("This is pthread_2!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁. */
    /* 注意，这里以防线程的抢占，以造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep(1);
    /* 临界资源. */
    gnum++;
    printf ("Thread_2 add one to num:%d/n",gnum);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit (NULL);
}
```

3)     条件变量函数：pthread_cond_init、int pthread_cond_signal、int pthread_cond_wait、int pthread_cond_destroy、pthread_cond_broadcast

| 函数                     | 功能                                                         |
| ------------------------ | ------------------------------------------------------------ |
| pthread_cond_init        | 用初始化的条件变量                                           |
| int pthread_cond_signal  | 解除某个条件变量上阻塞线程的阻塞                             |
| int pthread_cond_wait    | 一个线程等待"条件变量的条件成立"而挂起；另一个线程使"条件成立"（给出条件成立信号）。一个条件变量和一个互斥锁结合起来使用。 |
| int pthread_cond_destroy |                                                              |
| pthread_cond_broadcast   |                                                              |

# semaphore.h

1)     信号量线程控制函数：sem_init、sem_wait、sem_post、sem_getvalue、sem_destory

用户态进程对 sem 信号量可以有以下两种操作：

- 等待信号量
  当信号量值为 0 时，程序等待；当信号量值大于 0 时，信号量减 1，程序继续运行。
- 发送信号量
  将信号量值加 1

| 函数         | 功能                                                         |
| ------------ | ------------------------------------------------------------ |
| sem_init     | (sem_t *sem, int pshared, unsigned int value) 创建信号量     |
| sem_wait     | sem_wait 是一个阻塞的函数，测试所指定信号量的值，它的操作是原子的。若 sem value > 0，则该信号量值减去 1 并立即返回。若sem value = 0，则阻塞直到 sem value > 0，此时立即减去 1，然后返回。 |
| sem_pos      | 把指定的信号量 sem 的值加 1，唤醒正在等待该信号量的任意线程。int sem_post(sem_t *sem); |
| sem_getvalue | int sem_getvalue(sem_t *sem, int *sval);获取信号量 sem 的当前值，把该值保存在 sval，若有 1 个或者多个线程正在调用 sem_wait 阻塞在该信号量上，该函数返回阻塞在该信号量上进程或线程个数。 |
| sem_destory  | 清理用完的信号量                                             |





死锁检测

锁住自己的这个方向

然后等待死锁和cross

访问北边的信号量的锁





将车加入相应方向的等待队列。

如果车辆不是等待队列的最前方的车辆，那么就等待发出next的信号量。	或者现在路上正在有车开。

while(resouce == FALSE)

{

Pthread_cond_wait(&cond, &mutex);

}

打印crossing的信息

**1** 方向锁锁住

等本方向正在过马路的车pthread cond wait

设置本方向车要行驶

看看死锁

if 右边有车要过马路

「设置本方向车等待， 然后判断一下有没有死锁。死锁的话，就锁住死锁的锁，释放死锁的信号量。解锁死锁的锁。」

然后取消我们正在等马路的条件。iswait

锁住cross

开始开车 car leaving

sleep一下

解锁cross

锁住右边的车

放右边的车开走信号

解锁右边的车

**2** 锁住本方向等待队列

本车移除等待队列

释放信号给本方向的下一辆车

取消本车正在过马路的信号

**2** 解锁本车等待队列

**1** 解锁本方向信号





wait到一个互斥锁之后，会释放掉一个那个互斥锁，然后其他线程可以得到那个互斥锁。

第一辆车就不需要wait，右边的车也要wait。

可以参考读者写者。用一个计数器。+1 -1

























