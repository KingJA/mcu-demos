#include "led_out.h"
#include "delay.h"

#define MAIN_Fosc 11059200L //晶振频率
#define LED1 P1_1           //输出1
#define LED2 P1_2           //输出2

unsigned char CYCLE;  //定义周期该数字X基准定时时间如果是10 则周期是10x 0.1ms
unsigned char PWM_ON; //定义高电平时间

void led_out()
{
    while (1)
    {
        LED1 = 0;
        LED2 = 1;
        delay_ms(100);
        LED1 = 1;
        LED2 = 0;
        delay_ms(100);
    }
}

void led_pwm_out()
{
    __bit ZFlag;
    TMOD |= 0x01; //定时器设置 0.1ms in 12M crystal
    TH0 = (65536 - 45872) / 256;
    TL0 = (65536 - 45872) % 256; //定时0.1mS
    IE = 0x82;                   //打开中断
    TR0 = 1;
    CYCLE = 50; // 时间可以调整这个是10调整8位PWM就是256步
    while (!ZFlag)
    {
        delay_ms(25); //延时时间，从一个亮度到下一个亮度的间隔时间，速度快就能看到连续效果
        PWM_ON++;     //这个使用较长延时，以便能看清楚变化过程
        if (PWM_ON == CYCLE)
        { //这个里可以添加其他程序😂如到最亮时候控制设备
            ZFlag = 1;
        }
    }
    while (ZFlag) //亮度递减同上，是个相反的过程
    {
        delay_ms(25); //延迟时间为20000*0.4=8000us
        PWM_ON--;
        if (PWM_ON == 0)
        {
            ZFlag = 0;
        }
    }
}

void ztim(void) __interrupt 1
{
    static unsigned char count;
    TH0 = (65536 - 100) / 256;
    TL0 = (65536 - 100) % 256; //定时0.1mS
    if (count == PWM_ON)
    {
        LED1 = 1;
        LED2 = 0; //灯灭
    }
    count++;
    if (count == CYCLE)
    {
        count = 0;
        if (PWM_ON != 0) //如果开启时间是0 保持原来状态
        {
            LED1 = 0;
            LED2 = 1; //灯灭
        }
    }
}