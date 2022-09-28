#include "step.h"
int main(void)
{
	int i = 0;
	int lanqiu1[20]={0};//0 ??? 1 ?? 2 ????
	int linepos=0;
	init_all();
	//all_motor(0,0,1);
	//move_to_faqiu_and_back(1,1);
	//walk_right_both_on_line_and_stop_in_the_middle2();
	//walk_qianhou_on_line_and_stop_in_the_middles();
//	move_to_faqiu_and_back(1, 1);
	//faqiu_with_bianmaqi();
	all_progress1();
  all_progress2();
//	all_progress3();
	//move_between_lines(1,2);
	
	//move_between_lines(6,5);
	while (1)
	{
		//printf("stm32recv");
		if (USART_RX_STA != 0)
		{
			for (i = 0; i < (USART_RX_STA & 0x3fff); i++)
			{
				//printf("stm32recv:%c",USART_RX_BUF[i]);
				cmd(USART_RX_BUF[i]);
			}
			USART_RX_STA = 0;
		}
		delay_ms(50);
	}
}
