#include "step.h"

#define INIT_7 117
#define ZHUANJIAO_7 60
void init_all()
{
	delay_init(); //��ʱ������ʼ��
	all_GPIO_DefaultInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart2_init(115200);								//���ڳ�ʼ��Ϊ115200
	KEY_Init();										//��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED_Init();
	TIM3_PWM_Init(899, 0);
	TIM4_PWM_Init(899, 0);
	STOP;
	EXTIX_Init();
	TIM5_Int_Init(500 - 1, 7200 - 1);
	USART_RX_STA = 0;

	IIC_Init();
	pca_write(pca_mode1, 0x0);
	pca_setfreq(50.0); //����PWMƵ��
	reset_duoji();
}

void pca_setangle(int port, float angle)
{
	pca_setpwm(port, 0, 2.2 * angle + 158);
}

void reset_duoji()
{
	pca_setpwm(12, 0, 40 * 2.2 + 158); //increase this will lower zuixiamian
	pca_setpwm(13, 0, 62 * 2.2 + 158); //increase this will higher zuixiamian
	pca_setpwm(14, 0, 62 * 2.2 + 158); //increase this will lower zuixiamian
	pca_setangle(7, INIT_7);
	pca_setangle(6, 110);
}

void fangxia_duoji()
{
	pca_setangle(12, 80);
	pca_setangle(13, 57);
	pca_setangle(14, 90);
	delay_ms(500);
	pca_setangle(12, 128);
	pca_setangle(13, 55);
	pca_setangle(14, 117);
}

void shengqi_duoji()
{
	pca_setangle(12, 70);
	pca_setangle(14, 135);
}

void fangqiu()
{
	pca_setangle(12, 37);
	pca_setangle(13, 65);
	pca_setangle(14, 58);
	delay_ms(300);
	pca_setangle(12, 34);
	pca_setangle(13, 70);
	pca_setangle(14, 54);
}

void faqiudingwei()
{
	move_left();
	delay_ms(400);
	walk_left_both_on_line();
	tiaozhengweizhi_zuoyou();
	all_motor(MOTOR_SPEED, 1, 0);
	delay_ms(500);
	STOP;
}

void quqiu()
{
	reset_duoji();
	pca_setpwm(15, 0, 20 * 2.2 + 158); //increase this will lower zuixiamian
	delay_ms(800);
	fangxia_duoji();
	delay_ms(800);
	pca_setangle(15, 60);
	delay_ms(800);
	shengqi_duoji();
	delay_ms(500);
	reset_duoji();
	delay_ms(800);
	fangqiu();
	delay_ms(500);
	pca_setpwm(15, 0, 20 * 2.2 + 158); //increase this will lower zuixiamian
}

void quqiu_bufang(void)
{
	reset_duoji();
	pca_setpwm(15, 0, 20 * 2.2 + 158); //increase this will lower zuixiamian
	delay_ms(800);
	fangxia_duoji();
	delay_ms(800);
	pca_setangle(15, 60);
	delay_ms(800);
	shengqi_duoji();
	delay_ms(500);
	reset_duoji();
	delay_ms(800);
}

void faqiu()
{
	int i = 0;
	reset_duoji();
	motor4(650, 1, 0);
	for (i = 0; i < 3; i++)
		delay_ms(1000);
	pca_setangle(7, INIT_7 - ZHUANJIAO_7);
	delay_ms(500);
	motor4(750, 1, 1);
	reset_duoji();
}

void faqiu_with_bianmaqi()
{
	int MOCALUN_SPEED = 41;
	int speed = 670;
	int time = 0;
	int i = 0;
	int zhunbeishangtang = 0;
	int shangtang = 10;
	int angle = INIT_7;

	reset_duoji();
	motor4(speed, 1, 0);
	for(i=0;i<2;i++)
	delay_ms(750);
	for (time = 0; time < 700; time++)
	{
		printf("%d   ", motor_speed0);
		
		if (motor_speed0 > MOCALUN_SPEED)
		{

			shangtang--;
			if (shangtang == 0)
				break;
		}
		delay_ms(10);
	}
	pca_setangle(7, INIT_7 - ZHUANJIAO_7 - 10);
	delay_ms(1000);
	delay_ms(1000);
	motor4(1000, 1, 1);
	reset_duoji();
}

void shibie(int lanqiu[], int pos)
{
	int i = 0;
	u8 qiu_state;
	USART_RX_STA = 0;
	printf("o");
	while (1)
	{
		if (USART_RX_STA != 0)
		{
			qiu_state = USART_RX_BUF[0];
			USART_RX_STA = 0;
			break;
		}
		delay_ms(50);
	}
	qiu_state -= 48;
	lanqiu[pos - 1] = qiu_state & 0x1;
	lanqiu[pos] = (qiu_state & 0x2) / 2;
	lanqiu[pos + 1] = (qiu_state & 0x4) / 4;
}

