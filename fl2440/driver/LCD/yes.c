#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

#define XRES 480

char *fb_addr;
unsigned int fb_size;
//void drawline(int x1, int y1, int x2, int y2, int c);
/*	light a pixel	*/
void Pixel(int x, int y, int color)
{
    *((unsigned short *)(fb_addr+y*XRES*2+x*2)) = color;
}
/*	draw a line	*/
void Line(int x1,int y1,int x2,int y2,int color)
{
    int dx,dy,e;
    dx=x2-x1; 
    dy=y2-y1;
    
    if(dx>=0)
    {
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 1/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}    
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 2/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}    
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)

            if(dx>=dy) // 8/8 octant
            {
                e=dy-dx/2;
                while(x1<=x2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}    
                    x1+=1;
                    e+=dy;
                }
            }
            else        // 7/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){x1+=1;e-=dy;}    
                    y1-=1;
                    e+=dx;
                }
            }
        }    
    }
    else //dx<0
    {
        dx=-dx;        //dx=abs(dx)
        if(dy >= 0) // dy>=0
        {
            if(dx>=dy) // 4/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){y1+=1;e-=dx;}    
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 3/8 octant
            {
                e=dx-dy/2;
                while(y1<=y2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}    
                    y1+=1;
                    e+=dx;
                }
            }
        }
        else           // dy<0
        {
            dy=-dy;   // dy=abs(dy)

            if(dx>=dy) // 5/8 octant
            {
                e=dy-dx/2;
                while(x1>=x2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){y1-=1;e-=dx;}    
                    x1-=1;
                    e+=dy;
                }
            }
            else        // 6/8 octant
            {
                e=dx-dy/2;
                while(y1>=y2)
                {
                    Pixel(x1,y1,color);
                    if(e>0){x1-=1;e-=dy;}    
                    y1-=1;
                    e+=dx;
                }
            }
        }    
    }
}

void Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Line(x1,y1,x2,y1,color);
    Line(x2,y1,x2,y2,color);
    Line(x1,y2,x2,y2,color);
    Line(x1,y1,x1,y2,color);
}
void FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
    Line(x1,i,x2,i,color);
}
void main()
{
    int x1, y1,\
        x2, y2,\
        c;
    int fbd = 0;
    struct fb_fix_screeninfo fb_fix;
    struct fb_var_screeninfo fb_var;

    fbd = open("/dev/fb0", O_RDWR);

    ioctl(fbd, FBIOGET_FSCREENINFO, &fb_fix);
    ioctl(fbd, FBIOGET_VSCREENINFO, &fb_var);

    fb_size = fb_var.yres * fb_fix.line_length;
    
    printf("xres:%d, yres:%d\n"\
            "bits_per_pixel:%d\n"\
            "height:%d, width:%d\n",\
            fb_var.xres, fb_var.yres,\
            fb_var.bits_per_pixel,\
            fb_var.height, fb_var.width);
    printf("smem_start:%ld\n"\
            "smem_len:%d\n"\
            "line_length:%d\n",\
            fb_fix.smem_start,\
            fb_fix.smem_len,\
            fb_fix.line_length);

    fb_addr=(char *)mmap(0, fb_size, PROT_READ|PROT_WRITE, MAP_SHARED, fbd, 0);
    
    Line(0, 0, 480, 272, 0xF800);

    Rectangle(100, 100, 200, 200, 0x7E00);

    FilledRectangle(300, 5, 480, 10, 0x1F);

   //drawline(136, 100, 136, 300, 0xFFFF);
    close(fbd);
}
