/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  myfun.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/27/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/27/2017 03:46:24 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <string.h>

/* realize of strlen*/
void mystrlen(char data[])
{
    int i = 0;
    int len = 0;
    for(i = 0; data[i] != '\0'; i++)
    {
        len++;
    }
    printf("len = %d\n", len);
}

/* realize of strcpy and strncpy */
void mystrcpy(char data[], char data1[])
{
    int i = 0;
    for(i = 0; data[i] != '\0'; ++i)
    {
        data1[i] = data[i];
    }
    data1[i] = '\0';
    printf("%s %s\n", data1, data);
}


void mystrncpy(char data[], char data1[], int n)  //复制前n个字符
{
    int i = 0;
    for(i = 0; i < n && data[i] != '\0'; ++i)
    {
        data1[i] = data[i];
    }
    data1[i] = '\0';
    printf("%s %s\n", data1, data);
}


/* realize of strcat and strncat */
void mystrcat(char data[], char data1[])
{
    int len = strlen(data);
    int len1 = strlen(data1);
    int i;
    for(i = 0; data1[i] != '\0'; ++i)
    {
        data[len + i] = data1[i];
    }
    printf("%s\n", data);
}

  
void mystrncat(char data[], char data1[], int n)  //追加n个字符
{
    int len = strlen(data);
    int len1 = strlen(data1);
    int i;
    for(i = 0; i < n && data1[i] != '\0'; ++i)
    {
        data[len + i] = data1[i];
    }
    printf("%s\n", data);

}

int mystrcmp(char data[], char data1[])
{
    int i;
    for(i = 0; ; i++)
    {
        if(data[i] < data1[i])
        {
            return -1;
        }
        else if(data[i] > data1[i])
        {
            return 1;
        }
        else if(data[i] == '\0')
        {
            return 0;
        }
    }
}


int mystrncmp(char data[], char data1[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(data[i] < data1[i])
        {
            return -1;
        }
        else if(data[i] > data1[i])
        {
            return 1;
        }
        else if(data[i] == data1[i])
        {
            return 0;
        }
    }
}

void mystrstr(char data[], char data1[])
{
    char* index = NULL;
    index = data;
    char* str1 = NULL;
    char* str2 = NULL;

    if(*data1 == '\0')
    {
        printf("The data1 is NULL!\n");
    }

    while(*index != '\0')
    {
        str1 = index;
        str2 = data1;

        while(*str1 != '\0' && *str2 != '\0' && (*str1 - *str2) == 0)
        {
            str1++;
            str2++;
        }

        if(*str2 == '\0')
        {
            printf("%s\n", index);
        }

        index++;
    }

}


int main(int argc, char argv)
{
    char data[] = "123456789";
    char data1[] = "abc";
    char data2[4] = {'a', 's', 'b', 'w'};
//    mystrlen(data2);  
    mystrcpy(data1, data);
    mystrncpy(data, data1, 5);
//    mystrcat(data, data1);
//    mystrncat(data, data1, 2);
//      mystrstr(data, data1);
/*  
    int res = mystrcmp(data, data1);
    switch(res)
    {
        case 1:
            printf("data > data1\n");
            break;
        case -1:
            printf("data < data1\n");
            break;
        case 0:
            printf("data == data1\n");
            break;
        default:
            break;
    }

  
    int res1 = mystrncmp(data, data1, 1);
    switch(res1)
    {
        case 1:
            printf("data > data1\n");
            break;
        case -1:
            printf("data < data1\n");
            break;
        case 0:
            printf("data == data1\n");
            break;
        default:
            break;
    }
*/
    return 0;
}
