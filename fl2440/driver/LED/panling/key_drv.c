/*********************************************************************************
 *      Copyright:  (C) 2017 popy32 http://sfantree.com  
 *                  All rights reserved.
 *       Filename:  key_drv.c
 *    Description:  fl2440 key interrupt platform drivers
 *        Version:  1.0.0(04/26/2017~)
 *         Author:  popy32 panlingood@gmail.com
 ********************************************************************************/

#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>

struct work_struct *work;
struct timer_list buttons_timer;
static unsigned int key_num = 0;
wait_queue_head_t  key_q;
struct resource *res;
struct resource *res_irq;
static unsigned int *key_base;

void work_func(struct work_struct *work)
{  
    //设置超时时间为 100ms
    mod_timer(&buttons_timer, jiffies + (HZ /10)); 	
}

void buttons_timer_function(unsigned long data)  
{
    unsigned int key_val;
    //读取GPFDAT相应位的值判断按键是否按下
    key_val = readw(key_base+1)&0x1; 
    if (key_val == 0)
       //根据按键的不同赋予key_num不同的值
       key_num = 4;
    
    key_val = readw(key_base+1)&0x4;
    if (key_val == 0)
        key_num = 3;
        
    key_val = readw(key_base+1)&0x8;
    if (key_val == 0)
        key_num = 2;

    key_val = readw(key_base+1)&0x10;
    if (key_val == 0)
        key_num = 1;
    wake_up(&key_q); 
} 

//中断处理函数
irqreturn_t int_handle(int irq, void *dev_id)
{
    //向kernel提交工作队列
    schedule_work(work);
    return IRQ_HANDLED; 	
}

int key_open(struct inode *node,struct file *filp)
{
    unsigned int data;
    //GPFCON初始化 
    //设置0 2 3 4相应位为INT(外部中断)
    data = readw(key_base);
    data &= ~0b1111110011;
    data |=  0b1010100010;
    writew(data,key_base);
    
    //GPFDAT初始化 
    //清零0 2 3 4的残余数据
    data = readw(key_base+1);
    data &= ~0b11101;
    data |=  0b11101;
    writew(data,key_base+1);
    
    return 0;	
}

ssize_t key_read(struct file *filp, char __user *buf, size_t size, loff_t *pos)
{ 
    wait_event(key_q,key_num); 
    //将key_num传入用户空间
    copy_to_user(buf, &key_num, 4);    
    key_num = 0;  
    return 4;
}

int key_release(struct inode *node, struct file *filp){
    unsigned int data;
    
    data = readw(key_base);
    data &= ~0b1111110011;
    data |=  0b1010100010;
    writew(data,key_base);
    
    data = readw(key_base+1);
    data &= ~0b11101;
    data |=  0b11101;
    writew(data,key_base+1);
    
    key_num=0;
    return 0;
}
//文件描述符 "重载"系统调用
struct file_operations key_fops = 
{
    .open = key_open,
    .read = key_read,
    .release = key_release,	
};
//创建混杂驱动结构
struct miscdevice key_miscdev = {
    .minor = 200,
    .name = "key",
    .fops = &key_fops,	
};
//平台驱动 设备相互匹配后执行的probe
int key_probe(struct platform_device *pdev)
{
    int ret,size;
    //注册混杂设备
    ret = misc_register(&key_miscdev);    
    if (ret !=0)
        printk("register fail!\n");
    //从硬件资源拿到中断号
    res_irq =  platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	  //驱动注册
    request_irq(res_irq->start  ,int_handle,IRQF_TRIGGER_FALLING,"S2",(void *)1);
    request_irq(res_irq->start+2,int_handle,IRQF_TRIGGER_FALLING,"S3",(void *)2);
    request_irq(res_irq->start+3,int_handle,IRQF_TRIGGER_FALLING,"S4",(void *)3);
    request_irq(res_irq->end    ,int_handle,IRQF_TRIGGER_FALLING,"S5",(void *)4);
    //从硬件资源拿到IO资源，也就是GPFCON的地址
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    size = (res->end - res->start) + 1;
    key_base = ioremap(res->start, size);
    //创建工作队列(尽量减小中断)
    work = kmalloc(sizeof(struct work_struct),GFP_KERNEL);
    INIT_WORK(work, work_func);   
    //初始化内核定时器(按键去抖动)
    init_timer(&buttons_timer);   
    buttons_timer.function  = buttons_timer_function;
    add_timer(&buttons_timer);
    init_waitqueue_head(&key_q);    
    return 0;
}

int key_remove(struct platform_device *dev)
{
        //释放中断资源
        free_irq(res_irq->start  ,(void *)1);
        free_irq(res_irq->start+2,(void *)2);
        free_irq(res_irq->start+3,(void *)3);
        free_irq(res_irq->end    ,(void *)4);
        //释放内存映射
	      iounmap(key_base);
        //释放混杂设备
	      misc_deregister(&key_miscdev);
	      return 0;
}
//定义平台驱动
static struct platform_driver key_driver = {
	.probe		= key_probe,
	.remove		= key_remove,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "my-key",
	},
};

static int button_init()
{
    return platform_driver_register(&key_driver);
}

static void button_exit()
{	   
    platform_driver_unregister(&key_driver);
}

module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("popy32");
MODULE_DESCRIPTION("fl2440 key interrupt platform drivers!\n");
MODULE_VERSION("1.0");
