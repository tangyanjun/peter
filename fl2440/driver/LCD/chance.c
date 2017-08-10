/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  chance.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/27/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/27/2017 11:23:43 PM"
 *                 
 ********************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stdlib.h>
//#define COLOR     0x0F1000


    

int main(int argc, char **argv)
{
     int fd = -1;
     unsigned char* fb_mem;
     char *fbp = 0;
     int size = 0;
     int xres = 0;
     int yres = 0;
     int bits_per_pixel;
     int info = 0;
     struct fb_var_screeninfo vinfo; 
     int color = 0x0F1000; 
     if(!(access("/dev/fb0", F_OK)))
     {
        printf("File exist\n");
     }

     fd = open("/dev/fb0", O_RDWR, 0666);
     if (fd < 0)
     {
         printf("fail to open!%s\n", strerror(errno));   
         exit(1);
     }
     else
     {
         printf("open OK\n");
     }


     info = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
     if(info == 0)
     {
         printf("read ok!\n");
     }
    
     size = vinfo.xres * vinfo.yres * 2;

     

     fbp =(char *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
     if ((int)fbp == -1)
     {
         printf("mmaping faild!%s\n", strerror(errno));
         exit(3);
     }
    else
    {
         printf("mmaping OK\n");
    }

     
    
     *((short *)(fbp) + 200 * vinfo.xres + 200) = color;
            
     

     close(fd);
     munmap(fbp, size);
     
     return 0;


}

