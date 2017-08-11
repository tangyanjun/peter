/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  find.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/26/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/26/2017 02:43:56 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* 线性查找 */

size_t line_find(int data[], size_t size, int key)
{
    size_t i;
    for(i = 0; i < size; i++)
    {
        if(data[i] == key)
        {
            return i;
        }
    }
    return -1;
}

/* 二分法查找 */
size_t half_find(int data[], size_t size, int key)
{
    int left = 0;
    int right = size - 1;
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if(key < data[mid])
        {
            right = mid - 1;
        }
        else if(data[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int data[10];
    size_t i;
    size_t size = sizeof(data) / sizeof(data[0]);
    for(i = 0; i < size; i++)
    {
        printf("%d ", data[i] = /*rand() % 100*/i);
    }
    printf("\n");
    printf("查找目标:");
    int key;
    scanf("%d", &key);
    printf("查找结果:");
    //i = line_find(data, size, key);
    i = half_find(data, size, key);
    if(i == (size_t) - 1)
    {
        printf("失败!\n");
    }
    else
    {
        printf("[%u] %d\n", i, data[i]);
    }
    return 0;
}
