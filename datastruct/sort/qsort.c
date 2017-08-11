/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  qsort.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/26/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/26/2017 07:40:40 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
    char name[20];
    int age;
}STUDENT;

/* 自己写函数实现qsort */
void _myqsort(void* base, size_t left, size_t right, size_t size, int(*compar)(const void*, const void*))
{
    size_t p = (left + right) / 2;
    void* pivot = malloc(size);
    memcpy(pivot, base + p * size, size);
    size_t i = left;
    size_t j = right;
    while(i < j)
    {
        for(; !(i >= p || compar(pivot, base + i * size) < 0); ++i);
        if(i < p)
        {
            memcpy(base + p * size, base + i * size, size);
            p = i;
        }
        for(; !(j <= p || compar(base + j * size, pivot) < 0); --j);
        if(j > p)
        {
            memcpy(base + p * size, base + j * size, size);
            p = j;
        }
    }
    memcpy(base + p * size, pivot, size);
    free(pivot);
    if(p - left > 1)
    {
        _myqsort(base, left, p - 1, size, compar);
    }
    if(right - p > 1)
    {
        _myqsort(base, p + 1, right, size, compar);
    }
}

void myqsort(void* base, size_t nmemb, size_t size, int(*compar)(const void*, const void*))
{
    _myqsort(base, 0, nmemb - 1, size, compar);      
}

int stu_cmp(const void* a, const void* b)
{
    const STUDENT* pa = (const STUDENT*)a; 
    const STUDENT* pb = (const STUDENT*)b;
    int res = strcmp(pa->name, pb->name);  //先比较姓名大小
    if(!res)
    {
        return pa->age - pb->age;  //姓名大小一样，则按年龄升序
    }
    return -res;
}

int int_cmp(const void* a, const void* b)
{
    return *(const int*)b - *(const int*)a;
}

int str_cmp(const void* a, const void* b)   //字母的ASCII码值
{
    return strcmp(*(const char* const*)a, *(const char* const*)b);
}

int main(int argc, char **argv)
{
    int na[] = {55, 22, 33, 11, 44, 88, 99, 0, 77, 66};
    size_t size = sizeof(na[0]);
    size_t nmemb = sizeof(na) / size;
    qsort(na, nmemb, size, int_cmp);
    size_t i;
    for(i = 0; i < nmemb; ++i)
    {
        printf("%d ", na[i]);
    }
    printf("\n");
 
    const char* sa[] = {"beijing", "tianjin", "shanghai", "chongqing"};
    size = sizeof(sa[0]);
    nmemb = sizeof(sa) / size;
    qsort(sa, nmemb, size, str_cmp);
    for(i = 0; i < nmemb; ++i)
    {
        printf("%s ", sa[i]);
    }
    printf("\n");
    STUDENT ta[] = {
        {"zhangfei", 25},
        {"zhaoyun", 22},
        {"zhangfei", 20},
        {"zhaoyun", 23},
        {"guanyu", 50},
    };
    size = sizeof(ta[0]);
    nmemb = sizeof(ta) / size;
    qsort(ta, nmemb, size, stu_cmp);
    for(i = 0; i < nmemb; ++i)
    {
        printf("%s/%d ", ta[i].name, ta[i].age);
    }
    printf("\n");
    return 0;
}

