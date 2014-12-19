#ifndef __EEPROM_H
#define __EEPROM_H

#include "stm8s.h"
#include "stm8s_flash.h"

#define EP_HEADER_ADDR   (u8*)(0x4000)

u8 eeprom_unlock(void);
u8 eeprom_lock(void);
void read_config(void);
u8 filter_config(u8 code[]);
void write_config(u8 type, u8 code[]);
void clear_config();

#endif
