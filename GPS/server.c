/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  server.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(06/05/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/05/2017 07:42:35 AM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv)
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
    addr.sin_addr.s_addr = INADDR_ANY;
    int res = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (res == -1)
    {
        perror("bind");
        exit(-1);
    }
    printf("bind ok\n");
    listen(fd, 100);
    struct sockaddr_in from;
    socklen_t len = sizeof(from);
    int sockfd = accept(fd, (struct sockaddr*)&from, &len);
    printf("%s连接了\n", inet_ntoa(from.sin_addr));
    char buf[100] = {};
    res = read(sockfd, buf, sizeof(buf));
    printf("读到了%d字节,内容:%s\n", res, buf);
    close(sockfd);
    close(fd);
    return 0;
}

