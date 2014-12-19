/**
  ******************************************************************************
  * @file    stm8s_it.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service 
  *          routine.
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
#include "stm8s_it.h"
#include "stm8s_uart1.h"

#include "delay.h"
#include "uart.h"
#include "tim1.h"
#include "key.h"
#include "led.h"
#include "relay.h"
#include "eeprom.h"

u16 hltime,lltime,tttime,last_tttime;
u8 recived_code[3];
u8 recived_code_count;
u8 recived_sync;
u8 status, type;

u32 ctime;
u32 lmtime;

u8 RxBuffer[RxBufferSize];
u8 UART_RX_NUM=0;


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy Interrupt routine
  * @par Parameters:
  * None
  * @retval
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt, 25)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*_COSMIC_*/

/**
  * @brief TRAP Interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Top Level Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TLI_IRQHandler, 0)

{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Clock Controller Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTA Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
    u32 keytime,keytime1;
    TIM1_ITConfig(TIM1_IT_CC2, DISABLE);
    Delay(0x01fff);

    keytime  = 0;
    keytime1 = 0;
    while(!GPIO_ReadInputPin(GPIOB,GPIO_PIN_5))
    {
        keytime1 ++;
		
        if (keytime1==5000)
        {
            keytime1 = 0;
            keytime ++;
        }

        if (keytime==30 || keytime==52 || keytime==56 || keytime==78 || keytime==82 || keytime==86 || keytime==120)
        {
            Led_ON(2);
        }
        else if (keytime==0 || keytime==32 || keytime==54 || keytime==58 || keytime==80 || keytime==84 || keytime==88 || keytime==150 )
        {
            Led_OFF(2);
        }
    }
	
    if (keytime>1 && keytime<20)
    {
        status = 1;  
        Relay_REV();                        // Reverse
    }
    else if (keytime>32 && keytime<52)      // no lock M
    {
        type = 1;
        status = 2;                         // set 1
        Relay_OFF();                        // Reverse
    }
    else if (keytime>58 && keytime<78)      // self lock T
    {
        type = 2;
        status = 2;                         // set 1
        Relay_OFF();                        // Reverse
    }
    else if (keytime>88 && keytime<108)     // inter lock L
    {
        type = 3;
        status = 2;                         // set 1
        Relay_OFF();                        // Reverse
    }
    else if (keytime>120 && keytime<150)
    {
        clear_config();                     // reset
    
    }
    Led_OFF(2);
    TIM1_ITConfig(TIM1_IT_CC2, ENABLE);
}

/**
  * @brief External Interrupt PORTC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined (STM8S903) || defined (STM8AF622x) 
/**
  * @brief External Interrupt PORTF Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x) */

#if defined (STM8S208) || defined (STM8AF52Ax)
/**
  * @brief CAN RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_RX_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief CAN TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_TX_IRQHandler, 9)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S208) || (STM8AF52Ax) */

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
    if(TIM1_GetFlagStatus(TIM1_FLAG_CC2))
    {
        TIM1_SetCounter(0x0000);
        TIM1_ClearITPendingBit(TIM1_IT_CC2);
        TIM1_ClearFlag(TIM1_FLAG_CC2);
        if (TIM1->CCER1 & TIM1_CCER1_CC2P)
        {
            hltime=TIM1_GetCapture2();
            TIM1->CCER1 &= ~TIM1_CCER1_CC2P;
            //if (recived_sync) USART1_printf("h %d  ",hltime);
        }
        else
        {
            lltime=TIM1_GetCapture2();
            TIM1->CCER1 |= TIM1_CCER1_CC2P;
            //if (recived_sync) USART1_printf("l %d\r\n",lltime);
            last_tttime = tttime;
            tttime = hltime+lltime;
            if (lmtime && ctime-lmtime>8000)
            {
                Relay_OFF();
                lmtime=0;
            }
            if (!recived_sync && hltime>2 && lltime>500 && hltime*34 >= lltime*19/20 && hltime*34 <= lltime*21/20)
            {
                recived_sync = 1;
                recived_code_count = 0;
                recived_code[0] = 0;
                recived_code[1] = 0;
                recived_code[2] = 0;
            }
            else if (recived_sync && hltime>2 && lltime>2)
            {
                if (recived_code_count==0 || (tttime >= last_tttime*19/20 && tttime <= last_tttime*21/20))
                {
                    if (lltime*3 >= hltime*4/5 && lltime*3 <= hltime*6/5)
                    {
                        recived_code[recived_code_count/8] |= 1<< (7-recived_code_count%8);
                        recived_code_count++;
                    }
                    else if (hltime*3 >= lltime*4/5 && hltime*3 <= lltime*6/5)
                    {
                        recived_code_count++;
                    }
                }
                else if (recived_code_count>=24 )
                {
                    u8 i;
                    for (i=0;i<24;i++)
                        USART1_printf("%d",(recived_code[i/8] & 1<< (7-i%8))?1:0);
                    USART1_printf("\r\n");
                
                    recived_sync = 0;
                    recived_code_count = 0;
				
                    u8 recived_type = filter_config(recived_code);
                    if (status == 1) //no set
                    {
                        switch (recived_type)
                        {
                            case 1:
                            Relay_ON();                             //ON
                            lmtime = ctime;
                            break;
                            case 2:
                            Relay_REV();                             //Reverse
                            lmtime = 0;
                            break;
                            case 3:
                            Relay_ON();                             //ON
                            lmtime = 0;
                            break;
                            case 4:
                            Relay_OFF();                             //OFF
                            lmtime = 0;
                            break;
                        }
                    }
                    else if (status == 2) //set-1
                    {
                        if (recived_type)
                            status = 1;
                        else
                        {
                            write_config(type,recived_code);
                            if(type==3)
                                status = 3;
                            else
                                status = 1;
                            Relay_ON();                             //Reverse
                        }
                    }
                    else if (status == 3) //set-2
                    {
                        if (recived_type)
                            status = 1;
                        else
                        {
                            write_config(4,recived_code);
                            status = 1;
                            Relay_OFF();						//Reverse
                        }
                    }
                    Delay(0x1ffff);
                    Delay(0x1ffff);
                }
                else
                    recived_sync = 0;
            }
        }
    }
}

