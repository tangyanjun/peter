/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  si_test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(06/24/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/24/2017 04:50:48 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include "sl.h"

int main(int argc, char **argv)
{
    printf("整数：");
    unsigned int num;
    scanf("%d", &num);
    printf("进制：");
    int base;
    scanf("%d", &base);
    STACK stack;
    stack_init(&stack);
    do {
        stack_push(&stack, num % base);
    } while(num /= base);
    printf("结果：");
    while(!stack_empty(&stack))
    {
        int digit = stack_pop(&stack);
        printf("%d", digit);
    }
    printf("\n");
    stack_deinit(&stack);

    return 0;
}

