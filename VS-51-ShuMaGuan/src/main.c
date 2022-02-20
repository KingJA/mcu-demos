#include "mcs51/8052.h"
#define duansuo P2_6           //段锁
#define weisuo P2_7           //位锁
#define uint unsigned int          
#define uchar unsigned char 
#define MAIN_Fosc 11059200L //晶振频率，每秒         
uchar num;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay(uint ms);
void main()
{
    // 位选 控制显示几个数码管
    weisuo=1;
    P0=0xc0;
    weisuo=0;
  
    while(1){
        for ( num = 0; num < 16; num++)
        {
             // 段选 控制数码管显示什么数字
            duansuo=1;
            P0=table[num];//显示1 0x3f-0
            duansuo=0;
            delay(6000);
        }
        
    }
}

void delay(uint ms)
{
    unsigned int i;
    do
    {
        i = MAIN_Fosc / 1300000;
        while (--i)
            ;
    } while (--ms);
}