#if defined (STM8S903) || defined (STM8AF622x)
/**
  * @brief Timer5 Update/Overflow/Break/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
 
/**
  * @brief Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

#else /* (STM8S208) || (STM8S207) || (STM8S105) || (STM8S103) || (STM8AF62Ax) || (STM8AF52Ax) || (STM8AF626x) */
/**
  * @brief Timer2 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x) */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8AF626x)
/**
  * @brief Timer3 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8S105) || (STM8AF62Ax) || (STM8AF52Ax) || (STM8AF626x) */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8S903)
/**
  * @brief UART1 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART1 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
    u8 Res;
    if(UART1_GetITStatus(UART1_IT_RXNE )!= RESET)  
    {/*接收中断(接收到的数据必须是0x0d 0x0a结尾)*/
        Res =UART1_ReceiveData8();
        /*(USART1->DR);读取接收到的数据,当读完数据后自动取消RXNE的中断标志位*/
        if(( UART_RX_NUM&0x80)==0)/*接收未完成*/
        {
            if( UART_RX_NUM&0x40)/*接收到了0x0d*/
            {
                if(Res!=0x0a) UART_RX_NUM=0;/*接收错误,重新开始*/
                else  UART_RX_NUM|=0x80;    /*接收完成了 */
            }
            else /*还没收到0X0D*/
            {
                if(Res==0x0d) UART_RX_NUM|=0x40;
                else
                {
                    RxBuffer[ UART_RX_NUM&0X3F] = Res;
                    UART_RX_NUM++;
                    if( UART_RX_NUM>63)
                        UART_RX_NUM=0;/*接收数据错误,重新开始接收*/
                }
            }
        }
    }
 }
#endif /* (STM8S208) || (STM8S207) || (STM8S103) || (STM8S903) || (STM8AF62Ax) || (STM8AF52Ax) */

#if defined(STM8AF622x)
/**
  * @brief UART4 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART4 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART4_RX_IRQHandler, 18)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8AF622x) */

/**
  * @brief I2C Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x)
/**
  * @brief UART2 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART2 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S105) || (STM8AF626x) */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief UART3 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART3 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8AF52Ax) || (STM8AF62Ax) */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief ADC2 interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(ADC2_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#else /* STM8S105 or STM8S103 or STM8S903 or STM8AF626x or STM8AF622x */
/**
  * @brief ADC1 interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
 INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8AF52Ax) || (STM8AF62Ax) */

#if defined (STM8S903) || defined (STM8AF622x)
/**
  * @brief Timer6 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#else /* STM8S208 or STM8S207 or STM8S105 or STM8S103 or STM8AF52Ax or STM8AF62Ax or STM8AF626x */
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x)*/

/**
  * @brief Eeprom EEC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/