#include "led.h"

void Led_Init(void)
{
    GPIO_Init(LED1_PORT, (GPIO_Pin_TypeDef)(LED1_PIN|LED2_PIN), GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_WriteHigh(LED1_PORT, LED1_PIN);
    GPIO_WriteHigh(LED2_PORT, LED2_PIN);
}

void Led_ON(u8 num)
{
    switch(num)
    {
        case 1:
        GPIO_WriteLow(LED1_PORT, LED1_PIN);
        break;
        case 2:
        GPIO_WriteLow(LED2_PORT, LED2_PIN);
        break;
    }
}
void Led_OFF(u8 num)
{
    switch(num)
    {
        case 1:
        GPIO_WriteHigh(LED1_PORT, LED1_PIN);
        break;
        case 2:
        GPIO_WriteHigh(LED2_PORT, LED2_PIN);
        break;
    }
}

void Led_REV(u8 num)
{
    switch(num)
    {
        case 1:
            GPIO_WriteReverse(LED1_PORT, LED1_PIN);
            break;
        case 2:
            GPIO_WriteReverse(LED2_PORT, LED2_PIN);
            break;
    }
}

void Led_Write(u8 num, u8 status)
{
    switch(num)
    {
        case 1:
            if(status)
                GPIO_WriteLow(LED1_PORT, LED1_PIN);
            else
                GPIO_WriteHigh(LED1_PORT, LED1_PIN);
            break;
        case 2:
            if(status)
                GPIO_WriteLow(LED2_PORT, LED2_PIN);
            else
                GPIO_WriteHigh(LED2_PORT, LED2_PIN);
            break;
    }

}
