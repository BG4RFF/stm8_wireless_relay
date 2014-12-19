#ifndef __LED_H
#define __LED_H

#include "stm8s_gpio.h"

#define LED1_PORT GPIOC
#define LED1_PIN GPIO_PIN_4

#define LED2_PORT GPIOC
#define LED2_PIN GPIO_PIN_3

void Led_Init(void);
void Led_ON(u8 num);
void Led_OFF(u8 num);
void Led_REV(u8 num);
void Led_Write(u8 num, u8 status);

#endif
