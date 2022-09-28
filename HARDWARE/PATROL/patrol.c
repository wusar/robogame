#include "patrol.h"
void turn_left()
{
	motor0(MOTOR_SPEED, 1, 0);
	motor1(MOTOR_SPEED, 0, 1);
	motor2(MOTOR_SPEED, 0, 1);
	motor3(MOTOR_SPEED, 1, 0);
}

void turn_right()
{
	motor0(MOTOR_SPEED, 0, 1);
	motor1(MOTOR_SPEED, 1, 0);
	motor2(MOTOR_SPEED, 1, 0);
	motor3(MOTOR_SPEED, 0, 1);
}

void turn_left_until_line()
{
	int on_line = 0;
	
	motor0(MOTOR_SPEED, 1, 0);
	motor1(MOTOR_SPEED, 0, 1);
	motor2(MOTOR_SPEED, 0, 1);
	motor3(MOTOR_SPEED, 1, 0);
	delay_ms(500);
	while (1)
	{
		if (PGin(2) == 1)
		{
			STOP;
			break;
		}
		delay_ms(5);
	}
	
}

void move_right()
{
	motor0(MOTOR_SPEED, 0, 1);
	motor1(MOTOR_SPEED, 1, 0);
	motor2(MOTOR_SPEED, 0, 1);
	motor3(MOTOR_SPEED, 1, 0);
}

void move_left()
{
	motor0(MOTOR_SPEED, 1, 0);
	motor1(MOTOR_SPEED, 0, 1);
	motor2(MOTOR_SPEED, 1, 0);
	motor3(MOTOR_SPEED, 0, 1);
}

