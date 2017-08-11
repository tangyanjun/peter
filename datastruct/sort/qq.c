/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  qq.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/27/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/27/2017 06:01:10 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <string.h>

int main(int argc, char argv)
{
    char arr[5] = "hello";
    char str[5];
    int i;
    for(i = 0; i < 5; i++)
    {
        str[i] = arr[5 - i - 1];
    }
    printf("%s\n", str);


    
    int data[5] = {12, 52, 22, 40, 20};
    int max = data[0];
    for(i = 0; i < 5; i++)
    {
        if(data[i] > max)
        {
            max = data[i];
        }
    }
    printf("%d\n", max);
    return 0;
}

