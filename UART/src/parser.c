#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "init.h"
#include "parser.h"

char slowo[120] = {0};
int i = 0;

/*
void send_char(char c);
void send_string(const char* s);
void USART2_IRQHandler();
*/

extern uint32_t timer_ms;

/*void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

       timer_ms--;
    }
}
*/

void TIM2_IRQHandler()
{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
			{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
				timer_ms--;
			}
	}



void delay(int time)
{
	timer_ms = time;
	while (timer_ms){}
}


void konfiguracja()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w prawo
	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_11);
		delay(1);
		GPIO_ResetBits(GPIOC, GPIO_Pin_11);
		delay(20);
	}
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_11);
		delay(1);
		GPIO_ResetBits(GPIOC, GPIO_Pin_11);
		delay(50);
	}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
	GPIO_SetBits(GPIOA, GPIO_Pin_13);
		delay(1000);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(100);
		}
		GPIO_ResetBits(GPIOA, GPIO_Pin_13);
		GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	pozycja = '0';
	send_string("magnes wy³\n");
}

void jedz_z_S_do_0()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_2); // ustaw kierunek w lewo
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0) //sprawdz czujnik prawy S
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(50);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(200);
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
			delay(50);
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
			delay(15);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(50);
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
			delay(50);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(200);
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
			delay(50);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(200);
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
			delay(50);
		}
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);
			delay(200);
		}
		GPIO_ResetBits(GPIOC, GPIO_Pin_10);
		pozycja = 'S';

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

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy³¹cz przekaŸnik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);

}

void parser()
{
	if(slowo[i-1]=='\n'||slowo[i-1]=='\r')
	{
		send_string("parser(");
		send_string(slowo);
		send_string(")\n");
		switch(slowo[0])
		{
			case 'm':
				switch(slowo[1]){
					case '0':
						send_string(">>m0\n");
						if(pozycja=='S')
						{
							jedz_z_S_do_0();
							send_string("magnes wy³\n");
						}
						else if(pozycja=='N')
						{
							jedz_z_N_do_0();
							send_string("magnes wy³\n");
						}
						else
						{
							jedz_z_N_do_S();
							jedz_z_S_do_0();
							send_string("magnes wy³\n");
						}
						break;
					case 'N':
						send_string(">>mN\n");
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
							jedz_z_0_do_N();
							send_string("magnes N\n");
						}
						break;
					case 'S':
						send_string(">>mS\n");
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
							jedz_z_0_do_S();
							send_string("magnes S\n");
						}
						break;
					default: send_string("?\n");
				} break;
			case 's':
				switch(slowo[1]){
					case '0':
						//funkcja wy³¹cz œwiat³o
						send_string("swiatlo wy³\n");
						break;
					case '1':
						//funkcja w³¹cz œwiat³o
						send_string("swiatlo w³\n");
						break;
					default: send_string("?\n");
				} break;
	/*		case 'p':
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
	*/
		}



//czyszczenie slowa:

	for(int b=0; b<sizeof(slowo); b++) slowo[b]='\0';
	i=0;

	}
}

void USART2_IRQHandler()
{
	char c = USART_ReceiveData(USART2);
	if(c) {slowo[i]=c; i++;}
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



