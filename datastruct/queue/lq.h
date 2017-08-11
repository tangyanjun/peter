/********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  order.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(07/24/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/24/2017 09:25:50 AM"
 *                 
 ********************************************************************************/
#ifndef _LQ_H
#define _LQ_H

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct QueueNode{
    int                 data; //数据
    struct QueueNode*   next; //后指针
} QUEUE_NODE;

typedef struct Queue{
    QUEUE_NODE* front;  //弹出，前端
    QUEUE_NODE* rear;   //压入，后端
} QUEUE;


/* 分配内存并初始化为空队列 */
void queue_init(QUEUE* queue);
/* 释放剩余节点并恢复到初始状态 */
void queue_deinit(QUEUE* queue);
/* 判断是否空 */
bool queue_empty(QUEUE* queue);
/* 压入 */
void queue_push(QUEUE* queue, int data);
/* 弹出 */
int queue_pop(QUEUE* queue);
/* 队首 */
int queue_front(QUEUE* queue);
/* 大小 */
size_t queue_size(QUEUE* queue);



#endif /* _LQ_H */

