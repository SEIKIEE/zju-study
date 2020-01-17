#include <linux/module.h>			//modules KERN_INFO
#include <linux/sched/signal.h>		//struct task_struct

/*initilize the module*/
int init_module(void)
{
    printk("Process log:\n");	//mark to start count

    int totalProcess = 0;	//the total number of process
    /*the number of different state process*/
    int running = 0, interruptible = 0, uninterruptible = 0, zombie = 0, stopped = 0, traced = 0, dead = 0;

    struct task_struct *process;	//pointer pointing to process
    for(process=&init_task;(process=next_task(process))!=&init_task;)	//iterate over the process list
    {
    	/*print the basic data*/
        printk(KERN_INFO"Name: %s, pid: %d, state: %d, parent id: %d, parent name: %s",process->comm,process->pid,process->state,process->parent->pid,process->parent->comm);
        if(process->exit_state == 0)	//the process is not dead yet	
        {
            switch(process->state)	//count the number of process in different states
            {
                case TASK_RUNNING:
                    running++;
                    break;
                case TASK_INTERRUPTIBLE:
                    interruptible++;
                    break;
                case TASK_UNINTERRUPTIBLE:
                    uninterruptible++;
                    break;
                case TASK_STOPPED:
                    stopped++;
                    break;
                case TASK_TRACED:
                	traced++;
                	break;
                default:
                    break;
            }
        }
        else	//the process is dead or zombie
        {
        	switch(process->exit_state)
        	{
        		case EXIT_ZOMBIE:
        			zombie++;
        			break;
        		case EXIT_DEAD:
        			dead++;
        			break;
        		default:
        			break;
        	}
        }
        totalProcess++;
    }

    /*print the count result*/
    printk(KERN_INFO"The total number of process is %d\n", totalProcess);
    printk(KERN_INFO"The number of running process is %d\n", running);
    printk(KERN_INFO"The number of interruptible process is %d\n", interruptible);
    printk(KERN_INFO"The number of uninterruptible process is %d\n", uninterruptible);
    printk(KERN_INFO"The number pf zombie process is %d\n", zombie);
    printk(KERN_INFO"The number of stopped process id %d\n", stopped);
    printk(KERN_INFO"The number of traced process id %d\n", traced);
    printk(KERN_INFO"The number of dead process id %d\n", dead);

    return 0;
}

/*clean uo the module*/
void cleanup_module(void)
{
    printk("Good-bye!\n");
}

MODULE_LICENSE("GPL");

