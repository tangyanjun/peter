#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "gps.h"

/**************************************************************************************
 *  Description:从GPS数据包中抽取出GPRMC最小定位信息
 *   Input Args:buff：GPS返回的数据包 gps_date：GPRMC信息存储结构体
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int gps_analysis(char *buff,GPRMC *gps_date)
{
    char *ptr=NULL;

    if(gps_date==NULL)
      return -1;

    if(strlen(buff)<10)
      return -1;

    if(NULL==(ptr=strstr(buff,"$GPRMC")))
     return -1;

    sscanf(ptr,"$GPRMC,%d.000,%c,%f,N,%f,E,%f,%f,%d,,,%c*",&(gps_date->time),&(gps_date->pos_state),&(gps_date->latitude),&(gps_date->longitude),&(gps_date->speed),&(gps_date->direction),&(gps_date->date),&(gps_date->mode));

   return 0;
} /* ----- End of if()  ----- */

/********************************************************************************************

strstr(str1,str2) 函数用于在字符串str1中搜寻str2，并返回str2在str1中首次出现的地址；否则，返回NULL
sscanf()格式化字符串输入，从一个字符串中读进与指定格式相符的数据并在存入到另一个字符串中

**********************************************************************************************/

/**************************************************************************************
 *  Description:解析GPRMC最小定位信息，并打印到屏幕上
 *   Input Args:gps_date：gps_analysis函数抽取的GPRMC信息
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int print_gps(GPRMC *gps_date)
{
    printf("                                                           \n");
    printf("                                                           \n");
    printf("===========================================================\n");
    printf("==              全球GPS定位导航模块                 ==\n");
    printf("==              开发人员：唐延军                           ==\n");
    printf("==              邮箱：519656780@qq.com                  ==\n");
    printf("==              平台：fl2440                             ==\n");
    printf("==              GPS型号：FIT-GPS_SF2820（代替ET-312）    ==\n");
    printf("===========================================================\n");
    printf("                                                         \n");
    printf("                                                         \n");
    printf("===========================================================\n");
    printf("==                                                       \n");
    printf("==   GPS状态位 : %c  [A:有效状态 V:无效状态]             \n", gps_date->pos_state);
    printf("==   GPS模式位 : %c  [A:自主定位 D:差分定位]             \n", gps_date->mode);
    printf("==   日期 : 20%02d-%02d-%02d                             \n", gps_date->date%100,(gps_date->date%10000)/100,gps_date->date/10000);
    printf("==   时间 : %02d:%02d:%02d                               \n", (gps_date->time/10000+8)%24,(gps_date->time%10000)/100,gps_date->time%100);
    printf("==   纬度 : 北纬:%d度%d分%d秒                                    \n", ((int)gps_date->latitude) / 100, (int)(gps_date->latitude - ((int)gps_date->latitude / 100 * 100)), (int)(((gps_date->latitude - ((int)gps_date->latitude / 100 * 100)) - ((int)gps_date->latitude - ((int)gps_date->latitude / 100 * 100))) * 60.0));
    printf("==   经度 : 东经:%d度%d分%d秒                                    \n", ((int)gps_date->longitude) / 100, (int)(gps_date->longitude - ((int)gps_date->longitude / 100 * 100)), (int)(((gps_date->longitude - ((int)gps_date->longitude / 100 * 100)) - ((int)gps_date->longitude - ((int)gps_date->longitude / 100 * 100))) * 60.0));
    printf("==   速度 : %.3f                                         \n", gps_date->speed);
    printf("==                                                       \n");
    printf("==========================================================\n");
    return 0;
} /* ----- End of print_gps()  ----- */
