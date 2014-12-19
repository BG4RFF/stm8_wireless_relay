#include "key.h"

void Key_Init(void)
{
    GPIO_Init(KEY_PORT, KEY_PIN, GPIO_MODE_IN_PU_IT);
    EXTI_SetExtIntSensitivity(KEY_EXTI_PORT, EXTI_SENSITIVITY_FALL_ONLY);
}
