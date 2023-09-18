#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

static int *dynamic_counter;

static int __init test_hello_init(void)
{
	int cpu = get_cpu();
	int i;
	dynamic_counter = alloc_percpu(int);
	pr_info("cpu:%d\n", cpu);
	*per_cpu_ptr(dynamic_counter, cpu) = 1000;
	put_cpu();
	for (i = 0; i < num_online_cpus(); i++)
		pr_info("cpu:%d\tcounter:%d\n",i, *per_cpu_ptr(dynamic_counter, i));
	free_percpu(dynamic_counter);
	return -1;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
