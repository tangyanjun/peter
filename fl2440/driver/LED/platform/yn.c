/*********************************************************************************
 *      Copyright:  (C) 2017 qicheng
 *                  All rights reserved.
 *
 *       Filename:  plat_led_test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/04/2017)
 *         Author:  yangni <497049229@qq.com>
 *      ChangeLog:  1, Release initial version on "04/04/2017 10:23:58 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include "plat_ioctl.h"   //for ioctl
/*******open******/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>   //for strcmp
#include <unistd.h>   //for sleep

int main(int argc,char **argv)
{
    int fd,i;
    fd=open("/dev/led",O_RDWR);

    if (argc > 1)
    {
        
        
        if (!strcmp (argv[1],"LED_ON" ))
        {
            printf("turn on all leds!\n");
            for(i=0;i<=3;i++)
                ioctl(fd,LED_ON,i);
        }
        
        else if(!strcmp (argv[1],"LED_OFF"))
        {
            printf("turn off all leds!\n");
            for(i=0;i<=3;i++)
                 ioctl(fd,LED_OFF,i);
        }
        
        else if (!strcmp (argv[1],"LED_BLINK"))
        {
            printf("leds begin to blink...\n");
            while(1)
            {
                for(i=0;i<=3;i++)
                {
                    ioctl(fd,LED_BLINK,i);
                    sleep(1.5);
                    ioctl(fd,LED_OFF,i);
                }
            }
        }
    }
    else
    {
        printf("please input the status,LED_ON,LED_OFF or LED_BLINK");
    }

close(fd);
return 0;
}
