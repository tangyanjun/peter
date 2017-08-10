/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  writebuffer.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/05/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/05/2017 04:29:04 AM"
 *                 
 ********************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <mach/gpio.h>
#include <mach/hardware.h>
#include <linux/device.h>
#include <linux/cdev.h>

#define CHRDEV_NAME   "driver_wrbuff"
#define CLASS_NAME    "class_wrbuff"
#define DEVICE_NAME   "driver_wrbuff"

static dev_t      devt_wrbuffer;
static struct cdev* cdev_wrbuffer;
static struct class*  class_wrbuffer;


static int wrbuffer_open(struct inode *inode,struct file *file);
static ssize_t wrbuffer_read(struct file *file,char __user *buf,size_t count,loff_t *offset);
static ssize_t wrbuffer_write(struct file *file,const char __user *buf,size_t count,loff_t *offset);


static struct file_operations fops_wrbuffer={
.owner=THIS_MODULE,
.open=wrbuffer_open,
.read=wrbuffer_read,
.write=wrbuffer_write,
};

static int wrbuffer_open(struct inode *inode,struct file *file) {
printk("open write and buffer device!");
return 0;
}


static ssize_t wrbuffer_read(struct file *file, char __user *buf,size_t count, loff_t *offset){
printk("write buffer device!");
return 0;
}

static ssize_t wrbuffer_write(struct file *file, const char __user *buf,size_t count, loff_t *offset)  {
printk("read buffer device!");
return 0;
}

static int __init wrbuffer_init(void)   {
int ret;

/*1、申请设备号*/
ret = alloc_chrdev_region(&devt_wrbuffer,0,1,CHRDEV_NAME);
if(ret) {
printk("alloc char driver error!\n");
return ret;
}

/*2、注册字符设备*/
cdev_wrbuffer = cdev_alloc();
cdev_init(cdev_wrbuffer,&fops_wrbuffer);
cdev_wrbuffer->owner = THIS_MODULE;
ret=cdev_add(cdev_wrbuffer,devt_wrbuffer,1);
if(ret){
printk("cdev create error!\n");
unregister_chrdev_region(devt_wrbuffer,1);
return ret;
}

/*3、创建设备节点*/
class_wrbuffer=class_create(THIS_MODULE,CLASS_NAME);
device_create(class_wrbuffer,NULL,devt_wrbuffer,NULL,DEVICE_NAME);

printk("wrbuffer driver init is ok!\n");

return 0;
}

static void __exit wrbuffer_exit(void){
/*1、删除设备节点*/
device_destroy(class_wrbuffer,devt_wrbuffer);
class_destroy(class_wrbuffer);

/*2、取消字符设备注册*/
cdev_del(cdev_wrbuffer);

/*3、释放设备号*/
unregister_chrdev_region(devt_wrbuffer,1);
}

late_initcall(wrbuffer_init);
module_exit(wrbuffer_exit);

MODULE_AUTHOR("yxtouch520@yeah.net");
MODULE_DESCRIPTION("allwinner buffer read and write test driver");
MODULE_LICENSE("GPL");

