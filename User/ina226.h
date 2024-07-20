//
// Created by 86180 on 2024/6/5.
//
#ifndef __INA226_H
#define __INA226_H
//#include "system_ch32l103.h"
#include "debug.h"

#define READ_ADDR                  0x80	 //A0=GND，A1=GND // R=1, W=0
#define WRITE_ADDR                 0x80

#define Config_Reg                 0x00
#define Shunt_V_Reg                0x01//并联电压
#define Bus_V_Reg                  0x02//总线电压
#define Power_Reg                  0x03//功率寄存器，值等 于 当 前 LSB编 程 值 的 25倍
#define Current_Reg                0x04
#define Calib_Reg                  0x05
#define Mask_En_Reg                0x06//控制使能警报，选用警报选项为电流
#define Alert_Reg_limit            0x07//警报
#define Man_ID_Reg                 0xFE  //0x5449
#define ID_Reg                     0xFF  //0x2260

#define calibrate_value            0x3200//25600

__attribute__((unused)) u8 INA226_ReadByte(u8 reg_addr);
u16 INA226_Read2Byte(u8 reg_addr) ;
u16 INA226I2C1_Read2Byte(u8 reg_addr) ;

__attribute__((unused)) void INA226_WriteByte(u8 reg_addr,u8 reg_data);
void INA226_Write2Byte(u8 reg_addr,u16 reg_data);
void INA226I2C1_Write2Byte(u8 reg_addr, u16 reg_data) ;
void INA226_Init(void);
void IIC_Init(u32 bound, u16 address) ;
#endif
