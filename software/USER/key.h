#ifndef __KEY_H
#define __KEY_H

#include "stm8s_gpio.h"
#include "stm8s_exti.h"

#define KEY_PORT GPIOB
#define KEY_EXTI_PORT EXTI_PORT_GPIOB
#define KEY_PIN GPIO_PIN_5

void Key_Init(void);

#endif
