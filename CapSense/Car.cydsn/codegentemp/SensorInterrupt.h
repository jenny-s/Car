/*******************************************************************************
* File Name: SensorInterrupt.h
* Version 1.60
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__SensorInterrupt_INTC_H__)
#define __SensorInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define SensorInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void SensorInterrupt_Start(void);
void SensorInterrupt_StartEx(cyisraddress address);
void SensorInterrupt_Stop(void) ;

CY_ISR_PROTO(SensorInterrupt_Interrupt);

void SensorInterrupt_SetVector(cyisraddress address) ;
cyisraddress SensorInterrupt_GetVector(void) ;

void SensorInterrupt_SetPriority(uint8 priority) ;
uint8 SensorInterrupt_GetPriority(void) ;

void SensorInterrupt_Enable(void) ;
uint8 SensorInterrupt_GetState(void) ;
void SensorInterrupt_Disable(void) ;

void SensorInterrupt_SetPending(void) ;
void SensorInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SensorInterrupt ISR. */
#define SensorInterrupt_INTC_VECTOR            ((reg16 *) SensorInterrupt__INTC_VECT)

/* Address of the SensorInterrupt ISR priority. */
#define SensorInterrupt_INTC_PRIOR             ((reg8 *) SensorInterrupt__INTC_PRIOR_REG)

/* Priority of the SensorInterrupt interrupt. */
#define SensorInterrupt_INTC_PRIOR_NUMBER      SensorInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SensorInterrupt interrupt. */
#define SensorInterrupt_INTC_SET_EN            ((reg8 *) SensorInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SensorInterrupt interrupt. */
#define SensorInterrupt_INTC_CLR_EN            ((reg8 *) SensorInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SensorInterrupt interrupt state to pending. */
#define SensorInterrupt_INTC_SET_PD            ((reg8 *) SensorInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SensorInterrupt interrupt. */
#define SensorInterrupt_INTC_CLR_PD            ((reg8 *) SensorInterrupt__INTC_CLR_PD_REG)



/* __SensorInterrupt_INTC_H__ */
#endif
