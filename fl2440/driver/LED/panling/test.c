/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/26/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/26/2017 05:10:58 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char **argv)
{
    int fd;
    int key_num;
    fd = open("/dev/key", 0);    
    if (fd<0)
        printf("open fail\n");
    read(fd, &key_num, 4);
    printf("key is %d\n",key_num);
    close(fd);
    return 0;
}

