/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  otest.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/24/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/24/2017 09:45:15 AM"
 *                 
 ********************************************************************************/
#include "order.h"

int main(int argc, char **argv)
{
    QUEUE queue;
    queue_init(&queue, 9);
    int i = 0;
    
    for (i = 10; i <= 50; i+=10)
    {
        if (!queue_full(&queue))
        {
            queue_push(&queue, i);
        }
    }
    
    for (i = 0; i < 2; ++i)
    {
        if (!queue_empty(&queue))
        {
            printf("%d\n", queue_pop(&queue));
        }
    }
    
    for (i = 50; i <= 80; i+=10)
    {
        if (!queue_full(&queue))
        {
            queue_push(&queue, i);
        }
    }
    
    while(!queue_empty(&queue))
    {
        printf("%d\n", queue_pop(&queue));
    }
    
    queue_deinit(&queue);
    
    return 0;
}

