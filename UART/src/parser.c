#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "init.h"
#include "parser.h"

char slowo[120] = {0};
int i = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;

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
			delay(200);
		}
		GPIO_ResetBits(GPIOA, GPIO_Pin_13);
		GPIO_ResetBits(GPIOC, GPIO_Pin_12);
	pozycja = '0';
	send_string("konfiguracja zakoÒczona\r\n");
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
		send_string("Magnes wy≥πczony\r\n");
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
			delay(200);
		}*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = 'N';
	send_string("Magnes w pozycji N\r\n");
}

void jedz_z_0_do_N()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_2); // ustaw silnik w lewo
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0) //sprawdz czujnik lewy N
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			delay(1);
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
			delay(200);
		}
		*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
	pozycja = 'N';
	send_string("Magnes w pozycji N\r\n");
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
	send_string("Magnes w pozycji S\r\n");
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
			delay(50);
		}
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);
		pozycja = '0';
		send_string("Magnes wy≥πczony\r\n");
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
		send_string("Magnes w pozycji S\r\n");

}

void P0()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("AB\r\n");
}
void P1()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("BA\r\n");
}
void P2()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_14);
	GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("AD\r\n");
}
void P3()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_SetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("DA\r\n");
}
void P4()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("CB\r\n");
}
void P5()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("BC\r\n");
}
void P6()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_SetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("CD\r\n");
}
void P7()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_SetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("DC\r\n");
}
void P8()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("AC\r\n");
}
void P9()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_ResetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_ResetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("CA\r\n");
}

void PE()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_SetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("BD\r\n");
}
void PF()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_9); //k
	GPIO_SetBits(GPIOB, GPIO_Pin_14); //l
	GPIO_SetBits(GPIOC, GPIO_Pin_9); //m
	GPIO_SetBits(GPIOA, GPIO_Pin_1); //n

	GPIO_SetBits(GPIOA, GPIO_Pin_0); //wy≥πcz przekaünik P
	delay(1000);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	send_string("DB\r\n");
}
void check()
{
	//konfiguracja();
	jedz_z_0_do_N();
	jedz_z_N_do_0();
	jedz_z_0_do_S();
	jedz_z_S_do_0();
	jedz_z_0_do_N();
	jedz_z_N_do_S();
	jedz_z_S_do_N();
	konfiguracja();
	P0();
	delay(2000);
	P1();
	delay(2000);
	P2();
	delay(2000);
	P3();
	delay(2000);
	P4();
	delay(2000);
	P5();
	delay(2000);
	P6();
	delay(2000);
	P7();
	delay(2000);
	P8();
	delay(2000);
	P9();
	delay(2000);
	PE();
	delay(2000);
	PF();
	delay(2000);
	P0();
	delay(2000);
}

void parser()
{
	if(slowo[i-1]=='\n'||slowo[i-1]=='\r')
	{
		switch(slowo[0])
		{
			case 'c':
				check();
				send_string("Sprawdzanie zakoÒczone\n");
				break;

			case 'm':
				switch(slowo[1]){
					case '0':
						if(pozycja=='S')
						{
							jedz_z_S_do_0();
						}
						else if(pozycja=='N')
						{
							jedz_z_N_do_0();
						}
						else
						{
							jedz_z_N_do_S();
							jedz_z_S_do_0();
						}
						break;
					case 'N':
						if(pozycja=='0')
						{
							jedz_z_0_do_N();
						}
						else if(pozycja=='S')
						{
							jedz_z_S_do_N();
						}
						else
						{
							jedz_z_0_do_N();
						}
						break;
					case 'S':
						if(pozycja=='0')
						{
							jedz_z_0_do_S();
						}
						else if(pozycja=='N')
						{
							jedz_z_N_do_S();
						}
						else
						{
							jedz_z_0_do_S();
						}
						break;
					default: send_string("Nieznana komenda\r\n");
				} break;
			case 's':
				switch(slowo[1]){
					case '0':
						//funkcja wy≥πcz úwiat≥o
						send_string("swiatlo wy≥\r\n");
						break;
					case '1':
						//funkcja w≥πcz úwiat≥o
						send_string("swiatlo w≥\r\n");
						break;
					default: send_string("?\n");
				} break;
			case 'p':
				switch(slowo[1]){
					case '0':
						P0();
						break;
					case '1':
						P1();
						break;
					case '2':
						P2();
						break;
					case '3':
						P3();
						break;
					case '4':
						P4();
						break;
					case '5':
						P5();
						break;
					case '6':
						P6();
						break;
					case '7':
						P7();
						break;
					case '8':
						P8();
						break;
					case '9':
						P9();
						break;
					case 'E':
						PE();
						break;
					case 'F':
						PF();
						break;
				default: send_string("Komenda nie znana\r\n");
				}
			break;
			default: send_string("Komenda nie znana\r\n");
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
