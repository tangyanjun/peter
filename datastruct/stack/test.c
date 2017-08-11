/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  stack.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(06/11/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/11/2017 09:13:51 PM"
 *                 
 ********************************************************************************/
/* 基于顺序表的堆栈 */
#include "stack.h"
#include <stdio.h>
/* 测试用例 */
int main(void)
{
    STACK stack;
    stack_init(&stack, 12);
    int i = 0;
    while (!stack_full(&stack))
    {
        stack_push(&stack, i++);
    }
    while (!stack_empty(&stack))
    {
        printf("%d\n", stack_pop(&stack));
    }
    stack_deinit(&stack);
    return 0;
}


