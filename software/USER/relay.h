#ifndef __RELAY_H
#define __RELAY_H

#define RELAY_PORT GPIOD
#define RELAY_PIN GPIO_PIN_3

void Relay_Init(void);
void Relay_ON(void);
void Relay_OFF(void);
void Relay_REV(void);

#endif
