/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  myqueue.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(08/04/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "08/04/2017 10:18:20 AM"
 *                 
 ********************************************************************************/
#include <stdio.h>

int main(int argc, char **argv)
{
    int i;
    int arr[100];
    printf("please input 6 numbers: ");
    for(i = 0; i < 6; ++i)
    {
        scanf("%d", &arr[i]);
    }
    int head = 0;
    int tail = 5;

    while(head <= tail){
        printf("%d ", arr[tail]);
        tail--;
    }
    printf("\n");
    
    return 0;
}

