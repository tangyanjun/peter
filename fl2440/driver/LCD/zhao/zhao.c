/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  zhao.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/21/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/21/2017 10:49:26 AM"
 *                 
 ********************************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
       int fbfd=0;
       struct fb_var_screeninfo vinfo;
       unsigned long screensize=0;
       char *fbp=0;
       int x=0,y=0;
       fbfd=open("/dev/fb0",O_RDWR);  //打开帧缓冲设备
       if(!fbfd){
              printf("error\n");
              exit(1);
       }
       if(ioctl(fbfd,FBIOGET_VSCREENINFO,&vinfo)){  //获取屏幕可变参数
              printf("error\n");
              exit(1);
       }
       //打印屏幕可变参数
       printf("%dx%d,%dbpp\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);
       screensize=vinfo.xres*vinfo.yres* vinfo.bits_per_pixel/2;  //缓冲区字节大小
       fbp=(char *)mmap(0,screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fbfd,0);//映射
       if((int)fbp==-1){
              printf("error\n");
              exit(4);
       }   
       memset(fbp,0,screensize); //清屏
       char hz[16][2]={
       0x08, 0x00, 0x08, 0x00, 0x08, 0x04, 0x7E, 0x84, 0x08, 0x48, 0x08, 0x28, 0xFF, 0x10, 0x08, 0x10,
       0x28, 0x28, 0x2F, 0x28, 0x28, 0x44, 0x28, 0x84, 0x58, 0x00, 0x48, 0x00, 0x87, 0xFE, 0x00, 0x00,                                                                                  
    }; //16*16字模库中提取的“赵”字对应的字符数组
       int i,j,k;
       for(j=0;j<16;j++){
            for(i=0;i<2;i++){
                for(k=0;k<8;k++){
                    if(hz[j][i]&(0x80>>k))
                        *((unsigned short *)(fbp + j*vinfo.xres*2 + i*16 + k*2))=0xf100;
                }
            }
       }        
       munmap(fbp,screensize);
       close(fbfd);
       return 0;
}

