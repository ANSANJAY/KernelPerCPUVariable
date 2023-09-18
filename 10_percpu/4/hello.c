#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

DEFINE_PER_CPU(int, counter);

static int __init test_hello_init(void)
{
	int i = 0;

	for_each_online_cpu(i) {
		int value = per_cpu(counter, i);
		pr_info("Value of counter is %d at Processor:%d\n", value, i);
	}

	get_cpu_var(counter) = 10;
	pr_info("Printing counter value of all processor after updating current processor:%d\n",
			smp_processor_id());
	put_cpu_var(counter);

	for_each_online_cpu(i) {
		int value = per_cpu(counter, i);
		pr_info("Value of counter is %d at Processor:%d\n", value, i);
        }

    return -1;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
