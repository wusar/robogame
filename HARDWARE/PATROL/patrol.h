//functions about line patrol

#ifndef __PATROL_H
#define __PATROL_H
#include "delay.h"
#include "sys.h"
#include "timer.h"
#define STOP all_motor(2000, 0, 0)
#define MOTOR_SPEED 100
#define MOTOR_SPEED_SLOW 600
void turn_left(void);
void turn_right(void);
void move_right(void);
void move_left(void);
void turn_left_until_line(void);
void walk_left_both_on_line(void);
void walk_left_both_on_line_and_stop_in_th_middle(void);
void walk_left_both_on_line_and_stop_in_th_middle2(void);
void walk_right_both_on_line(void);
void walk_right_both_on_line_and_stop_in_the_middle2(void);
void walk_qianhou_on_line(void);
void walk_qianhou_on_line_and_stop_in_the_middles(void);
void walk_qianhou_back_on_line(void);
void walk_qianhou_back_on_line_and_stop_in_the_middle(void);
void cross_jian_su_dai(void);
void cross_jian_su_dai_back(void);
void cross_a_line(void);
void cross_a_line_back(void);
void cross_a_line_left(void);
void tiaozhengweizhi(void);
void tiaozhengweizhi_zuoyou(void);
#endif