void walk_left_both_on_line()
{
	int count = 0;
	while (count < 450)
	{
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED, 1, 0);
				//motor1(600, 0, 1);
				//motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 0, 1);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					all_motor(1000, 0, 0);
					return;
				}
			}
		}
		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(600, 0, 1);
				motor1(MOTOR_SPEED, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 1, 0);
				//motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{

					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED_SLOW, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(600, 1, 0);
				}
				else
				{
					all_motor(1000, 0, 0);
					return;
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_left_both_on_line_and_stop_in_th_middle()
{
	int count = 0;
	while (count < 2000)
	{
		if (PGin(4) == 1)
		{
			STOP;
			return;
		}
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED, 1, 0);
				//motor1(600, 0, 1);
				//motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 0, 1);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}
		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(600, 0, 1);
				motor1(MOTOR_SPEED, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 1, 0);
				//motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{

					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED_SLOW, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(600, 1, 0);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_left_both_on_line_and_stop_in_th_middle2()
{
	//	walk_left_both_on_line();
	//	move_left();
	//	delay_ms(400);
	int count = 0;
	int on_the_line = 0;

	while (count < 2000)
	{
		if (PGin(2) == 1&&count>30)
			on_the_line = 1;
		if (on_the_line == 1)
		{
			if (PGin(3) == 1)
			{
				STOP;
				return;
			}
		}
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED, 1, 0);
				//motor1(600, 0, 1);
				//motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 0, 1);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}

		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(600, 0, 1);
				motor1(MOTOR_SPEED, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 1, 0);
				//motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{

					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED_SLOW, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(600, 1, 0);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_right_both_on_line()
{
	int count = 0;
	while (count < 300)
	{
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 0, 1);
				//motor1(MOTOR_SPEED, 0, 1);
				//motor2(600, 1, 0);
				motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED, 0, 1);
					//motor1(600, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED_SLOW, 1, 0);
				}
				else
				{
					all_motor(1000, 0, 0);
					return;
				}
			}
		}
		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 1, 0);
			motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 1, 0);
				motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{
					//motor0(600, 0, 1);
					motor1(MOTOR_SPEED, 1, 0);
					motor2(MOTOR_SPEED_SLOW, 0, 1);
					//motor3(MOTOR_SPEED, 1, 0);
				}
				else
				{
					all_motor(1000, 0, 0);
					return;
				}
			}
		}
		delay_ms(10);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_right_both_on_line_and_stop_in_the_middle2()
{
	int count = 0;
	int on_the_line = 0;
	while (count < 800)
	{
		if (PGin(5) == 1&&count>30)
			on_the_line = 1;
		if (on_the_line == 1)
		{
			if (PGin(3) == 1)
			{
				STOP;
				return;
			}
		}
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 0, 1);
				//motor1(MOTOR_SPEED, 0, 1);
				//motor2(600, 1, 0);
				motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED, 0, 1);
					//motor1(600, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED_SLOW, 1, 0);
				}
				else
				{
					motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}
		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 1, 0);
			motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 1, 0);
				motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{
					//motor0(600, 0, 1);
					motor1(MOTOR_SPEED, 1, 0);
					motor2(MOTOR_SPEED_SLOW, 0, 1);
					//motor3(MOTOR_SPEED, 1, 0);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 1, 0);
					motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}
		delay_ms(10);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_qianhou_on_line()
{
	int count = 0;
	while (count < 70)
	{									   //11??
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 0, 1);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 0, 1);
				motor3(MOTOR_SPEED, 0, 1);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED_SLOW, 0, 1);
				}
				else
				{
					delay_ms(10);
					if (PFin(8) == 1 && PFin(11) == 1)

					{
						all_motor(MOTOR_SPEED, 0, 0);
						return;
					}
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 0, 1);

				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					delay_ms(1);
					if (PGin(2) == 1 && PGin(5) == 1)
					{
						all_motor(1000, 0, 0);
						return;
					}
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_qianhou_on_line_and_stop_in_the_middles()
{
	int count = 0;
	while (count < 2000)
	{ //11??
		if (PFin(12) == 1)
		{
			all_motor(MOTOR_SPEED, 0, 0);
			return;
		}
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 0, 1);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 0, 1);
				motor3(MOTOR_SPEED, 0, 1);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED_SLOW, 0, 1);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 0, 1);

				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_qianhou_back_on_line()
{
	int count = 0;
	while (count < 2000)
	{									   //11??
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 1, 0);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					motor2(MOTOR_SPEED_SLOW, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
				}
				else
				{
					all_motor(MOTOR_SPEED, 0, 0);
					return;
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			motor1(MOTOR_SPEED, 1, 0);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 1, 0);
				motor1(MOTOR_SPEED, 1, 0);
				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED_SLOW, 1, 0);

					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					all_motor(1000, 0, 0);
					return;
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void walk_qianhou_back_on_line_and_stop_in_the_middle(void)
{
	int count = 0;
	while (count < 2000)
	{ //11??
		if (PFin(13) == 1)
		{
			all_motor(MOTOR_SPEED, 0, 0);
			return;
		}
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 1, 0);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					motor2(MOTOR_SPEED_SLOW, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			motor1(MOTOR_SPEED, 1, 0);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 1, 0);
				motor1(MOTOR_SPEED, 1, 0);
				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED_SLOW, 1, 0);

					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED, 1, 0);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void cross_jian_su_dai()
{
	int count = 0;
	while (count < 1300)
	{									   //11??
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED + 00, 0, 1);
			motor3(MOTOR_SPEED + 00, 0, 1);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 0, 1);
				motor3(MOTOR_SPEED, 0, 1);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED_SLOW, 0, 1);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 0, 1);

				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void cross_jian_su_dai_back(void)
{

	int count = 0;
	while (count < 1300)
	{									   //11??
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 1, 0);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					motor2(MOTOR_SPEED_SLOW, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			motor1(MOTOR_SPEED, 1, 0);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 1, 0);
				motor1(MOTOR_SPEED, 1, 0);
				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED_SLOW, 1, 0);

					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED, 1, 0);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void cross_a_line()
{
	//	walk_qianhou_on_line();
	//	all_motor(MOTOR_SPEED, 0, 1);
	//	delay_ms(400);
	int count = 0;
	int on_the_line1 = 0;
	int on_the_line2 = 0;

	while (count < 1600)
	{
		if (on_the_line1 == 1)
		{
			if (PFin(8) == 0 || PFin(11) == 0)
			{
				STOP;
				return;
			}
		}
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 0, 1);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 0, 1);
				motor3(MOTOR_SPEED, 0, 1);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED_SLOW, 0, 1);
				}
				else
				{
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED, 0, 1);
					delay_ms(3);
					if (PFin(8) == 1 && PFin(11) == 1)
						on_the_line1 = 1;
				}
			}
		}

		if (on_the_line2 == 1)
		{
			if (PGin(2) == 0 || PGin(5) == 0)
			{
				STOP;
				return;
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED_SLOW, 0, 1);

				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
					delay_ms(3);
					if (PGin(2) == 1 && PGin(5) == 1)
						on_the_line2 = 1;
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void cross_a_line_back()
{
	int count = 0;
	int on_the_line1 = 0;
	int on_the_line2 = 0;

	while (count < 2000)
	{ //11??
		if (on_the_line1 == 1)
		{
			if (PFin(8) == 0 || PFin(11) == 0)
			{
				STOP;
				return;
			}
		}
		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 1, 0);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					motor2(MOTOR_SPEED_SLOW, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 1, 0);
					on_the_line1 = 1;
				}
			}
		}
		if (on_the_line2 == 1)
		{
			if (PGin(2) == 0 || PGin(5) == 0)
			{
				STOP;
				return;
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			motor1(MOTOR_SPEED, 1, 0);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED_SLOW, 1, 0);
				motor1(MOTOR_SPEED, 1, 0);
				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED_SLOW, 1, 0);

					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED, 1, 0);
					//motor2(MOTOR_SPEED, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
					on_the_line2 = 1;
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void cross_a_line_left()
{
	//	walk_left_both_on_line();
	//	move_left();
	//	delay_ms(400);
	int count = 0;
	int on_the_line1 = 0;
	int on_the_line2 = 0;

	while (count < 2000)
	{
		if (on_the_line1 == 1)
		{
			if (PFin(12) == 0 || PFin(15) == 0)
			{
				STOP;
				return;
			}
		}
		if (PFin(12) == 0 && PFin(15) == 0) //??
		{
			motor0(MOTOR_SPEED, 1, 0);
			//motor1(MOTOR_SPEED, 0, 1);
			//motor2(MOTOR_SPEED, 1, 0);
			motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PFin(12) == 0 && PFin(15) == 1)
			{
				motor0(MOTOR_SPEED, 1, 0);
				//motor1(600, 0, 1);
				//motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED_SLOW, 0, 1);
			}
			else
			{
				if (PFin(12) == 1 && PFin(15) == 0)
				{
					motor0(MOTOR_SPEED_SLOW, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 1, 0);
					//motor1(MOTOR_SPEED, 0, 1);
					//motor2(MOTOR_SPEED, 1, 0);
					motor3(MOTOR_SPEED, 0, 1);
					on_the_line1 = 1;
				}
			}
		}

		if (on_the_line2 == 1)
		{
			if (PGin(0) == 0 || PFin(7) == 0)
			{
				STOP;
				return;
			}
		}
		if (PGin(0) == 0 && PFin(7) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 1, 0);
			//motor3(MOTOR_SPEED, 1, 0);
		}
		else
		{
			if (PGin(0) == 0 && PFin(7) == 1)
			{
				//motor0(600, 0, 1);
				motor1(MOTOR_SPEED, 0, 1);
				motor2(MOTOR_SPEED_SLOW, 1, 0);
				//motor3(MOTOR_SPEED, 1, 0);
			}
			else
			{
				if (PGin(0) == 1 && PFin(7) == 0)
				{

					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED_SLOW, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(600, 1, 0);
				}
				else
				{
					//motor0(MOTOR_SPEED, 0, 1);
					motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 1, 0);
					//motor3(MOTOR_SPEED, 1, 0);
					on_the_line2 = 1;
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void tiaozhengweizhi()
{
	int count = 0;
	while (count < 200)
	{

		if (PFin(8) == 0 && PFin(11) == 0) //??
		{
			//motor0(MOTOR_SPEED, 0, 1);
			//motor1(MOTOR_SPEED, 0, 1);
			motor2(MOTOR_SPEED, 0, 0);
			motor3(MOTOR_SPEED, 0, 0);
		}
		else
		{
			if (PFin(8) == 0 && PFin(11) == 1)
			{
				//motor0(MOTOR_SPEED, 0, 1);
				//motor1(600, 0, 1);
				motor2(MOTOR_SPEED, 1, 0);
				motor3(MOTOR_SPEED, 0, 1);
			}
			else
			{
				if (PFin(8) == 1 && PFin(11) == 0)
				{
					//	motor0(600, 0, 1);
					//motor1(MOTOR_SPEED, 0, 1);
					motor2(MOTOR_SPEED, 0, 1);
					motor3(MOTOR_SPEED, 1, 0);
				}
				else
				{
					motor2(MOTOR_SPEED, 0, 0);
					motor3(MOTOR_SPEED, 0, 0);
				}
			}
		}

		if (PGin(2) == 0 && PGin(5) == 0) //??
		{
			motor0(MOTOR_SPEED, 0, 0);
			motor1(MOTOR_SPEED, 0, 0);
			//motor2(MOTOR_SPEED, 0, 1);
			//motor3(MOTOR_SPEED, 0, 1);
		}
		else
		{
			if (PGin(2) == 0 && PGin(5) == 1)
			{
				motor0(MOTOR_SPEED, 0, 1);
				motor1(MOTOR_SPEED, 1, 0);

				//motor2(MOTOR_SPEED, 0, 1);
				//motor3(600, 0, 1);
			}
			else
			{
				if (PGin(2) == 1 && PGin(5) == 0)
				{
					motor0(MOTOR_SPEED, 1, 0);
					motor1(MOTOR_SPEED, 0, 1);
					//motor2(600, 0, 1);
					//motor3(MOTOR_SPEED, 0, 1);
				}
				else
				{
					motor0(MOTOR_SPEED, 0, 0);
					motor1(MOTOR_SPEED, 0, 0);
				}
			}
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}

void tiaozhengweizhi_zuoyou()
{
	int count = 0;
	while (count < 400)
	{
		if (PFin(12))
		{
			all_motor(MOTOR_SPEED, 0, 1);
		}
		else if (PFin(15))
		{
			all_motor(MOTOR_SPEED, 1, 0);
		}
		else
		{
			STOP;
		}
		delay_ms(3);
		count++;
	}
	all_motor(1000, 0, 0);
}
