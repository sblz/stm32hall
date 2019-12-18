#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

void init()
{

	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	NVIC_InitTypeDef nvic;
	NVIC_InitTypeDef nvic2;
	EXTI_InitTypeDef exti;
	TIM_TimeBaseInitTypeDef tim;

	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);


	/*TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Prescaler = 6400 - 1;
	tim.TIM_Period = 100 - 1;
	TIM_TimeBaseInit(TIM2, &tim);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	nvic2.NVIC_IRQChannel = TIM2_IRQn;
	nvic2.NVIC_IRQChannelPreemptionPriority = 1;
	nvic2.NVIC_IRQChannelSubPriority = 2;
	nvic2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic2);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	nvic.NVIC_IRQChannel = USART2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	*/
	/*GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType =  GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	// Definicja czujnika
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	gpio.GPIO_Mode =  GPIO_Mode_OUT;
	gpio.GPIO_OType =  GPIO_OType_PP;
	GPIO_Init(GPIOC, &gpio);


	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_OType =  GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType =  GPIO_OType_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOC, &gpio);

	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);
	*/

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

	  SysTick_Config(SystemCoreClock / 1000);

	 /* TIM_TimeBaseStructInit(&tim);
	  tim.TIM_CounterMode = TIM_CounterMode_Up;
	  tim.TIM_Prescaler = 6400 - 1;
	  tim.TIM_Period = 100 - 1;
	  TIM_TimeBaseInit(TIM2, &tim);*/

	  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	  TIM_Cmd(TIM2, ENABLE);

	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line13;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	USART_StructInit(&uart);
	uart.USART_BaudRate = 115200;
	USART_Init(USART2, &uart);
	USART_Cmd(USART2, ENABLE);



	send_string("init\r\n");   //usunac?



}
