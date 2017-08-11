/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  maze.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/08/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/08/2017 03:50:37 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sl.h"

/* environment */
#define SPACE_MOUSE    '*' /* mouse */
#define SPACE_WAY      ' ' /* passage */
#define SPACE_WALL     '@' /* wall */
#define SPACE_PASS     '.' /* track */
#define SPACE_IMPASSE  'X' /* impasse */

/* direction */
#define DIR_RIGHT  0  /* right */
#define DIR_DOWN   1  /* down */
#define DIR_LEFT   2  /* left */
#define DIR_UP     3  /* up */

/* The mouse */
const char* g_mouse = ">V<^";

typedef struct Mouse{
     int x;       /* horizontal */
     int y;       /* vertical */
     int dir;     /* direction */
     int total;   /* total number steps*/
     int valid;   /* effective steps */
     STACK brain; /* brain */
} MOUSE;


/* initialization */
void mouse_init(MOUSE* mouse, int x, int y, int dir)
{
     mouse->x = x;
     mouse->y = y;
     mouse->dir = dir;
     mouse->total = 0;
     mouse->valid = 0;
     stack_init(&mouse->brain);
}

/* finalization */
void mouse_deinit(MOUSE* mouse)
{
     stack_deinit(&mouse->brain);
}

/* memory of mouse */
void mouse_remember(MOUSE* mouse, int dir)
{
     stack_push(&mouse->brain, dir);
}

/* recall/reminiscence */
int mouse_recall(MOUSE* mouse)
{
     return stack_pop(&mouse->brain);
}

/* advance */
void mouse_go(MOUSE* mouse, int dir)
{
     switch(dir)
     {
         case DIR_RIGHT:
             ++mouse->x;
             break;
         case DIR_DOWN:
             ++mouse->y;
             break;
         case DIR_LEFT:
             --mouse->x;
             break;
         case DIR_UP:
             --mouse->y;
             break;
     }
     mouse_remember(mouse, mouse->dir = dir);
     ++mouse->total;
     ++mouse->valid;
     
}

/* retreat */
void mouse_back(MOUSE* mouse)
{
     switch (mouse_recall(mouse))
     {
          case DIR_RIGHT:
              --mouse->x;
              mouse->dir = DIR_LEFT;
              break;
          case DIR_DOWN:
              --mouse->y;
              mouse->dir = DIR_UP;
              break;
          case DIR_LEFT:
              ++mouse->x;
              mouse->dir = DIR_RIGHT;
              break;
          case DIR_UP:
              ++mouse->y;
              mouse->dir = DIR_DOWN;
              break;
     }
     ++mouse->total;
     --mouse->valid;
}

/* maze */
typedef struct Maze{
     int   cx;     /* width */
     int   cy;     /* height */
     char* space;  /* space */
     MOUSE mouse;  /* mouse */
}MAZE;

/* maze initialization */
void maze_init(MAZE* maze, int cx, int cy)
{
     maze->cx = cx;
     maze->cy = cy;
     maze->space = malloc(cx * cy * sizeof(char));
     mouse_init(&maze->mouse, 0, 1, DIR_RIGHT);
     srand(time(NULL));
     char (*space)[cx] = (char(*)[cx])maze->space;
     int y;
     int x;
     for (y = 0; y <cy; ++y)
     {
          for (x = 0; x < cx; ++x)
          {
              if (x == maze->mouse.x && y == maze->mouse.y)
              {
                   space[y][x] = SPACE_MOUSE;
              }
              else if((y == 1 && x < 4) || (y == cy - 2 && x > cx - 5))
              {
                   space[y][x] = SPACE_WAY;    
              }
              else if(y == 0 || y == cy -1 || x == 0 || x == cx - 1)
              {
                   space[y][x] = SPACE_WALL;
              }
              else
              {
                   space[y][x] = rand() % 4 ? SPACE_WAY : SPACE_WALL;
              }
          }
     }
}

/* maze finalization */
void maze_deinit(MAZE* maze)
{
     free(maze->space);
     mouse_deinit(&maze->mouse);
}

/* show the maze */
void maze_show(MAZE* maze)
{
     char(*space)[maze->cx] = (char(*)[maze->cx])maze->space;
     int y;
     int x;
     for (y = 0; y < maze->cy; ++y)
     {
          for (x = 0; x < maze->cx; ++x)
          {
              switch(space[y][x])
              {
                   case SPACE_MOUSE:
                       printf("\033[;;31m");  //color control red
                       break;
                   case SPACE_WALL:
                       printf("\033[;;34m");  //color control bule
                       break;
                   case SPACE_PASS:
                       printf("\033[;;32m");  //color control green
                       break;
                   case SPACE_IMPASSE:
                       printf("\033[;;35m");  //color control pruple
                       break;
              }
              printf("%c\033[0m", space[y][x] == SPACE_MOUSE ? g_mouse[maze->mouse.dir] : space[y][x]);
          }
          printf("\n");
     }
     printf("a total of go %d steps, %d effective.\n", maze->mouse.total, maze->mouse.valid);
}


/* read a char from standard input, no echo, no Enter */
int getch(void)
{
     struct termios old;
     ioctl(STDIN_FILENO, TCGETS, &old);
     struct termios new = old;
     new.c_lflag &= ~(ECHO | ICANON);
     ioctl(STDIN_FILENO, TCSETS, &new);
     int ch = getchar();
     ioctl(STDIN_FILENO, TCSETS, &old);
     return ch;
}

/* quit? */
bool maze_quit(void)
{
     printf("press Q to quit, press others to continue...");
     int ch = getch();
     printf("\n");
     return strchr("Qq", ch) != NULL;
}

/* next steps */
bool maze_step(MAZE* maze)
{
     char(*space)[maze->cx] = (char(*)[maze->cx])maze->space;
     int y = maze->mouse.y;
     int x = maze->mouse.x;
     space[y][x] = SPACE_PASS;
     if (x + 1 <= maze->cx - 1 && space[y][x + 1] == SPACE_WAY)
     {
          mouse_go(&maze->mouse, DIR_RIGHT);
     }
     else if(y + 1 <= maze->cy - 1 && space[y + 1][x] == SPACE_WAY)
     {
          mouse_go(&maze->mouse, DIR_DOWN);
     }
     else if(x - 1 >= 0 && space[y][x - 1] == SPACE_WAY)
     {
          mouse_go(&maze->mouse, DIR_LEFT);
     }
     else if(y - 1 >= 0 && space[y - 1][x] == SPACE_WAY)
     {
          mouse_go(&maze->mouse, DIR_UP);
     }
     else
     {
          space[y][x] = SPACE_IMPASSE;
          mouse_back(&maze->mouse);
     }
     y = maze->mouse.y;
     x = maze->mouse.x;
     space[y][x] = SPACE_MOUSE;
     maze_show(maze);
     if (y == maze->cy - 2 && x == maze->cx - 1)
     {
          printf("succeed!\n");
          return false;
     }
     if (y == 1 && x == 0)
     {
          printf("not to go!\n");
          return false;
     }
     return true;
}

/* run */
void maze_run(MAZE* maze)
{
     for (maze_show(maze); !maze_quit() && maze_step(maze););
}

/* main */
int main(int argc, char **argv)
{
     if (argc < 3)
     {
          printf("%s <width> <height>\n", argv[0]);
          return -1;
     }
     MAZE maze;
     maze_init(&maze, atoi(argv[1]), atoi(argv[2]));
     maze_run(&maze);
     maze_deinit(&maze);
     return 0;
}
