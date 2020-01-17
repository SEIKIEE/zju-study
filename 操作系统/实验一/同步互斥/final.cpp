#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 100
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//一辆汽车
struct carNode
{
    int id;
    int direction;
};
//一个汽车队列
struct carQueue
{
    int size; //队列中车总数
    int head; //第一辆车
    int tail; //最后一辆车
    char direction[6];
    int cars[MAX];
};
pthread_cond_t queue[4];         //各个方向车辆队列的条件变量
pthread_mutex_t lock[4];         //各个方向条件变量互斥锁
pthread_cond_t next[4];          //各个方向设置下次通行车辆的条件变量
pthread_mutex_t cross;           //路口通行互斥量
pthread_mutex_t Wait[4];         //设置各个方向上等待队列的互斥量
pthread_cond_t deadlockCond;     //死锁条件变量
pthread_mutex_t deadlockLock;    //检测死锁互斥量
struct carNode car[MAX];         //车量队列
struct carQueue waitCarQueue[4]; //各个方向等待的车的队列
int isWait[4] = {0};             //各个方向上是否有车等待
int isCar[4] = {0};              //各个方向上的路口是否有车正在通行

void *checkDeadLock(void *);
void *carCross(void *car);

int main(int argc, char const *argv[])
{
    //初始化条件变量和互斥量
    for (int i = 0; i < 4; i++)
    {
        pthread_cond_init(&queue[i], NULL);
        pthread_cond_init(&next[i], NULL);
        pthread_mutex_init(&lock[i], NULL);
    }
    pthread_cond_init(&deadlockCond, NULL);
    pthread_mutex_init(&deadlockLock, NULL);

    //初始化等待队列
    for (int i = 0; i < 4; i++)
    {
        waitCarQueue[i].head = 0;
        waitCarQueue[i].tail = 0;
        waitCarQueue[i].size = 0;
    }

    //创建死锁线程
    pthread_t deadlock;
    pthread_create(&deadlock, NULL, checkDeadLock, NULL);

    //创建和总车数相等的线程
    pthread_t carThread[strlen(argv[1])];
    //标记好四个车队的方向
    strcpy(waitCarQueue[NORTH].direction, "North");
    strcpy(waitCarQueue[EAST].direction, "East");
    strcpy(waitCarQueue[SOUTH].direction, "South");
    strcpy(waitCarQueue[WEST].direction, "West");
    //获得四个方向的车队
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        switch (argv[1][i])
        {
        case 'n':
            //北方
            car[i].id = i + 1;
            car[i].direction = 0;
            //加入北方车队
            waitCarQueue[NORTH].size++;
            waitCarQueue[NORTH].cars[waitCarQueue[NORTH].tail++] = i + 1;
            break;
        case 'e':
            //东方
            car[i].id = i + 1;
            car[i].direction = 1;
            //加入东方车队
            waitCarQueue[EAST].size++;
            waitCarQueue[EAST].cars[waitCarQueue[EAST].tail++] = i + 1;
            break;
        case 's':
            //南方
            car[i].id = i + 1;
            car[i].direction = 2;
            //加入南方车队
            waitCarQueue[SOUTH].size++;
            waitCarQueue[SOUTH].cars[waitCarQueue[SOUTH].tail++] = i + 1;
            break;
        case 'w':
            //西方
            car[i].id = i + 1;
            car[i].direction = 3;
            //加入西方车队
            waitCarQueue[WEST].size++;
            waitCarQueue[WEST].cars[waitCarQueue[WEST].tail++] = i + 1;
            break;
        default:
            break;
        }
    }

    //创建线程
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        pthread_create(&carThread[i], NULL, carCross, (void *)&car[i]);
    }
    //等待线程停止
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        pthread_join(carThread[i], NULL);
    }

    //释放资源
    pthread_mutex_destroy(&cross);
    pthread_mutex_destroy(&deadlockLock);
    pthread_cond_destroy(&deadlockCond);
    for (int i = 0; i < 4; i++)
    {
        pthread_mutex_destroy(&lock[i]);
        pthread_cond_destroy(&queue[i]);
        pthread_cond_destroy(&next[i]);
        pthread_mutex_destroy(&Wait[i]);
    }
}

void *carCross(void *car)
{
    struct carNode *Car = (struct carNode *)car;

    //如果这辆车不是等待列表中的第一辆车
    while (waitCarQueue[Car->direction].cars[waitCarQueue[Car->direction].head] != Car->id)
    {
        ;
    }
    //开到路口
    printf("car %d from %s arrives at crossing\n", Car->id, waitCarQueue[Car->direction].direction);

    //开启路口锁
    pthread_mutex_lock(&lock[Car->direction]);
    //这个方向上有车在开，等待信号量
    while (isCar[Car->direction] == 1)
    {
        pthread_cond_wait(&queue[Car->direction], &lock[Car->direction]);
    }
    //标记本车要开
    isCar[Car->direction] = 1;
    //标记本车等待
    isWait[Car->direction] = 1;
    //如果右边有车，等待信号量
    if (waitCarQueue[(Car->direction + 1) % 4].size != 0)
    {
        pthread_cond_wait(&next[Car->direction], &lock[Car->direction]);
    }
    //当前没有车在路口等待，本车可以开了
    isWait[Car->direction] = 0;
    pthread_mutex_lock(&cross);
    printf("car %d from %s leaving crossing\n", Car->id, waitCarQueue[Car->direction].direction);
    pthread_mutex_unlock(&cross);
    //释放左边车辆通行信号
    pthread_cond_signal(&next[(Car->direction + 3) % 4]);
    pthread_mutex_unlock(&lock[Car->direction]);

    //将开走的车移除等待队列
    pthread_mutex_lock(&Wait[Car->direction]);
    waitCarQueue[Car->direction].head++;
    waitCarQueue[Car->direction].size--;
    isCar[Car->direction] = 0;
    //释放本车队下一辆车可以行驶的信号量
    pthread_cond_signal(&queue[Car->direction]);
    pthread_mutex_unlock(&Wait[Car->direction]);
    pthread_exit(NULL);
}

void *checkDeadLock(void *)
{
    while (1)
    {
        pthread_mutex_lock(&cross);
        pthread_cond_wait(&deadlockCond, &cross);
        pthread_mutex_lock(&lock[NORTH]);
        printf("DEADLOCK: car jam detected, signalling North to go\n");
        pthread_cond_signal(&queue[NORTH]);
        pthread_mutex_unlock(&lock[NORTH]);
        pthread_mutex_unlock(&cross);
    }
}