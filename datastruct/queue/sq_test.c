/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  sq_test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/24/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/24/2017 03:08:26 PM"
 *                 
 ********************************************************************************/
#include "sq.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    QUEUE queue;
    queue_init(&queue);
    queue_push(&queue, 1);
    queue_push(&queue, 2);
    queue_push(&queue, 3);
    queue_push(&queue, 4);
    queue_push(&queue, 5);
    printf("%d\n", queue_pop(&queue));
    printf("%d\n", queue_pop(&queue));
    printf("%d\n", queue_pop(&queue));
    queue_push(&queue, 6);
    queue_push(&queue, 7);
    queue_push(&queue, 8);
    while (!queue_empty(&queue))
    {
        printf("%d\n", queue_pop(&queue));
    }
    queue_deinit(&queue);

    return 0;
}

