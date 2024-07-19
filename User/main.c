/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/07/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *I2C interface routine to operate EEPROM peripheral:
 *I2C1_SCL(PB10)\I2C1_SDA(PB11).
 *This example uses EEPROM for AT24Cxx series.
 *Steps:
 *READ EEPROM:Start + 0xA0 + 8bit Data Address + Start + 0xA1 + Read Data + Stop.
 *WRITE EERPOM:Start + 0xA0 + 8bit Data Address + Write Data + Stop.	 
 *
 */

#include "debug.h"
#include "ina226.h"
/**********************************************************************
*@Note:
AT24Cxx��

READ EEPROM��Start + 0xA0 + 8bit Data Address + Start + 0xA1 + Read Data + Stop.
WRITE EERPOM��Start + 0xA0 + 8bit Data Address + Write Data + Stop.
*******************************************************************************/
/* EERPOM DATA ADDRESS Length Definition */
#define Address_8bit  0
#define Address_16bit  1

/* EERPOM DATA ADDRESS Length Selection */
#define Address_Lenth   Address_8bit
//#define Address_Lenth   Address_16bit

/* Global define */
#define SIZE sizeof(TEXT_Buffer)

/* Global Variable */
const u8 TEXT_Buffer[] = {"CH32L10x I2C TEST"};


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void) {
/*
 *  计算公式：
 *  电流LSB = 预计最大电流 / 2 ^ 15       0.0001

    校准寄存器=0.00512/电流LSB/0.002      25600
    测量电流 = 电流寄存器值*电流LSB = 并联电压寄存器值*校准寄存器值/2048
 *  总线电压 = 总线电压寄存器值*1.25
 *  功率 = 功率寄存器值*25*电流LSB=电流*总线电压
 * */
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%lu\r\n", SystemCoreClock);
    printf("ChipID:%08lx\r\n", DBGMCU_GetCHIPID());
    INA226_Init();
    u16 mask_reg = 0x8000;//1000 0000 0000 0000电流上限警告
    INA226_Write2Byte(Mask_En_Reg,mask_reg);
    u16 alert_reg = 0x960;//警报上限值3A
    INA226_Write2Byte(Alert_Reg_limit,alert_reg);//

    while(1){
        u16 Bus_V = INA226_Read2Byte(Bus_V_Reg);
        u16 Shunt_V = INA226_Read2Byte(Shunt_V_Reg);
        u16 Current = INA226_Read2Byte(Current_Reg);
        u16 Power = INA226_Read2Byte(Power_Reg);
        u16 alert_flag = INA226_Read2Byte(Mask_En_Reg);

        printf("Bus_V  = %f mV\r\n",Bus_V*1.25);//9584
        printf("Shunt_V= %f mV\r\n", Shunt_V*0.0025);//8000
        printf("Current= %f  A\r\n", Current*0.0001);//10000
        printf("Power  = %f  W\r\n", Power*0.025);//4792
        printf("Alert_flag=%x\r\n",alert_flag);

    }

}
