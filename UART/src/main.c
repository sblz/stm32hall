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




int main()
{
	init();
	konfiguracja();
	while(1){
	USART2_IRQHandler();
	}
	return 0;
}

