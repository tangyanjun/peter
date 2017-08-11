/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  lqtest.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/24/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/24/2017 10:46:52 AM"
 *                 
 ********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include "lq.h"

int main(int argc, char **argv)
{
    QUEUE queue;
    queue_init (&queue);
    char text[20];

    for(;;)
    {
        fgets(text, 20, stdin);
        if (strcmp(text, "!") == 0)
        {
            break;
        }
        queue_push(&queue, (int)strcpy(malloc((strlen(text) + 1) * sizeof(char)), text));
    }
    printf("-----------------\n");
    while(!queue_empty(&queue))
    {
        char* ps = (char*)queue_pop(&queue);
        printf("%s\n", ps);
        free(ps);
    }
    queue_deinit(&queue);
    return 0;
}

