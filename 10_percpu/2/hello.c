#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

static DEFINE_PER_CPU (long, percpuvar) = 5;

static int __init test_hello_init(void)
{
    int cpu;
    pr_info("percpuvar=%ld\n", get_cpu_var(percpuvar)++);
    cpu = smp_processor_id ();
    printk("current cpu = %d\n",cpu);
    put_cpu_var(percpuvar);
    pr_info("percpuvar=%ld\n", get_cpu_var(percpuvar));
    cpu = smp_processor_id ();
    printk("current cpu = %d\n",cpu);
    put_cpu_var(percpuvar);

    return -1;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
