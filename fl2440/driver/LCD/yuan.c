/*********************************************************************************
 *      Copyright:  (C) 2017 minda
 *                  All rights reserved.
 *
 *       Filename:  yuan.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/22/2017)
 *         Author:  tangyanjun <519656780@qq.com>
 *      ChangeLog:  1, Release initial version on "04/22/2017 07:12:35 PM"
 *                 
 ********************************************************************************/

#define U32 unsigned int
#define M5D(n)           ((n) & 0x1fffff)
#define rGPCCON (*(volatile unsigned *)0x56000020)//Port C control
#define rGPCDAT (*(volatile unsigned *)0x56000024)//Port C data
#define rGPCUP (*(volatile unsigned *)0x56000028)//Pull-up control C

#define rGPDCON (*(volatile unsigned *)0x56000030)//Port D control
#define rGPDDAT (*(volatile unsigned *)0x56000034)//Port D data
#define rGPDUP (*(volatile unsigned *)0x56000038)//Pull-up control D

#define rGPGCON (*(volatile unsigned *)0x56000060)//Port G control
#define rGPGDAT (*(volatile unsigned *)0x56000064)//Port G data
#define rGPGUP (*(volatile unsigned *)0x56000068)//Pull-up control G

#define rLCDCON1 (*(volatile unsigned *)0x4d000000)//LCD control 1
#define rLCDCON2 (*(volatile unsigned *)0x4d000004)//LCD control 2
#define rLCDCON3 (*(volatile unsigned *)0x4d000008)//LCD control 3
#define rLCDCON4 (*(volatile unsigned *)0x4d00000c)//LCD control 4
#define rLCDCON5 (*(volatile unsigned *)0x4d000010)//LCD control 5
#define rLCDSADDR1 (*(volatile unsigned *)0x4d000014)//STN/TFT Frame buffer start address 1
#define rLCDSADDR2 (*(volatile unsigned *)0x4d000018)//STN/TFT Frame buffer start address 2
#define rLCDSADDR3 (*(volatile unsigned *)0x4d00001c)//STN/TFT Virtual screen address set
#define rLCDINTMSK (*(volatile unsigned *)0x4d00005c)//LCD Interrupt mask
#define rTCONSEL (*(volatile unsigned *)0x4d000060)//LPC3600 Control --- edited by junon

#define LCD_WIDTH    480
#define LCD_HEIGHT   272

//垂直同步信号的脉宽、后肩和前肩
#define VSPW (3-1)
#define VBPD (15-1)
#define VFPD (12-1)
//水平同步信号的脉宽、后肩和前肩
#define HSPW (30-1)
#define HBPD (38-1)
#define HFPD (20-1)
////显示尺寸
#define LINEVAL (LCD_HEIGHT-1)
#define HOZVAL (LCD_WIDTH-1)

//for LCDCON1
#define CLKVAL_TFT 6//设置时钟信号
#define MVAL_USED 0//
#define PNRMODE_TFT 3 //TFT型LCD
#define BPPMODE_TFT 13 //24位TFT型LCD

//for LCDCON5
#define BPP24BL 0//32位数据表示24位颜色值时，低位数据有效，高8位无效
#define INVVCLK 0//像素值在VCLK下降沿有效
#define INVVLINE 1//翻转HSYNC信号
#define INVVFRAME 1//翻转VSYNC信号
#define INVVD 0//正常VD信号极性
#define INVVDEN 0//正常VDEN信号极性
#define PWREN 1//使能PWREN信号
#define BSWP 0//颜色数据字节不交换
#define HWSWP 0//颜色数据半字不交换
//定义显示缓存区
volatile U32 LCD_BUFFER[LCD_HEIGHT][LCD_WIDTH];
void delay(int a)
{
int k;
for(k=0;k<a;k++)
;
}

//绘制屏幕背景颜色，颜色为c
void Brush_Background( U32 c)
{
int x,y ;

for( y = 0 ; y < LCD_HEIGHT ; y++ )
{
for( x = 0 ; x < LCD_WIDTH ; x++ )
{
LCD_BUFFER[y][x] = c ;
}
}
}

//画实心圆，颜色为c。圆心在屏幕中心，半径为80个像素
void Draw_Circular(U32 c)
{
int x,y ;
int tempX,tempY;
int radius = 80;
int SquareOfR = radius*radius;

for( y = 0 ; y < LCD_HEIGHT ; y++ )
{
for( x = 0 ; x < LCD_WIDTH ; x++ )
{
if(y<=120 && x<=160)
{
tempY=120-y;
tempX=160-x;
}
else if(y<=120&& x>=160)
{
tempY=120-y;
tempX=x-160;
}
else if(y>=120&& x<=160)
{
tempY=y-120;
tempX=160-x;
}
else
{
tempY = y-120;
tempX = x-160;
}

if ((tempY*tempY+tempX*tempX)<=SquareOfR)
LCD_BUFFER[y][x] = c ;
}
}
}

void main(void)
{
//配置LCD相关引脚
rGPCUP= 0x00000000;
rGPCCON = 0xaaaa02a9;
rGPDUP = 0x00000000;
rGPDCON=0xaaaaaaaa;

rLCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(PNRMODE_TFT<<5)|(BPPMODE_TFT<<1)|0;
rLCDCON2=(VBPD<<24)|(LINEVAL<<14)|(VFPD<<6)|(VSPW);
rLCDCON3=(HBPD<<19)|(HOZVAL<<8)|(HFPD);
rLCDCON4=(HSPW);
rLCDCON5 = (BPP24BL<<12) | (INVVCLK<<10) | (INVVLINE<<9) | (INVVFRAME<<8) | (0<<7) | (INVVDEN<<6) | (PWREN<<3) |(BSWP<<1) | (HWSWP);

rLCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
rLCDSADDR2=M5D( ((U32)LCD_BUFFER+(LCD_WIDTH*LCD_HEIGHT*4))>>1 );
rLCDSADDR3=LCD_WIDTH*32/16;
rLCDINTMSK|=(3);//屏蔽LCD中断
rTCONSEL = 0;//无效LPC3480

rGPGUP=rGPGUP&(~(1<<4))|(1<<4);//GPG4上拉电阻无效
rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //设置GPG4为LCD_PWREN
rGPGDAT = rGPGDAT | (1<<4) ;//GPG4置1

rLCDCON5=rLCDCON5&(~(1<<3))|(1<<3);//有效PWREN信号
rLCDCON5=rLCDCON5&(~(1<<5))|(0<<5);//PWREN信号极性不翻转

rLCDCON1|=1;//LCD开启

while(1)
{
//黑色背景，白色实心圆
Brush_Background(0x0);
Draw_Circular(0xffffff);
delay(5000000);

//白色背景，黑色实心圆
Brush_Background(0xffffff);
Draw_Circular(0x0);
delay(5000000);

//蓝色背景，黄色实心
Brush_Background(0xff);
Draw_Circular(0xffff00);
delay(5000000);

//绿色背景，品色实心圆
Brush_Background(0xff00);
Draw_Circular(0xff00ff);
delay(5000000);

//红色背景，青色实心圆
Brush_Background(0xff0000);
Draw_Circular(0xffff);
delay(5000000);

//青色背景，红色实心圆
Brush_Background(0xffff);
Draw_Circular(0xff0000);
delay(5000000);

//品色背景，绿色实心圆
Brush_Background(0xff00ff);
Draw_Circular(0xff00);
delay(5000000);

//黄色背景，蓝色实心圆
Brush_Background(0xffff00);
Draw_Circular(0xff);
delay(5000000);
}
}
