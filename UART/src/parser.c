#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "init.h"


volatile uint32_t timer_ms = 0;

void send_char(char c);
void send_string(const char* s);
void USART2_IRQHandler();


char slowo[120] = {0};
int i = 0;

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


char pozycja;

void konfiguracja()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w prawo
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		delay(1000);
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = '0';
}
void jedz_z_S_do_0()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w lewo
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0) //sprawdz czujnik prawy S
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
		pozycja = '0';
}

void jedz_z_S_do_N()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w lewo
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0) // sprawdz czujnik lewy N
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		/*while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = 'N';
}

void jedz_z_0_do_N()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_2); // ustaw silnik w lewo
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0) //sprawdz czujnik lewy N
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		delay(1000);
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		/*while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = 'N';
}
void jedz_z_0_do_S()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // ustaw silnik w prawo
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = 'S';
}
void jedz_z_N_do_0()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w prawo
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		GPIO_ResetBits(GPIOC, GPIO_Pin_10);
		pozycja = '0';
}
void jedz_z_N_do_S()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w lewo
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		GPIO_ResetBits(GPIOC, GPIO_Pin_10);
		pozycja = 'S';

}

void RAB()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //wy≥πcz przekaünik L
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //wy≥πcz przekaünik N
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //wy≥πcz przekaünik M
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //wy≥πcz przekaünik K
	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
}
void RBA()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //wy≥πcz przekaünik L
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //wy≥πcz przekaünik N
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //wy≥πcz przekaünik M
	GPIO_SetBits(GPIOB, GPIO_Pin_9); //wy≥πcz przekaünik K
	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
}

void przelacz(char *k, char *l, char *m, char *n)
{
	if(k=='0') GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	else GPIO_SetBits(GPIOB, GPIO_Pin_9);
	if(l=='0') GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	else GPIO_SetBits(GPIOB, GPIO_Pin_14);
	if(m=='0') GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	else GPIO_SetBits(GPIOC, GPIO_Pin_9);
	if(n=='0') GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	else GPIO_SetBits(GPIOA, GPIO_Pin_1);

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);

}

void parser(char *t)
{
	//send_string(slowo);  //echo
	switch(t[0])
	{
		case 'm':
			switch(t[1]){
				case '0':
					if(pozycja=='S')
					{
						jedz_z_S_do_0();
						send_string("magnes wy≥\n");
					}
					else if(pozycja=='N')
					{
						jedz_z_N_do_0();
						send_string("magnes wy≥\n");
					}
					else
					{
						send_string("magnes wy≥\n");
					}
					break;
				case 'N':
					if(pozycja=='0')
					{
						jedz_z_0_do_N();
						send_string("magnes N\n");
					}
					else if(pozycja=='S')
					{
						jedz_z_S_do_N();
						send_string("magnes N\n");
					}
					else
					{
						send_string("magnes N\n");
					}
					break;
				case 'S':
					if(pozycja=='0')
					{
						jedz_z_0_do_S();
						send_string("magnes S\n");
					}
					else if(pozycja=='N')
					{
						jedz_z_N_do_S();
						send_string("magnes S\n");
					}
					else
					{
						send_string("magnes S\n");
					}
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
		//default: send_string("?\n");
		case 'p':
			if (t[1]=='A' && t[2]=='B')
			{
				przelacz('0','0','0','0');
			}
			else if (t[1]=='B' && t[2]=='A') przelacz('0','0','0','1');
			else if (t[1]=='A' && t[2]=='D') przelacz('0','0','1','0');
			else if (t[1]=='D' && t[2]=='A') przelacz('0','0','1','1');
			else if (t[1]=='C' && t[2]=='B') przelacz('0','1','0','0');
			else if (t[1]=='B' && t[2]=='C') przelacz('0','1','0','1');
			else if (t[1]=='C' && t[2]=='D') przelacz('0','1','1','0');
			else if (t[1]=='D' && t[2]=='C') przelacz('0','1','1','1');
			else if (t[1]=='A' && t[2]=='C') przelacz('1','0','0','0');
			else if (t[1]=='C' && t[2]=='A') przelacz('1','0','0','1');
			else if (t[1]=='B' && t[2]=='D') przelacz('1','1','1','0');
			else if (t[1]=='D' && t[2]=='B') przelacz('1','1','1','1');
		break;

	}



//czyszczenie slowa:

	for(int b=0; b<sizeof(t); b++) t[b]='\0';

}

void USART2_IRQHandler()
{
	slowo[i] = USART_ReceiveData(USART2);
	if(slowo[i]=='\n'||slowo[i]=='\r') {parser(&slowo); i=-1;} //
	i++;
}



void send_char(char c)
{
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

void send_string(const char* s)
{
	while (*s)
	send_char(*s++);
}



/*void TIM2_IRQHandler()

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

