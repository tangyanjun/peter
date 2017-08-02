/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  life.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(06/09/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "06/09/2017 09:24:57 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

int getch(void)   //为了去掉getchar的回车与回显
{
    struct termios term_old;
    ioctl(STDIN_FILENO, TCGETS, &term_old);
    struct termios term_new = term_old;
    term_new.c_lflag &= ~(ECHO | ICANON);
    ioctl(STDIN_FILENO, TCSETS, &term_new);
    int ch = getchar();
    ioctl(STDIN_FILENO, TCSETS, &term_old);
    return ch;
}

int main(void)
{
    printf("群落宽度:");
    int width;
    scanf("%d", &width);
    printf("群落高度:");
    int height;
    scanf("%d%*c", &height);
    char cells[height][width];
    srand(time(0));
    int i, j;
    for (i = 0; i < height; ++i)
        for (j = 0; j < width; ++j)
            cells[i][j] = rand() % 2 ? '*' : ' ';
    int gen;
    for (gen = 1;;++gen)
    {
        printf("+-");
        for (i = 0; i < width * 2; ++i)
            printf("-");
        printf("+\n");
        int live = 0;
        for (i = 0; i < height; ++i)
        {
            printf("| ");
            for (j = 0; j < width; ++j)
            {
                printf("%c ", cells[i][j]);
                if(cells[i][j] == '*')
                {
                   ++live;
                }
            }
            printf("|\n");
        }
        printf("+-");
        for(i = 0; i < width * 2; ++i)
            printf("-");
        printf("+\n");
        printf("第%d代, 有%d个活的。\n", gen, live);
        printf("按<Q>键退出，按其他键继续...");
        int ch = getch();
        printf("\n");
        if (ch == 'Q' || ch == 'q')
        {
            break;
        }
        for (i = 0; i < height; ++i)  //前缀节省一丢丢时间
            for (j = 0; j < width; ++j)
            {
                int u = i - 1;
                int d = i + 1;
                int l = j - 1;
                int r = j + 1;
                int around = 0;
                if (u >= 0 && cells[u][j] == '*')
                    ++around;
                if (d < height && cells[d][j] == '*')
                    ++around;
                if (l >= 0 && cells[i][l] == '*')
                    ++around;
                if (r < width && cells[i][r] == '*')
                    ++around;
                if (u >= 0 && l >= 0 && cells[u][l] == '*')
                    ++around;
                if (u >= 0 && r < width && cells[u][r] == '*')
                    ++around;
                if (d < height && l >= 0 && cells[d][l] == '*')
                    ++around;
                if (d < height && r < width && cells[d][r] == '*')
                    ++around;
                if (around == 3)
                    cells[i][j] = '*';
                else if (around != 2)
                    cells[i][j] = ' ';
            }
    }   //主要打印我们的环境
    return 0;
}

