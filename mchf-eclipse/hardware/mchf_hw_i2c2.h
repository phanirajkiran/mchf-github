/*  -*-  mode: c; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4; coding: utf-8  -*-  */
/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014                            **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:                                                                     **
**  Description:                                                                   **
**  Last Modified:                                                                 **
**  Licence:		CC BY-NC-SA 3.0                                                **
************************************************************************************/

#ifndef __MCHF_HW_I2C2_H
#define __MCHF_HW_I2C2_H

#include "mchf_hw_i2c.h"

void 		mchf_hw_i2c2_init(void);

#define I2C2_FLAG_TIMEOUT               ((uint32_t)0x500)
#define I2C2_LONG_TIMEOUT               ((uint32_t)(300 * I2C2_FLAG_TIMEOUT))

#define I2C_FlagStatusOrReturn(BUS, FLAG, RETURN) { \
        uint32_t timeout = BUS##_FLAG_TIMEOUT;\
        while(I2C_GetFlagStatus(BUS, (FLAG)))\
        { if ((timeout--) == 0) { return (RETURN); } } }

#define I2C_EventCompleteOrReturn(BUS,EVENT, RETURN) { \
        uint32_t timeout = BUS##_LONG_TIMEOUT;\
        while(!I2C_CheckEvent(BUS, (EVENT)))\
        { if ((timeout--) == 0) { return (RETURN); } } }


#endif
