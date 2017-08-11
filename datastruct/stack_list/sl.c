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
#include <stdlib.h>
#include "sl.h"

/* 创建节点 */
static STACK_NODE* create_node(int data, STACK_NODE* next)
{
     STACK_NODE* node = malloc(sizeof(STACK_NODE));
     node->data = data;
     node->next = next;
     return node;
}

/* 销毁节点 */
static STACK_NODE* destroy_node(STACK_NODE* node)
{
     STACK_NODE* next = node->next;
     free(node);
     return next;
}

/* 初始化为空堆栈 */
void stack_init(STACK* stack)
{
     stack->top = NULL;
}

/* 释放剩余节点并恢复到初始状态 */
void stack_deinit(STACK* stack)
{
     while(stack->top)
     {
          stack->top = destroy_node(stack->top);
     }
}

/* 判断是否为空 */
bool stack_empty(STACK* stack)
{
     return !stack->top;
}

/* 压入 */
int stack_push(STACK* stack, int data)
{
     stack->top = create_node(data, stack->top);
}

/* 弹出 */
int stack_pop(STACK* stack)
{
     int data = stack->top->data;
     stack->top = destroy_node(stack->top);
     return data;
}

/* 栈顶 */
int stack_top(STACK* stack)
{
     return stack->top->data;
}

/* 大小 */
size_t stack_size(STACK* stack)
{
     size_t size = 0;
     STACK_NODE* node = NULL;
     for (node = stack->top; node; node = node->next)
     {
          ++size;
     }
     return size;
}

