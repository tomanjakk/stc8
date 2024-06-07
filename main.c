#include "GPIO.h"
#include "Delay.h"
#include "NVIC.h"
#include "UART.h"
#include "Switch.h"
#include "Config.h"
#include "STC8H_PWM.h"


#include "MY_Config.h"
	

#define PERIOD ((MAIN_Fosc/1000)-1)


int a=1;
int ba=1;
PWMx_Duty duty;

void main() {
EAXSFR();		/* ��չ�Ĵ�������ʹ�ܣ� ��д�� */
EA=1;
P01=1;
MY_GPIO_Config();
		
MY_PWM_Config();
	
	
	while(1){
        //�����percent�仯
        a += ba;
        if(a >= 100) {
            ba = -1;
        } else if(a <= 0) {
            ba = 1;
        }
        //3.2 ������ĳ�Ա��ֵ : 0 ~ PERIOD
        duty.PWM6_Duty = PERIOD *  a / 100;

        //3.3 ����PWM��ռ�ձ�
        UpdatePwm(PWM6, &duty);
				//printf("��ֵ�ǣ�%d\n",PERIOD *  a / 100);

        delay_ms(20);
	}
	
}