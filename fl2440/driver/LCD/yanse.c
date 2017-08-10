/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  yanse.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/11/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/11/2017 02:07:31 AM"
 *                 
 ********************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#define FB_DEVICE_NAME "/dev/fb0"


#define RED_COLOR565      0X0F100
#define WHITE_COLOR565    0XFFFFF
#define BLUE_COLOR565     0X0001F
#define GOLD_COLOR565     0XFFD70
//#define BROWN_COLOR565    0XA23A2
//#define BLACK_COLOR565    0X00000
//#define GRAY_COLOR565     0X80808
//#define GREEN_COLOR565    0X00800
//#define PURPLE_COLOR565   0X80008



typedef struct fb_dev{
             int fd;/*帧缓冲设备硬件描述符*/
             void *pfb;/*指向帧缓冲映射到用户空间的首地址*/
             int xres;/*一帧图像的宽度*/
             int yres;/*一帧图像的高度*/
             int size;/*一帧图像的大小*/
             int bits_per_pixel;/*每个像素的大小*/
     } fb_dev_t;

int fb_open(fb_dev_t *fbd, char *fbn)
{
    struct fb_var_screeninfo vinfo;

    if((fbd->fd = open(fbn, O_RDWR)) == -1)
    {
          printf("Error: Cannot open framebuffer device.\n");
          _exit(EXIT_FAILURE);
    }

   /* 获取LCD可变参数*/
   ioctl(fbd->fd, FBIOGET_VSCREENINFO, &vinfo);

   fbd->xres = vinfo.xres;
   fbd->yres = vinfo.yres;
   fbd->bits_per_pixel = vinfo.bits_per_pixel;

   /* 计算一帧图像的大小 */
   fbd->size = fbd->xres * fbd->yres * fbd->bits_per_pixel / 8;
   
   printf("%d * %d,%d bits_per_pixel,screensize = %d.\n",fbd->xres,fbd->yres,fbd->bits_per_pixel,fbd->size);

    /* 将帧映射到内存 */
    /* mmap的应用*/
/*mmap可以把文件内容映射到一段内存中，准确说是虚拟内存，通过对这段内存的读取和修改，实现对文件的读取和修改。 */
/* addr:指定映射的起始地址，通常为NULL，由系统指*/
/* length:将文件的多大长度映射到内存 */
/* prot:映射区的保护方式，可以是可被执行(PROT_EXEC)，可被写入(PROT_WRITE)，可被读取(PROT_READ)，映射区不能存取(PROT_NONE) */
/* flags:映射区的特性，对映射区的写入数据会复制回文件，且允许其他映射文件的进城共享(MAP_SHARED)，对映射区的写入操作会产生一个映射的复制，对此区域所做的修改不会写会源文件(MAP_PRIVATE) */
/* fd:由open返回的文件描述符，代表要映射的文件 */
/* offset:以文件开始出的偏移，必须是分页大小的整数倍，通常为0，表示从头开始映射 */

/* 注意:在修改映射文件时，只能在原长度上修改，不能增加文件长度，因为内存是已经分配好的 */

      fbd->pfb = mmap(NULL, fbd->size, PROT_READ | PROT_WRITE, MAP_SHARED, fbd->fd, 0);

      if((int)fbd->pfb == -1) 
      {
              printf("Error: Failed to map frambuffer device to memory!\n");
              _exit(EXIT_FAILURE);
      }

                return 0;
}

      int fb_close(fb_dev_t *fbd)
      {
       /* 解除映射 */
           munmap(fbd->pfb, fbd->size);

       /* 关闭设备文件 */
           close(fbd->fd);
      }

int fb_drawrect(fb_dev_t *fbd, int x0, int y0, int w, int h, int color)
{
              int x,y;

              for(y=y0; y<y0+h; y++)
              {
                  for(x=x0; x<x0+w; x++)
                  {
                        *((short *)(fbd->pfb) + y*fbd->yres + x) = color;
                  }
              }    

              return 0;
}
#if 1
int fb_drawrect1(fb_dev_t *fbd1, int x1, int y1, int w1, int h1, int color1)
{
              int x2;
              int y2;

              for(y2=y1; y2<y1+h1; y2++)
              {
                   for(x2=x1; x2<x1+w1; x2++)
                   {
                       *((short *)(fbd1->pfb) + x2*fbd1->xres + y2) = color1;
                   }
              }
              return 0;
}
#endif


#if 0
void Draw_Text16 (unsigned int x, U32 y, U32 color, const unsigned char ch[]) 
{
    unsigned short int i,j;
    unsigned char mask,buffer;
    for(i=0; i<16; i++)
    {
       mask = 0x80;//掩码
       buffer = ch[i*2];//提取一行的第一个字节
       for(j=0; j<8; j++)
       {
          if(buffer&mask)
          {
                 PutPixel(x+j, y+i, color); //为笔画上色
          }
               mask = mask>>1;
       }
          mask = 0x80;//掩码
          buffer = ch[i*2+1];//提取一行的第二个字节
          for(j=0; j<8; j++)
          {
              if(buffer&mask)
              { 
                   PutPixel(x+j+8,y+i,color);//为笔画上色
              }
                  mask = mask>>1;
          }
     }
}

#endif


int main(int argc, char **argv)
{
      fb_dev_t *fbd;
      fb_dev_t *fbd1;
      fbd = (fb_dev_t *)malloc(sizeof(fb_dev_t));

      fb_open(fbd, FB_DEVICE_NAME);

      if(fbd->bits_per_pixel == 16)
      {
          
           printf("Red/WHITE/Blue/GOLD Screen!");

          fb_drawrect(fbd, 0, 0, fbd->yres, fbd->xres, RED_COLOR565);
       //   sleep(2);
      //   fb_drawrect(fbd, 0, fbd->xres/4, fbd->yres, fbd->xres/4,WHITE_COLOR565);
     //     sleep(2);
    //      fb_drawrect(fbd, 0, fbd->xres*2/4, fbd->yres, fbd->xres/4, BLUE_COLOR565);
    //      sleep(2);
  //        fb_drawrect(fbd, 0, fbd->xres*3/4, fbd->yres, fbd->xres/4, GOLD_COLOR565);
//          sleep(2);

        //  memset(fbd->pfb, 0, fbd->size);
        // fb_drawrect1(fbd1, 0, 0, fbd1->yres, fbd1->xres/4, GOLD_COLOR565);
       //  sleep(2);
       //  fb_drawrect1(fbd1, 0, fbd1->xres/4, fbd1->yres, fbd1->xres/4, GOLD_COLOR565);
        // sleep(2);
       //  fb_drawrect1(fbd1, 0, fbd1->xres*2/4, fbd1->yres, fbd1->xres/4, GOLD_COLOR565);
      //   sleep(2);
      //   fb_drawrect1(fbd1, 0, fbd->xres*3/4, fbd1->yres, fbd1->xres/4, GOLD_COLOR565);
      
      
      }   

      

      else
           printf("16 bits only!");

           fb_close(fbd);

           return 0;
}

