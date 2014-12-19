/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_clk.h"

#include "delay.h"
#include "led.h"
#include "relay.h"
#include "key.h"
#include "uart.h"
#include "tim1.h"
#include "intrinsics.h"
#include "eeprom.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


extern u8 RxBuffer[RxBufferSize];
extern u8 UART_RX_NUM;
	
extern	u16 hltime;
extern	u16 lltime;
extern	u16 tttime;	  
extern	u16 last_tttime;

extern	u8 recived_code1;
extern	u8 recived_code2;
extern	u8 recived_code3;
extern	u8 recived_code_count;
extern	u8 recived_sync;
extern u32 ctime;


extern u8 status, type;


int main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    /*!<Set High speed internal clock */
 

    Relay_Init();
    Led_Init();
    Key_Init();
    Tim1_Init();
    Uart_Init();
	

    UART1_SendString("Device Boot V1.0\r\n", sizeof("Device Boot V1.0\r\n"));
    recived_sync = 0;
    status = 1;
    Delay(0x0ffff);
    read_config();
    Delay(0x0ffff);
    __enable_interrupt(); 

    TIM1_Cmd(ENABLE);
	
	
    /* Infinite loop */
    while (1)
    {
        ctime ++;
        if(status==2)
            Led_Write(2, !((ctime>>13)%2));
        else if(status==3)
            Led_Write(2, !((ctime>>14)%2));
        else
            Led_Write(2, !((ctime>>13)%8));
    }
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