void move_between_lines(int start, int end)
{
	int i;
	if (start == end)
		return;
	if (start > end)
	{
		for (i = start; i > end; i--)
		{
			//tiaozhengweizhi();
			walk_right_both_on_line_and_stop_in_the_middle2();
			//tiaozhengweizhi();
		}
	}
	if (start < end)
	{
		for (i = start; i < end; i++)
		{
			//tiaozhengweizhi();
			walk_left_both_on_line_and_stop_in_th_middle2();
			//tiaozhengweizhi();
		}
	}
}

void get_a_qiu(int lanqiu[], int *linepos, int fangxia, int dir, int reverse)
{
	int i = 0;
	
	tiaozhengweizhi();
	if (dir)
	{
		for (i = 0; i < 9; i++)
		{
			if (lanqiu[i] == 1)
				break;
		}
	}
	else
	{
		for (i = 8; i >= 0; i--)
		{
			if (lanqiu[i] == 1)
				break;
		}
	}
	if (i > 8 || i < 0)
		return;
	if (reverse == 1 && i > 5)
		return;
	if (reverse == 1 && i == 5)
	{
		move_between_lines(*linepos, 4);
		walk_qianhou_on_line();
		tiaozhengweizhi();
		move_between_lines(4, 5);
		*linepos = 5;
	}
	else
	{

		if (i == 0)
		{
			move_between_lines(*linepos, 1);
			walk_qianhou_on_line();
			tiaozhengweizhi();
			move_between_lines(1, 0);
			*linepos = 0;
		}
		else
		{
			if (i == 8)
			{
				move_between_lines(*linepos, 7);
				walk_qianhou_on_line();
				tiaozhengweizhi();
				move_between_lines(7, 8);
				*linepos = 8;
			}
			else
			{
				{
					move_between_lines(*linepos, i);
					*linepos = i;
					walk_qianhou_on_line();
				}
			}
		}
	}
	tiaozhengweizhi();
	if (fangxia)
		quqiu();
	else
		quqiu_bufang();
	lanqiu[*linepos] = 2;
}

void move_to_faqiu_and_back(int rotate, int start_rotate)
{
	if (start_rotate)
		cross_a_line_back();

	else
	{
		cross_a_line_back();
		cross_a_line_back();
		cross_a_line_back();
	}
	//walk_qianhou_back_on_line_and_stop_in_the_middle();
	cross_jian_su_dai_back();
	walk_qianhou_back_on_line_and_stop_in_the_middle();
	faqiudingwei();
	faqiu_with_bianmaqi();
	fangqiu();
	delay_ms(500);
	pca_setpwm(15, 0, 20 * 2.2 + 158); //increase this will lower zuixiamian
	delay_ms(800);
	faqiu_with_bianmaqi();
	walk_qianhou_on_line_and_stop_in_the_middles();
	walk_right_both_on_line_and_stop_in_the_middle2();

	
	if (rotate)
	{
		tiaozhengweizhi();

		turn_left_until_line();
		turn_left();
		delay_ms(500);
		turn_left_until_line();
		tiaozhengweizhi();
		cross_a_line_back();
	cross_a_line_back();
	cross_jian_su_dai_back();
		walk_qianhou_back_on_line_and_stop_in_the_middle(); //到达取球区开始
	}
	else{
		
	cross_a_line();
	cross_a_line();

	cross_jian_su_dai();
		walk_qianhou_on_line_and_stop_in_the_middles(); //到达取球区开始
	}
	}

void all_progress1()
{
	int i = 0;
	for (i = 0; i < 4; i++)
		cross_a_line();
	walk_qianhou_on_line_and_stop_in_the_middles();
	move_left();
	delay_ms(700);
	for (i = 0; i < 2; i++)
		cross_a_line_left(); //此时到达发球区
	walk_left_both_on_line_and_stop_in_th_middle2();
	//--------
	cross_a_line();
	cross_a_line();
	cross_jian_su_dai();
	walk_qianhou_on_line_and_stop_in_the_middles(); //到达取球区开始
}

