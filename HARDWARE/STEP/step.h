#ifndef __STEP_H
#define __STEP_H
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "myiic.h"
#include "pca9685.h"
#include "encoder.h"
#include "patrol.h"

void init_all(void);
void pca_setangle(int port, float angle);
void reset_duoji(void);
void fangxia_duoji(void);
void fangqiu(void);
void quqiu(void);
void quqiu_bufang(void);
void faqiu(void);
void cmd(char cmd);
void shibie(int lanqiu[], int pos);
void move_between_lines(int start, int end);
void get_a_qiu(int lanqiu[], int *linepos, int fangxia, int dir, int reverse);
void faqiudingwei(void);
void move_to_faqiu_and_back(int rotate, int start_rotate);
#endif
