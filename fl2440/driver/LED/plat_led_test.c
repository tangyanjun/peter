/*********************************************************************************
 *      Copyright:  (C) 2017 TangBin<tangbinmvp@gmail.com>
 *                  All rights reserved.
 *
 *       Filename:  plat_led_test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/30/2017)
 *         Author:  TangBin <tangbinmvp@gmail.com>
 *      ChangeLog:  1, Release initial version on "03/30/2017 06:10:20 PM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DEVNAME_LEN    10

#define PLATDRV_MAGIC             0x60
#define LED_OFF                   _IO (PLATDRV_MAGIC, 0x18)
#define LED_ON                    _IO (PLATDRV_MAGIC, 0x19)
#define LED_BLINK               _IO (PLATDRV_MAGIC, 0x1A)

int main(int argc, char **argv)
{
    int  ctl_number;
    int  led_number;
    int  fd;
    char dev_name[DEVNAME_LEN]={0,0,0,0};

    if(argc>2)
    {
        snprintf(dev_name,sizeof(dev_name),"/dev/led");
        fd = open(dev_name, O_RDWR, 0755);

        ctl_number = atoi(argv[1]);
        led_number = atoi(argv[2]);

        if(0  == ctl_number)
            ioctl(fd,LED_ON,led_number);   //ioctl函数将字符串转换成int整数
        else if(1 == ctl_number)
            ioctl(fd,LED_OFF,led_number);
        else if(2 == ctl_number)
            ioctl(fd,LED_BLINK,led_number);
        else
        {
            printf("error!\n");
            printf("Please enter the correct parameters.\n");
            printf("correct format: %s 0(on)|1(off)|2(blink) 0|1|2|3\n",argv[0]);
        }
      }
}












