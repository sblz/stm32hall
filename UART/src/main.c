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

extern uint32_t timer_ms = 0;



void SysTick_Handler()
{
	if (timer_ms)
	 {
		 timer_ms--;
	 }
}

int main()
{
	init();
	konfiguracja();
	while(1)
	{
		parser();
		delay(10);
	}
		delay(5000);
		jedz_z_0_do_S();
		delay(5000);
		jedz_z_S_do_N();

//	jedz_z_S_do_0();
//	jedz_z_0_do_N();
//	jedz_z_N_do_S();
//	jedz_z_S_do_N();
//	jedz_z_N_do_0();
	for(;;){}
	return 0;
}

