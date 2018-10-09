/*
 *    Description:  Check that ioctl can not send more than 2^14B (16384).
 *        Created:  09/10/2018
 *         Author:  Yohan Pipereau
*/

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/string.h>

static long ioc_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	char *msg = (char *) arg;
	printk(KERN_DEBUG "received cmd number %d, size %lu and arg %s\n", cmd,
	       strlen(msg), msg);
	return 0;
}

static int ioc_release(struct inode *inode, struct file *filep)
{
	printk(KERN_DEBUG "ioc module has been closed\n");
	return 0;
}

static int ioc_open(struct inode *inode, struct file *filep)
{
	printk(KERN_DEBUG "ioc module has been opened\n");
	return 0;
}

static struct file_operations ioc_fops = {
	.owner		= THIS_MODULE,
	.open 		= ioc_open,
	.release	= ioc_release,
	.unlocked_ioctl = ioc_ioctl,
};

static struct miscdevice ioc_misc = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "ioc",
	.fops	= &ioc_fops,
};

static int __init ioc_init(void)
{
	int rc;

	printk(KERN_INFO "registering ioc module\n");

	rc = misc_register(&ioc_misc);
	if (rc < 0) {
		printk(KERN_ERR "failed registering\n");
		return rc;
	}

	return 0;
}

static void __exit ioc_exit(void)
{
	printk(KERN_INFO "unregistering ioc module\n");

	misc_deregister(&ioc_misc);
}

module_init(ioc_init);
module_exit(ioc_exit);
