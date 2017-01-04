/****************************************************************************
 *
 * MODULE:             reversion.c
 *
 * COMPONENT:          linux kernel interface
 *
 * REVISION:           $Revision:  1.0$
 *
 * DATED:              $Date: 2016-12-06 15:13:17 +0100 (Fri, 12 Dec 2016 $
 *
 * AUTHOR:             PCT
 *
 ****************************************************************************
 *
 * Copyright panchangtao@gmail.com 2016. All rights reserved
 *
 ***************************************************************************/
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "reversion.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Changtao.Pan");
MODULE_DESCRIPTION("This Module used to reversion a str");
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
ssize_t write_reversion(struct file *filp, const char __user *buf, size_t count, loff_t *ppos);
ssize_t read_reversion(struct file *filp, char __user *buf, size_t count, loff_t *ppos);
static int open_reversion(struct inode *inode, struct file *filp);
long ioctl_reversion(struct file *filp, unsigned int cmd, unsigned long arg);
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
int major_reversion = REVERSION_MAJOR;
int minor_reversion = REVERSION_MINOR;
int number_reversion = REVERSION_NR_DEVS;
module_param(major_reversion, int, S_IRUGO);	//可以通insmod传递值到驱动中
module_param(minor_reversion, int, S_IRUGO);	
module_param(number_reversion, int, S_IRUGO);	

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
static struct file_operations file_ops = {
	.owner 				= THIS_MODULE,
	.open 				= open_reversion,
	.write 				= write_reversion,
	.read 				= read_reversion,
	.unlocked_ioctl 	= ioctl_reversion
};
struct cdev *pcdev_reversion;
/****************************************************************************/
/***        Local    Functions                                            ***/
/****************************************************************************/
static int __init reversion_init(void)
{
	int ret = 0;
	dev_t dev;
	
    print("init reversion module");
	if(major_reversion){
		dev = MKDEV(major_reversion, minor_reversion);
		ret = register_chrdev_region(dev, number_reversion, REVERSION_NAME);
	} else {
		ret = alloc_chrdev_region(&dev, minor_reversion, number_reversion, REVERSION_NAME);
		major_reversion = MAJOR(dev);
	}
	if(ret < 0){
		printk(KERN_WARNING "reversion:can't get major %d\n", major_reversion);
		return ret;
	}
	pcdev_reversion = cdev_alloc();	//inode 结构的一个结构体，在内核内部表示设备
	pcdev_reversion->owner = THIS_MODULE;
	pcdev_reversion->ops = &file_ops;
	
    cdev_add(pcdev_reversion, dev, number_reversion);
	
	return 0;
}

static void reversion_exit(void)
{
	print("exit reversion module");
	cdev_del(pcdev_reversion);
	unregister_chrdev_region(MKDEV(major_reversion, minor_reversion), number_reversion);//unregion device
}

ssize_t write_reversion(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    char auBuf[128] = {0};
    if(copy_from_user(auBuf, buf, count)){
        printk(KERN_ERR "reversion:can't get date form user space\n");
        return EFAULT;
    }
    printk(KERN_DEBUG "reversion:get data form user space:%s\n", auBuf);
	return 0;
}
ssize_t read_reversion(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
    if(copy_to_user(buf, "kernel", sizeof("kernel"))){
        printk(KERN_ERR "reversion:can't set date to user space\n");
        return EFAULT;
    }
	return 0;
}
static int open_reversion(struct inode *inode, struct file *filp)
{
	return 0;
}
long ioctl_reversion(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}
module_init(reversion_init);
module_exit(reversion_exit);
