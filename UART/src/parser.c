#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "init.h"

volatile uint32_t timer_ms = 0;

void SysTick_Handler()
{
	 if (timer_ms)
	 {
		 timer_ms--;
	 }
}

void delay(int time)
{
	timer_ms = time;
	while (timer_ms) {};
}

void parser(char *t)
{
	//send_string(slowo);  //echo
	switch(t[0])
	{
		case 'm':
			switch(t[1]){
				case '0':
					//funkcja jedz do 0
					send_string("magnes wy≥\n");
					break;
				case 'N':
					// funkcja jedü do N
					send_string("magnes N\n");
					break;
				case 'S':
					//funkcja jedü do S
					send_string("magnes S\n");
					break;
				default: send_string("?\n");
			} break;
		case 's':
			switch(t[1]){
				case '0':
					//funkcja wy≥πcz úwiat≥o
					send_string("swiatlo wy≥\n");
					break;
				case '1':
					//funkcja w≥πcz úwiat≥o
					send_string("swiatlo w≥\n");
					break;
				default: send_string("?\n");
			} break;
		default: send_string("?\n");
	}

//czyszczenie slowa:

	for(int b=0; b<sizeof(t); b++) t[b]='\0';

}



void czujnik()
{
	 if (EXTI_GetITStatus(EXTI_Line13))
	 {
		 if (spr(GPIOC, GPIO_Pin_0) == 0)  // jesli przycisk jest przycisniety
		 {
			 GPIO_SetBits(GPIOC, GPIO_Pin_1);// zapal diode
		 }
	 	 else
	 	 {
	 		 GPIO_ResetBits(GPIOC, GPIO_Pin_1);//zagaú diode
	 	 }
	 EXTI_ClearITPendingBit(EXTI_Line13);
	 }
}
void jedzP()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_2);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
			delay(100);
			GPIO_ResetBits(GPIOC, GPIO_Pin_1);

			delay(100);
		}
		send_string("koniec\n");
}
void jedzL()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
			delay(100);
			GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			delay(100);
		}
}

/*void jedz(int kier)
{
	switch(kier)
	{
	case 0: for()
		void korok()


		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void TIM2_IRQHandler()

	{
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
				{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
					if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1))
						GPIO_ResetBits(GPIOC, GPIO_Pin_1);
					else
						GPIO_SetBits(GPIOC, GPIO_Pin_1);
				}
			else
			{
				GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			}
		}
	}
*/

