#include "eeprom.h"
#include "uart.h"

u8 set_code_count;
u8 set_code[10][3];
u8 set_code_type[10];

u8 eeprom_unlock(void)
{
    FLASH->DUKR=0xAE;
    FLASH->DUKR=0x56;
    FLASH->CR2=0x00;
    FLASH->NCR2=0xFF;
    return !(FLASH->IAPSR & 0x08);
}

u8 eeprom_lock(void)
{
    FLASH->IAPSR=(u8)(~0x08);
    return 1;  
}

void read_config(void)
{
    u8 *p = EP_HEADER_ADDR;
    u8 i,j;
    set_code_count = 0;
    while(*p !=0)
    {
        set_code_type[set_code_count]=*p;
        set_code[set_code_count][0]=*(p+1);
        set_code[set_code_count][1]=*(p+2);
        set_code[set_code_count][2]=*(p+3);
        set_code_count++;
        p+=4;
    }
    USART1_printf("- %d settings -\r\n", set_code_count);
    for (i=0;i<set_code_count;i++)
    {
        USART1_printf("%d : %d ",i,set_code_type[i]);
        for (j=0;j<24;j++)
            USART1_printf("%d",(set_code[i][j/8] & 1<< (7-j%8))?1:0);
        USART1_printf("\r\n");
    }
}

u8 filter_config(u8 code[])
{
    u8 i;
    for (i=0;i<set_code_count;i++)
    {
        if (set_code[i][0]==code[0] && set_code[i][1]==code[1] && set_code[i][2]==code[2])
            return set_code_type[i];
    }
    return 0;
}

void write_config(u8 type, u8 code[])
{
    u8 *p = EP_HEADER_ADDR;
    while (eeprom_unlock())
    ;
    p+= set_code_count*4;
    *p = type;
    while((FLASH->IAPSR & 0x04) == 0);
    *(p+1) = code[0];
    while((FLASH->IAPSR & 0x04) == 0);
    *(p+2) = code[1];
    while((FLASH->IAPSR & 0x04) == 0);
    *(p+3) = code[2];
    while((FLASH->IAPSR & 0x04) == 0);
    set_code_type[set_code_count]=type;
    set_code[set_code_count][0]=code[0];
    set_code[set_code_count][1]=code[1];
    set_code[set_code_count][2]=code[2];
    set_code_count++;
    eeprom_lock();
}

void clear_config()
{
    u8 *p = EP_HEADER_ADDR;
    u8 i;
    while (eeprom_unlock())
    ;
    set_code_count=0;
    for(i=0;i<40;i++)
    {
        *(p+i) = 0;
        while((FLASH->IAPSR & 0x04) == 0);
    }
    eeprom_lock();
}
