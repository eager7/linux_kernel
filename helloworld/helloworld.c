#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Changtao.Pan");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("hello world");

static int how_many = 0;
static char *whom = "pct";
module_param(how_many, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static int hello_init(void)
{
 	int i = 0;
	printk(KERN_ALERT "hello init\n");
	for(i = 0; i < how_many; i++){
		printk(KERN_DEBUG "hello %s\n", whom);
	}
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
