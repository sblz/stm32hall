#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
//
//#define TM_DELAY_TIM            TIM2
//#define TM_DELAY_TIM_IRQ        TIM2_IRQn
//#define TM_DELAY_TIM_IRQ_HANDLER    TIM2_IRQHandler

void init()
{

	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef nvic;
	NVIC_InitTypeDef nvic2;
	EXTI_InitTypeDef exti;
	TIM_TimeBaseInitTypeDef tim;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);


	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType =  GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 9600;
	USART_Init(USART2, &uart);
	USART_Cmd(USART2, ENABLE);
	//
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);

	TIM_TimeBaseStructInit(&tim);
	tim.TIM_RepetitionCounter = 100;
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 100 - 1;
	tim.TIM_Period = 1000 - 1;
	TIM_TimeBaseInit(TIM2, &tim);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	 nvic2.NVIC_IRQChannel = TIM2_IRQn;
	 nvic2.NVIC_IRQChannelPreemptionPriority = 1;
	 nvic2.NVIC_IRQChannelSubPriority = 0;
	 nvic2.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&nvic2);

		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		nvic.NVIC_IRQChannel = USART2_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority = 2;
		nvic.NVIC_IRQChannelSubPriority = 0;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);

	GPIO_StructInit(&gpio);

	// deklaracja wyjœcia steruj¹cego tranzystora P
	 gpio.GPIO_Pin = GPIO_Pin_0;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOA, &gpio);

	 //deklaracja wyjœcia steruj¹cego do prze³¹cznika K1 L
	 gpio.GPIO_Pin = GPIO_Pin_14;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_OD;
	 gpio.GPIO_OType =  GPIO_PuPd_NOPULL;
	 GPIO_Init(GPIOB, &gpio);

	 //deklaracja wyjœcia steruj¹cego do prze³¹cznika K2 N
	 gpio.GPIO_Pin = GPIO_Pin_1;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOA, &gpio);

	 //deklaracja wyjœcia steruj¹cego do prze³¹cznika K3 M
	 gpio.GPIO_Pin = GPIO_Pin_9;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOC, &gpio);

	 //deklaracja wyjœcia steruj¹cego do prze³¹cznika K4 K
	 gpio.GPIO_Pin = GPIO_Pin_9;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOB, &gpio);

	 // deklaracja wyjœcia sterowania kierunkiem obrotu silnika
	 gpio.GPIO_Pin = GPIO_Pin_2;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOD, &gpio);

	 // w³¹czenie kroku silnika
	 gpio.GPIO_Pin = GPIO_Pin_11;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOC, &gpio);

	 // sterowanie krokiem silnika M0
	 gpio.GPIO_Pin = GPIO_Pin_10;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOC, &gpio);

	 // sterowanie krokiem silnika M1
	 gpio.GPIO_Pin = GPIO_Pin_12;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOC, &gpio);

	 // sterowanie krokiem silnika M2
	 /*GPIO_StructInit(&gpio);
	 gpio.GPIO_Pin = GPIO_Pin_13;
	 gpio.GPIO_Mode =  GPIO_Mode_OUT;
	 gpio.GPIO_OType =  GPIO_OType_PP;
	 GPIO_Init(GPIOA, &gpio);*/

	 // wyprowadzenie wejœciowe z czujnika 1
	  gpio.GPIO_Pin = GPIO_Pin_4;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOA, &gpio);

	  // wyprowadzenie wejœciowe z czujnika 2
	  gpio.GPIO_Pin = GPIO_Pin_0;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOB, &gpio);

	  // wyprowadzenie wejœciowe z czujnika 3
	  gpio.GPIO_Pin = GPIO_Pin_1;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOC, &gpio);

	  // wyprowadzenie wejœciowe z czujnika 4
	  gpio.GPIO_Pin = GPIO_Pin_0;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOC, &gpio);

	  // wyprowadzenie wejœciowe z czujnika 5
	  gpio.GPIO_Pin = GPIO_Pin_3;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOC, &gpio);

	  // wyprowadzenie wejœciowe z czujnika 6
	  gpio.GPIO_Pin = GPIO_Pin_2;
	  gpio.GPIO_Mode = GPIO_Mode_IN;
	  gpio.GPIO_OType =  GPIO_PuPd_UP;
	  GPIO_Init(GPIOC, &gpio);

	  //SysTick_Config(SystemCoreClock / 1000);

	send_string("init\r\n");   //usunac?



}
