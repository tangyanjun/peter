/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/29/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "03/29/2017 02:55:07 PM"
 *                 
 ********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<asm/ioctl.h>
#ifndef __KERNEL__
#include <sys/ioctl.h>
#endif

#define PLATDRV_MAGIC      0X60
#define LED_ON              _IO (PLATDRV_MAGIC, 0x19)
#define LED_OFF            _IO (PLATDRV_MAGIC, 0x18)
#define LEN_LED             4
#define LED_BUF            128

int main(int argc,char **argv)
{
    int fd[LEN_LED];
    char dev_name[LED_BUF];
    int i;
        
        for(i=0;i<LEN_LED;i++)
        {
            snprintf(dev_name,sizeof(dev_name),"/dev/led%d",i);
            fd[i]=open(dev_name,O_RDWR,0755);
                if(fd[i]<0)
                  {
                    printf("open failure:%s",strerror(errno));
                  }
        }

                while(1)
           {
              for(i=0;i<LEN_LED;i++)
                  {
                  //   ioctl(fd[i],LED_OFF);
                   //  sleep(0.5);
                     ioctl(fd[i],LED_ON);
                     sleep(1);
                     ioctl(fd[i],LED_OFF);
                     sleep(0.5);
                  }


           }    

        for(i=0;i<LEN_LED;i++)
       {
             close(fd[i]);
             return 0;
       }

#if 0
   if(argc>1)
{
    printf("error:Too many parameter");
}
  else
{
    while(1)
        {
            for(i=0;i<4;i++)
                {
                    switch(i)
                        {
                            case 0:
                                fd[i]=open("/dev/led0",O_RDWR,755);
                                ioctl(fd[i],LED_ON);
                                sleep(1);
                                ioctl(fd[i],LED_OFF);
                                close(fd[i]);

                            break;
                            case 1:
                                fd[i]=open("/dev/led1",O_RDWR,755);
                                ioctl(fd[i],LED_ON);
                                sleep(1);
                                ioctl(fd[i],LED_OFF);
                                close(fd[i]);
                                break;
                       case 2:
                       fd[i]=open("/dev/led2",O_RDWR,755);
                       ioctl(fd[i],LED_ON);
                       sleep(1);
                       ioctl(fd[i],LED_OFF);
                       close(fd[i]);
                       break;
                       case 3:
                       fd[i]=open("/dev/led3",O_RDWR,755);
                       ioctl(fd[i],LED_ON);
                       sleep(1);
                       ioctl(fd[i],LED_OFF);
                       close(fd[i]);
                       break;
                       
                       }
                       }
                       }
}
#endif
  return 0;
  
  
  }
