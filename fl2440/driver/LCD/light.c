/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  light.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/21/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/21/2017 02:04:02 AM"
 *                 
 ********************************************************************************/
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
      int fd;

      fd = open("/sys/class/leds/backlight/brightness", O_RDWR);
      if(fd < 0)
      {
           printf("can not open file.\n");
           return -1;
      }

      if (!strcmp(argv[1], "on"))
      write(fd, "1", 1);
      else if(!strcmp(argv[1], "off"))
      write(fd, "0", 1);

      close(fd);
      return 0;
}

