/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  mytest.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/22/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/22/2017 01:39:25 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <unistd.h>
#include <errno.h>

int main()
{
      int fb = 0;
      struct fb_var_screeninfo     vinfo;
      struct fb_fix_screeninfo     finfo;

      int screensize = 0;
      char  *fbp = 0;
      int x = 0;
      int y = 0;
      int location = 0;
      int bits_per_pixel;


      if(!(access("/dev/fb0", F_OK)))
      {
         printf("OK\n");
      }
      else
      {
         printf("fail%s\n", strerror(errno));
      }

      fb = open("/dev/fb0", O_RDWR, 0666);
      if(fb < 0)
      {
         printf("open failed%s\n", strerror(errno));
         return -1;
      }

      ioctl(fb, FBIOGET_FSCREENINFO, &finfo);
      ioctl(fb, FBIOGET_FSCREENINFO, &finfo);

      bits_per_pixel = vinfo.bits_per_pixel/8;
      screensize = vinfo.xres * vinfo.yres * bits_per_pixel;
      fbp = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
      if(fbp < 0)
      {
         printf("mmap%s\n", strerror(errno));
      }

      for(x=100; x<200; x++)
      {
          for(y=100; y<200; y++)
          {
            location = x * bits_per_pixel + y * finfo.line_length;
            *(fbp + location) = 0;
            *(fbp + location + 1) = 255;
            *(fbp + location + 2) = 0;
            *(fbp + location + 3) = 0;
          }
      }

      munmap(fbp, screensize);
      close(fb);
      return 0;

}
