/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "parser.h"
#include "init.h"

void send_char(char c);
void send_string(const char* s);
void USART2_IRQHandler();

char slowo[120] = {0};
int i = 0;


int main()
{
	init();
	for(;;){}
	return 0;
}

void USART2_IRQHandler()
{
	slowo[i] = USART_ReceiveData(USART2);
	if(slowo[i]=='\n') {parser(&slowo); i=-1;} //
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