void all_progress2()
{
	int lanqiu1[20] = {0}; //0 未识别 1 篮球 2 不是篮球
	int lanqiu2[9] = {0};
	int linepos = 0;
	int have_qiu = 0;
	int i = 0;
	//	goto mystart;
	tiaozhengweizhi();
	move_between_lines(-1, 1);
	tiaozhengweizhi();
	linepos = 1;
	shibie(lanqiu1, linepos);
	move_between_lines(1, 4);
	tiaozhengweizhi();
	linepos = 4;
	shibie(lanqiu1, linepos);
	move_between_lines(4, 7);
	tiaozhengweizhi();
	linepos = 7;
	shibie(lanqiu1, linepos);
	for (i = 0; i < 9; i++)
	{
		printf("%d*\n", lanqiu1[i]);
	}
	cross_a_line();
	for (i = 0; i < 3; i++)
		walk_qianhou_on_line(); //识别完球，撞墙定位
	tiaozhengweizhi();
	get_a_qiu(lanqiu1, &linepos, 1, 0, 0);
	get_a_qiu(lanqiu1, &linepos, 0, 0, 0);

	move_between_lines(linepos, -1);
	tiaozhengweizhi();
	while (1)
	{
		have_qiu = 0;
		for (i = 0; i < 9; i++)
			if (lanqiu1[i] == 1)
				have_qiu = 1;
		if (have_qiu == 0)
			break;
		move_to_faqiu_and_back(0, 0);
		tiaozhengweizhi();
		move_between_lines(-1, 1);
		tiaozhengweizhi();
		linepos = 1;
		cross_a_line();
		for (i = 0; i < 3; i++)
			walk_qianhou_on_line(); //识别完球，撞墙定位

		get_a_qiu(lanqiu1, &linepos, 1, 0, 0);
		get_a_qiu(lanqiu1, &linepos, 0, 0, 0);
		move_between_lines(linepos, -1);
		tiaozhengweizhi();
	}
	move_to_faqiu_and_back(1, 0);

	//mystart:
	linepos = 6;
	tiaozhengweizhi();
	move_between_lines(6, 4);
	tiaozhengweizhi();
	linepos = 4;
	shibie(lanqiu2, linepos);
	move_between_lines(4, 1);
	tiaozhengweizhi();
	linepos = 1;
	shibie(lanqiu2, linepos);
	cross_a_line();
	for (i = 0; i < 3; i++)
		walk_qianhou_on_line(); //识别完球，撞墙定位

	get_a_qiu(lanqiu2, &linepos, 1, 1, 1);
	get_a_qiu(lanqiu2, &linepos, 0, 1, 1);

	for (i = 0; i < 9; i++)
		printf("%d ", lanqiu2[i]);
	move_between_lines(linepos, 6);
	tiaozhengweizhi();
	tiaozhengweizhi();
	turn_left_until_line();
	tiaozhengweizhi();
	while (1)
	{
		have_qiu = 0;
		for (i = 0; i < 6; i++)
		{
			if (lanqiu2[i] == 1)
				have_qiu = 1;
		}
		if (have_qiu == 0)
			break;
		move_to_faqiu_and_back(1, 1);
		linepos = 6;
		tiaozhengweizhi();
		move_between_lines(6, 4);
		tiaozhengweizhi();
		linepos = 4;

		cross_a_line();
		for (i = 0; i < 3; i++)
			walk_qianhou_on_line(); //识别完球，撞墙定位

		get_a_qiu(lanqiu2, &linepos, 1, 1, 1);
		get_a_qiu(lanqiu2, &linepos, 0, 1, 1);

		for (i = 0; i < 9; i++)
			printf("%d ", lanqiu2[i]);
		move_between_lines(linepos, 6);
		tiaozhengweizhi();
		turn_left_until_line();
		tiaozhengweizhi();
	}
	move_to_faqiu_and_back(1, 1);
	STOP;
}

void send_data(u8 message)
{
	USART_SendData(USART2, message);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET)
		;
}

void cmd(char cmd)
{
	switch (cmd)
	{
	case 'w':
	{
		LED1 = !LED1;
		all_motor(MOTOR_SPEED, 0, 1);
		delay_ms(1000);
		STOP;
		break;
	}
	case 's':
	{
		LED1 = !LED1;
		all_motor(MOTOR_SPEED, 1, 0);
		delay_ms(1000);
		STOP;
		break;
	}
	case 'z':
	{
		LED1 = !LED1;
		turn_left();
		delay_ms(300);
		STOP;
		break;
	}
	case 'c':
	{
		LED1 = !LED1;
		turn_right();
		delay_ms(300);
		STOP;
		break;
	}
	case 'd':
	{
		LED1 = !LED1;
		move_right();
		delay_ms(1000);
		STOP;
		break;
	}
	case 'a':
	{
		LED1 = !LED1;
		move_left();
		delay_ms(1000);
		STOP;
		break;
	}
	case 'e':
	{
		pca_setangle(7, 130);
		quqiu();
		break;
	}
	case 'f':
	{
		faqiu();
		break;
	}
	case 'g':
	{
		faqiu_with_bianmaqi();
		break;
	}
	case 'q':
	{
		reset_duoji();
		STOP;
		motor4(700, 0, 0);
		break;
	}
	case '1':
	{
		cross_a_line();
		break;
	}
	case '2':
	{
		cross_a_line_left();
		break;
	}
	case '5':
	{
		walk_qianhou_on_line();
		break;
	}
	case '6':
	{
		walk_qianhou_back_on_line();
		break;
	}
	case '7':
	{
		walk_right_both_on_line();
		break;
	}
	case '8':
	{
		walk_left_both_on_line();
		break;
	}
	case 'l':
	{
		all_progress1();

		break;
	}
	case 'k':
	{
		all_progress2();

		break;
	}
	case 'p':
	{
		while (1)
		{
			printf("%d %d %d %d %d %d\n", encoder_num0, motor_speed0, encoder_num1, motor_speed1, encoder_num2, motor_speed2);
			printf("%d %d %d %d\n", PFin(0), PFin(1), PFin(2), PFin(3));
			printf("%d %d %d %d\n", PFin(4), PFin(5), PFin(6), PFin(7));
			printf("%d %d %d %d\n", PFin(8), PFin(9), PFin(10), PFin(11));
			printf("%d %d %d %d\n", PFin(12), PFin(13), PFin(14), PFin(15));
			printf("--------------------\n");
			delay_ms(1000);
		}
		break;
	}
	}
}
