#ifndef PARSER_H
#define PARSER_H
#include <stm32f4xx.h>

//static uint32_t timer_ms;

extern uint32_t timer_ms;
void parser();

void send_char(char c);
void send_string(const char* s);
void USART2_IRQHandler();

void konfiguracja();
void jedz_z_S_do_0();
void jedz_z_S_do_N();
void jedz_z_0_do_N();
void jedz_z_0_do_S();
void jedz_z_N_do_0();
void jedz_z_N_do_S();

char slowo[120];
int i;

//void SysTick_Handler();

void delay(int time);

char pozycja;



void przelacz();

void parser();








#endif
