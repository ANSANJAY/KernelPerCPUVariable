#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>

#define COMPANY_NAME	"linux"

MODULE_LICENSE("GPL");
static struct proc_dir_entry  *file_pde; //pde -proc directory entry
unsigned int percpu_data[NR_CPUS];


static int cpu_show(struct seq_file *m, void *v)
{
	int i;
	for (i = 0 ; i < num_online_cpus(); i++)
		seq_printf(m, "Processor %d:%u\n", i, percpu_data[i]);
        return 0;
}



static int my_open(struct inode *inode, struct file *file)
{
	return single_open(file, cpu_show, NULL);

}

static ssize_t proc_write_cpu(struct file * file, const char *buffer, size_t count, loff_t * data)
{
	unsigned char buf[10];
	unsigned int user_val;
	int cpu;

	pr_info("%s\n", __func__);
	if (copy_from_user(buf, buffer, count))
	{
		return -EFAULT;
	}
	else
	{
		buf[count] = '\0';
		user_val = simple_strtoul(buf, NULL, 10);

		cpu = get_cpu(); /* get current processor and disable kernel preemption */
		percpu_data[cpu] = user_val;
		printk("percpu_data on cpu=%d is %u\n", cpu, percpu_data[cpu]);
		put_cpu(); /* enable kernel preemption */

	}
	return count;

}

static struct file_operations cpu_ops = {
  .owner = THIS_MODULE,
  .open  = my_open,
  .read = seq_read,
  .llseek= seq_lseek,
  .write = proc_write_cpu,
};


static int hello_init(void)
{
	pr_info("%s: In init\n", __func__);

	file_pde = proc_create("percpu",0644, NULL, &cpu_ops);
	if (!file_pde) {
		pr_err("%s: error creating proc file\n", __func__);
		return -1;
	}

	return 0;
}

static void hello_exit(void)
{
	pr_info("%s: In exit\n", __func__);
	remove_proc_entry("percpu", NULL);
}

module_init(hello_init);
module_exit(hello_exit);
