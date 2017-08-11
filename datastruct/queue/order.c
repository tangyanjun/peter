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
#include "order.h"


/* 分配内存并初始化为空队列 */
void queue_init(QUEUE* queue, size_t cap)
{
    queue->arr = malloc(cap * sizeof(queue->arr[0]));  //为数组分配内存空间大小
    queue->cap = cap;  //容量
    queue->rear = 0;
    queue->front = 0;
    queue->size = 0;
}
/* 释放内存并恢复到初始状态 */
void queue_deinit(QUEUE* queue)
{
    free(queue->arr);
    queue->arr = NULL;
    queue->cap = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}
/* 判断是否满 */
bool queue_full(QUEUE* queue)
{
    return queue->size >= queue->cap;
}
/* 判断是否空 */
bool queue_empty(QUEUE* queue)
{
    return !queue->size;
}
/* 压入 */
void queue_push(QUEUE* queue, int data)   //满了不能压
{
    if(queue->rear >= queue->cap)
    {
        queue->rear = 0;
    }
    ++queue->size;
    queue->arr[queue->rear++] = data;
}
/* 弹出 */
int queue_pop(QUEUE* queue)
{
    if(queue->front >= queue->cap)   //空了不能弹
    {
       queue->front = 0;
    }
    --queue->size;
    return queue->arr[queue->front++];
}
/* 队首 */
int queue_front(QUEUE* queue)
{
    if(queue->front >= queue->cap)
    {
        queue->front = 0;
    }
    return queue->arr[queue->front];
}
/* 大小 */
size_t queue_size(QUEUE* queue)
{
    return queue->size;
}




