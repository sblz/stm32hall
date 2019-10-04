#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

void parser(char *t)
{
	//send_string(slowo);  //echo
	switch(t[0])
	{
		case 'm':
			switch(t[1]){
				case '0': send_string("magnes wy³\n"); break;
				case 'N': send_string("magnes N\n"); break;
				case 'S': send_string("magnes S\n"); break;
				default: send_string("?\n");
			} break;
		case 's':
			switch(t[1]){
				case '0': send_string("swiatlo wy³\n"); break;
				case '1': send_string("swiatlo w³\n");  break;
				default: send_string("?\n");
			} break;
		default: send_string("?\n");
	}

//czyszczenie slowa:

	for(int b=0; b<sizeof(t); b++) t[b]='\0';

}
