#include "MY_Config.h"
#include "GPIO.h"
#include "UART.h"
#include "Delay.h"
#include "Config.h"
#include "Switch.h"
#include "NVIC.h"
#include "Timer.h"
#include "STC8H_PWM.h"

#define PERIOD  ((MAIN_Fosc/1000)-1)
void MY_GPIO_Config() {
    GPIO_InitTypeDef init;
    /*init.Mode=GPIO_OUT_PP;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    init.Pin=GPIO_Pin_3;		//要设置的端口
    GPIO_Inilize(GPIO_P5,&init);*/
	
	  init.Mode=GPIO_OUT_PP;		//IO模式,  		GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    init.Pin=GPIO_Pin_1;		//要设置的端口
    GPIO_Inilize(GPIO_P0,&init);

}
void MY_UART_Config() {
    COMx_InitDefine init;
    init.UART_Mode=UART_8bit_BRTx;			//模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    init.UART_BRT_Use=BRT_Timer1;		//使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
    init.UART_BaudRate=115200;		//波特率, 	   一般 110 ~ 115200
    init.Morecommunicate=ENABLE;	//多机通讯允许, ENABLE,DISABLE
    init.UART_RxEnable=ENABLE;		//允许接收,   ENABLE,DISABLE
    init.BaudRateDouble=DISABLE;		//波特率加倍, ENABLE,DISABLE

    UART_Configuration(UART1,&init);

    UART1_SW(UART1_SW_P30_P31);

    NVIC_UART1_Init(ENABLE,Priority_0);


}




void MY_TX1_write2buff() {
    int i=1;
    if(COM1.RX_Cnt >0 && --COM1.RX_TimeOut==0) {
        for(i=0; i<COM1.RX_Cnt; i++) {
            TX1_write2buff(RX1_Buffer[i]);
        }
        COM1.RX_Cnt=0;
    }

    delay_ms(20);

}


void MY_Timer_Config() {

    TIM_InitTypeDef init;
    init.TIM_Mode=TIM_16BitAutoReload;		//工作模式,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
    init.TIM_ClkSource=TIM_CLOCK_1T;	//时钟源		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    init.TIM_ClkOut=DISABLE;		//可编程时钟输出,	ENABLE,DISABLE
    init.TIM_Value=65536UL - (MAIN_Fosc / 1000UL);;		//装载初值
    //init.TIM_PS;         //8位预分频器 (注意:并非所有系列都有此寄存器,详情请查看数据手册)
    init.TIM_Run=ENABLE;		//是否运行		ENABLE,DISABLE

    NVIC_Timer0_Init(ENABLE,Priority_0);

    Timer_Inilize(Timer0,&init);

}

void MY_PWM_Config(){
    PWMx_InitDefine init;
    init.PWM_Mode=CCMRn_PWM_MODE1;		//模式,   CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    init.PWM_Period=PERIOD;		//周期时间,   0~65535
    init.PWM_Duty=0;			//占空比时间, 0~Period
    init.PWM_DeadTime=255;	//死区发生器设置, 0~255
    init.PWM_EnoSelect=ENO6P;		//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    init.PWM_CEN_Enable=ENABLE;		//使能计数器, ENABLE,DISABLE
    init.PWM_MainOutEnable=ENABLE;//主输出使能,  ENABLE,DISABLE

    PWM_Configuration(PWMB,&init);
    PWM_Configuration(PWM6,&init);
    //中断
    NVIC_PWM_Init(PWMB,ENABLE,Priority_0);

    //切换引脚
    PWM6_SW(PWM6_SW_P01);
}