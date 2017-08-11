/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  sort.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/26/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/26/2017 03:46:05 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* 冒泡排序 */
void bubble_sort(int data[], size_t size)
{
    int ordered = 1;  //记录是否需要排序了
    size_t j = 0;
    size_t i = 0;
    int swap = 0;
    for(i; i < size - 1; ++i)
    {
        for(j = 0; j < size - 1; ++j)
        {
            if(data[j] < data[j + 1])
            {
                swap = data[j + 1];
                data[j + 1] = data[j];
                data[j] = swap;
                ordered = 0;
            }
        }
        if(ordered)
        {
            break;
        }
    }
}

/* 插入排序 */
void insert_sort(int data[], size_t size)
{
    size_t i;
    for(i = 1; i < size; ++i)
    {
        int inserted = data[i];
        size_t j;
        for(j = i; j > 0 && inserted < data[j - 1]; --j)
        {
            data[j] = data[j - 1];
        }
        if(j != i)
        {
            data[j] = inserted;
        }
    }
}

/* 选择排序 */
void select_sort(int data[], size_t size)
{
    size_t i;
    for(i = 0; i < size - 1; i++)
    {
        size_t min = i;
        size_t j;
        for(j = i + 1; j < size; ++j)
        {
            if(data[j] < data[min])   
            {
                min = j;      
            }
        }
        if(min != i)
        {
            int swap = data[i];
            data[i] = data[min];
            data[min] = swap;
        }
    }
}

/* 快速排序 */
void quick_sort(int data[], size_t left, size_t right)
{
    size_t p = (left + right) / 2;
    int pivot = data[p];
    size_t i = left;
    size_t j = right;
    while(i < j)
    {
        for(; !(i >= p || pivot < data[i]); ++i);
        if(i < p)
        {
            data[p] = data[i];
            p = i;
        }
        for(; !(j <= p || data[j] < pivot); --j);
        if(j > p)
        {
            data[p] = data[j];
            p = j;
        }
    }
    data[p] = pivot;
    if(p - left > 1)
    {
        quick_sort(data, left, p - 1);
    }
    if(right - p > 1)
    {
        quick_sort(data, p + 1, right);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int data[10];
    size_t i = 0;
    size_t size = sizeof(data) / sizeof(data[0]);
    for(i = 0; i < size; i++)
    {
        printf("%2d ", data[i] = rand() % 100);
    }
    printf("\n");
    bubble_sort(data, size);
  //  insert_sort(data, size);
  //  select_sort(data, size);
 //   quick_sort(data, 0, size - 1);
    for(i = 0; i < size; i++)
    {
        printf("%2d ", data[i]);
    }
    printf("\n");

    return 0;
}

