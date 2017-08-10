#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include "od.h"


#define XRES 480
char *fb_addr;
unsigned int fb_size;







void main()
{
    int x1, y1,\
        x2, y2,\
        c, i, j;
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
    
    for(i=0; i<130560; i++)
    {
        *((unsigned short *)(fb_addr+i*2)) = ed[i];
    }
    printf("OK!\n");
    munmap(fb_addr, fb_size);
    close(fbd);
}
