/*********************************************************************************
 *      Copyright:  (C) 2017 Li Wanneng<liwjng@gmail.com>
 *                  All rights reserved.
 *
 *       Filename:  app_turnled.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/10/2017)
 *         Author:  Li Wanneng <liwjng@gmail.com>
 *      ChangeLog:  1, Release initial version on "04/10/2017 01:26:36 AM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08
#define PLATDRV_MAGIC   0x60
#define OFF _IO (PLATDRV_MAGIC,0x18)
#define ON _IO (PLATDRV_MAGIC,0X19)

/********************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 ********************************************************************************/
int main (int argc, char **argv)
{
    int button_fd;
    int led_fd;
    int ret_button;
    int current_button;
    
    button_fd = open("/dev/button",0);
    if(button_fd<0)
    {
        printf("open button failed.\n");
        exit(1);
    }

   while(1)
    {
        ret_button = read(button_fd,&current_button,sizeof(4));
        if(ret_button!=sizeof(current_button))
        {
            printf("Read() button failed.\n");
        }

        else 
            
        {
            switch(current_button)
            {
                case KEY1:
                          printf("Turn led0 ON.\n");
                         
                          if(led_fd>=0)
                          {
                              ioctl(led_fd,OFF);
                              close(led_fd);
                          }

                          led_fd = open("/dev/led0",O_RDWR,755);
                          break;
                case KEY2:
                          printf("Turn led1 ON\n");
                    
                          if(led_fd>=0)
                          {        
                              ioctl(led_fd,OFF);
                              close(led_fd);
                          }   
                         
                          led_fd = open("/dev/led1",O_RDWR,755);
                          break;
                case KEY3:
                          printf("Turn led2 ON.\n");
                          
                          if(led_fd>=0)
                          {
                              ioctl(led_fd,OFF);
                             close(led_fd);
                          }
                          
                          led_fd = open("/dev/led2",O_RDWR,755);
                          break;
                case KEY4:
                          printf("Turn led3 ON.\n");
                     
                          if(led_fd>=0)
                          {
                              ioctl(led_fd,OFF);
                              close(led_fd);
                          }
                          
                          led_fd = open("/dev/led3",O_RDWR,755);
                          break;
                
                default:printf("errno.\n");
            }
             if(led_fd<0)
             {
               printf("open led failed.\n");
               exit(1);     
             }
        }
          ioctl(led_fd,ON);
    }

    ioctl(led_fd,OFF);
    close(led_fd);
    close(button_fd);

    return 0;
} /* ----- End of main() ----- */

