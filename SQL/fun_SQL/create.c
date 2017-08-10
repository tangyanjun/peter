/*********************************************************************************
 *      Copyright:  (C) 2017 tangyanjun<519656780@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  create.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(07/10/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "07/10/2017 09:11:49 PM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can not open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    sqlite3_close(db);

    return 0;
}

