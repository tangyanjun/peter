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
#include "lq.h"

/* 创建节点 */
static QUEUE_NODE* create_node(int data)
{
    QUEUE_NODE* node = malloc(sizeof(QUEUE_NODE));
    node->data = data;
    node->next = NULL;
    return node;
}
/* 销毁节点 */
static QUEUE_NODE* destroy_node(QUEUE_NODE* node)
{
    QUEUE_NODE* next = node->next;
    free(node);
    return next;
}

/* 初始化为空队列 */
void queue_init(QUEUE* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

/* 释放剩余节点并恢复到初始状态 */
void queue_deinit(QUEUE* queue)
{
    while(queue->front)
    {
        queue->front = destroy_node(queue->front);
    }
    queue->rear = NULL;
}
/* 判断是否空 */
bool queue_empty(QUEUE* queue)
{
    return !queue->front && !queue->rear;
}
/* 压入 */
void queue_push(QUEUE* queue, int data)
{
    QUEUE_NODE* node = create_node(data);
    if (queue->rear)
    {
        queue->rear->next = node;
    }
    else
    {
        queue->front = node;
    }
    queue->rear = node;
}
/* 弹出 */
int queue_pop(QUEUE* queue)
{
    int data = queue->front->data;
    if (!(queue->front = destroy_node(queue->front)))
    {
        queue->rear = NULL;
    }
    return data;
}
/* 队首 */
int queue_front(QUEUE* queue)
{
    return queue->front->data;
}
/* 大小 */
size_t queue_size(QUEUE* queue)
{
    size_t size = 0;
    QUEUE_NODE* node = NULL;
    for (node = queue->front; node; node = node->next)
    {
        ++size;
    }
    return size;
}




