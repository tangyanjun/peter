/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  cs.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/28/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/28/2017 05:35:28 AM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <errno.h>



int main(int argc, char **argv)
{
     int fb = -1;
     struct fb_var_screeninfo vinfo;
     unsigned char *pdf;
     int size = 0;

     fb = open("/dev/fb0", O_RDWR, 0666);
     if(fb < 0)
     {
         printf("open failed!%s\n", strerror(errno));
         exit(1);
     }
     
     ioctl(fb, FBIOGET_VSCREENINFO, &vinfo);
     size = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
     pdf =(char *)mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fb, 0);
     if((int)pdf == -1)
     {
         printf("mmaped failed!%s\n", strerror(errno));
     }
       
     write(fb, pdf, 4);


     if (vinfo.bits_per_pixel != 16)
     {
         printf("not support!%s\n", strerror(errno));
         exit(2);
     }



     



          
     munmap(pdf, size);
     close(fb);
}

