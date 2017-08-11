/********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  sl.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(06/15/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/15/2017 09:40:34 PM"
 *                 
 ********************************************************************************/
#ifndef  _SL_H
#define  _SL_H
#include <sys/types.h>
#include <stdbool.h>
/* 节点 */
typedef struct StackNode{
       int                  data;  /* 数据 */
       struct StackNode*   next; /* 后指针，结构体中可以定义同名指针，但是不可以定义同名变量，因为不影响同类型的类型大小计算 */
} STACK_NODE;

/* 堆栈 */
typedef struct Stack{
       STACK_NODE*   top;  /* 栈顶 */
} STACK;

/* 初始化为空堆栈 */
void stack_init(STACK* stack);
/* 释放剩余节点并恢复到初始状态 */
void stack_deinit(STACK* stack);
/* 判断是否为空 */
bool stack_empty(STACK* stack);
/* 压入 */
int stack_push(STACK* stack, int data);
/* 弹出 */
int stack_pop(STACK* stack);
/* 栈顶 */
int stack_top(STACK* stack);
/* 大小 */
size_t stack_size(STACK* stack);
#endif /* _SL_H */

