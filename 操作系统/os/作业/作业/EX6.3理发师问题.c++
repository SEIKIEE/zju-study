semaphore   mutex = 1;//用于保护椅子变量
semaphore   customers = 0;
semaphore   barbers = 0;
int EmptyChair= N;  //所有椅子的数量

理发师：
void Barber()
{
	while(true){
		wait(customers)；//无顾客理发时，理发师睡觉
        wait(mutex);   //用于互斥
        EmptyChair ++;     //空椅子数量增加一个
		signal(barbers);  //理发师理发
        signal（mutex）; ﻿﻿//释放椅子保护
        babering;   //理发操作
	}
}


顾客:
﻿void Customer ()
{
	wait(mutex);  
    if(EmptyChair > 0){
		﻿//店内仍有空椅子
		EmptyChair --;
		signal(customers);//叫醒理发师
        signal(mutex);//释放椅子互斥量
        wait(barber);//等待正在忙的理发师
        PrepareForBarber;
    }﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿

    else
		//店内无空椅子
		signal(mutex)﻿;  //释放椅子互斥量
		//顾客离开理发店
}﻿﻿﻿


﻿﻿﻿﻿﻿﻿﻿

﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿﻿

        

 


