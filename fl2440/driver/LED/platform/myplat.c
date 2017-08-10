/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  myplat.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/05/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/05/2017 02:40:02 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include "plat_ioctl.h"   //for ioctl
/* ******open******/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>   //for strcmp
#include <unistd.h>   //for sleep

int main(int argc, char **argv)
{
    
    int fd = open("/dev/led", O_RDWR);

    if (argc > 1)
    {
       
        if (!strcmp (argv[1], "0" ))
        {
          while(1)
          {
          ioctl(fd, LED_ON, 0);
          printf("turn on the LED0\n");
          sleep(1);
          ioctl(fd, LED_OFF, 0);
          printf("turn off the LED0\n");
          sleep(2);
          ioctl(fd,LED_BLINK,0);
          printf("blinking the LED0\n");
          sleep(3);
          }
        }

        else if (!strcmp (argv[1], "1" ))
        {
          while(1)
          {
          ioctl(fd, LED_ON, 1);
          printf("turn on the LED1\n");
          sleep(1);
          ioctl(fd, LED_OFF, 1);
          printf("turn off the LED1\n");
          sleep(2);
          ioctl(fd,LED_BLINK,1);
          printf("blinking the LED1\n");
          sleep(3);
        
          }
        }

        else if (!strcmp (argv[1], "2" ))
        {
          while(1)
          {
          ioctl(fd, LED_ON, 2);
          printf("turn on the LED2\n");
          sleep(1);
          ioctl(fd, LED_OFF, 2);
          printf("turn off the LED2\n");
          sleep(2);
          ioctl(fd,LED_BLINK,2);
          printf("nlinking the LED2\n");
          sleep(3);
          }
        }

        else if (!strcmp (argv[1], "3" ))
        {
          while(1)
          {
          ioctl(fd, LED_ON, 3);
          printf("turn on the LED3\n");
          sleep(1);
          ioctl(fd, LED_OFF, 3);
          printf("turn off the LED3\n");
          sleep(2);
          ioctl(fd,LED_BLINK,3);
          printf("blinking the LED3\n");
          sleep(3);
          }
        }
    }

    else 
    {
        printf("please input the status, 0, 1, 2 or 3");
    }

    close(fd);

    return 0;

}

