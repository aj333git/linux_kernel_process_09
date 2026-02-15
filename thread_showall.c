#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/version.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Show all threads");

static int __init thread_showall_init(void)
{
    struct task_struct *p, *t;

    pr_info("TGID   PID   TYPE   NAME\n");
    pr_info("---------------------------\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(6,6,0)
    do_each_thread(p, t) {
#else
    for_each_process_thread(p, t) {
#endif
        get_task_struct(t);

        if (t->mm == NULL)
            pr_info("%5d %5d  KTHRD [%s]\n",
                    p->tgid, t->pid, t->comm);
        else
            pr_info("%5d %5d  UTHRD  %s\n",
                    p->tgid, t->pid, t->comm);

        put_task_struct(t);
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,6,0)
    } while_each_thread(p, t);
#else
    }
#endif

    return 0;
}

static void __exit thread_showall_exit(void)
{
    pr_info("thread_showall unloaded\n");
}

module_init(thread_showall_init);
module_exit(thread_showall_exit);
