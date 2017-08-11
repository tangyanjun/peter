/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  findex.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/26/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/26/2017 03:23:40 PM"
 *                 
 ********************************************************************************/
/* 数组:1 2 8 9 2 4 9 12 4 7 10 13 6 8 11 15 
 * 设计一个查找算法函数，返回匹配元素的下标
 * 观察
 * 1 2  8  9
 * 2 4  9 12
 * 4 7 10 13
 * 6 8 11 15
 * 右上角的值可作为中间值，用于缩小范围
 * */


#include <stdio.h>

size_t find(int data[], int rows, int cols, int key)
{
    if(!data || !rows || !cols)
    {
        return -1;
    }
    int row = 0;
    int col = cols - 1;
    while(row < rows && col >= 0)
    {
        size_t i = row * cols + col;
        if(key < data[i])
        {
            --col;
        }
        else if(data[i] < key)
        {
            ++row;
        }
        else
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    int data[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
    int j = 0;
    for(j = 0; j < 16; j++)
    {
        printf("%d ", data[j]);
    }
    printf("\n");
    int key;
    printf("请输入要查找的数:");
    scanf("%d", &key);
    size_t i = find(data, 4, 4, key);
    if(i == (size_t)-1)
    {
        printf("查找失败!\n");
    }
    else
    {
        printf("[%u] %d\n", i, data[i]);
    }
    return 0;
}
