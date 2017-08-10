/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  server.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(06/04/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/04/2017 09:22:31 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "gps.h"
#define      SIZE         100

int gps_analysis(char *buff, GPRMC *gps_date)
{
      char *ptr = NULL;
      
      if (gps_date == NULL)
          return -1;

      if (strlen(buff) < 10)
          return -1;

      if (NULL == (ptr = strstr(buff, "$GPRMC")))
          return -1;

      sscanf(ptr, "$GPRMC,%d.000,%c,%f,N,%f,E,%f,%f,%d,,,%c*", &(gps_date->time),&(gps_date->pos_state),&(gps_date->latitude),&(gps_date->longitude),&(gps_date->speed),&(gps_date->direction),&(gps_date->date),&(gps_date->mode));

      return 0;
}


int print_gps(GPRMC  *gps_date)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2222);
    addr.sin_addr.s_addr = inet_addr("192.168.0.5");
    int res = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (res == -1)
    {
        perror("connect");
        exit(-1);
    }
    printf("connect ok\n");
//    write(fd, "hello", 5);
    char buf[SIZE] = {};
    sprintf(buf, "纬度 : 北纬:%d度%d分%d秒\n, 经度 : 东经:%d度%d分%d秒\n", ((int)gps_date->latitude) / 100, (int)(gps_date->latitude - ((int)gps_date->latitude / 100 * 100)), (int)(((gps_date->latitude - ((int)gps_date->latitude / 100 * 100)) - ((int)gps_date->latitude - ((int)gps_date->latitude / 100 * 100))) * 60.0), ((int)gps_date->longitude) / 100, (int)(gps_date->longitude - ((int)gps_date->longitude / 100 * 100)), (int)(((gps_date->longitude - ((int)gps_date->longitude / 100 * 100)) - ((int)gps_date->longitude - ((int)gps_date->longitude / 100 * 100))) * 60.0));
    write(fd, &buf, strlen(buf));
    close(fd);
    return 0;
}

