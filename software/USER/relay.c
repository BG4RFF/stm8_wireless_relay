#include "relay.h"
#include "led.h"

void Relay_Init(void)
{
    GPIO_Init(RELAY_PORT, RELAY_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_WriteLow(RELAY_PORT, RELAY_PIN);
}

void Relay_ON(void)
{
    GPIO_WriteHigh(RELAY_PORT, RELAY_PIN);
    Led_ON(1);
}

void Relay_OFF(void)
{
    GPIO_WriteLow(RELAY_PORT, RELAY_PIN);
    Led_OFF(1);
}

void Relay_REV(void)
{
    GPIO_WriteReverse(RELAY_PORT, RELAY_PIN);
    Led_REV(1);
}
