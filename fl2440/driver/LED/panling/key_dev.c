/*********************************************************************************
 *      Copyright:  (C) 2017 popy32 http://sfantree.com  
 *                  All rights reserved.
 *       Filename:  key_dev.c
 *    Description:  fl2440 key interrupt platform devices                 
 *        Version:  1.0.0(04/26/2017~)
 *         Author:  popy32 panlingood@gmail.com
 ********************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#define GPFCON 0x56000050
static struct resource key_resource[] = {
  //定义按键相关的IO资源
	[0] = {
		.start = GPFCON,
		.end   = GPFCON + 8,
		.flags = IORESOURCE_MEM,
	},
  //定义按键相关的中断资源
  //EINT0 EINT2 EINT3 EINT4
	[1] = {
		.start = IRQ_EINT0,
		.end   = IRQ_EINT4,
		.flags = IORESOURCE_IRQ,
	},
};

//注册平台设备
struct platform_device key_device = {
	.name		  = "my-key",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(key_resource),
	.resource	  = key_resource,
};
//加载模块的入口函数
static int button_init()
{
    platform_device_register(&key_device);
    return 0;
}
//卸载模块的退出函数
static void button_exit()
{	   
    platform_device_unregister(&key_device);
}

module_init(button_init);
module_exit(button_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("popy32");
MODULE_DESCRIPTION("fl2440 key interrupt platform devices!\n");
MODULE_VERSION("1.0");
