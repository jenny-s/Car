/*******************************************************************************
* File Name: LineInterrupt.h
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
#if !defined(__LineInterrupt_INTC_H__)
#define __LineInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define LineInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void LineInterrupt_Start(void);
void LineInterrupt_StartEx(cyisraddress address);
void LineInterrupt_Stop(void) ;

CY_ISR_PROTO(LineInterrupt_Interrupt);

void LineInterrupt_SetVector(cyisraddress address) ;
cyisraddress LineInterrupt_GetVector(void) ;

void LineInterrupt_SetPriority(uint8 priority) ;
uint8 LineInterrupt_GetPriority(void) ;

void LineInterrupt_Enable(void) ;
uint8 LineInterrupt_GetState(void) ;
void LineInterrupt_Disable(void) ;

void LineInterrupt_SetPending(void) ;
void LineInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LineInterrupt ISR. */
#define LineInterrupt_INTC_VECTOR            ((reg16 *) LineInterrupt__INTC_VECT)

/* Address of the LineInterrupt ISR priority. */
#define LineInterrupt_INTC_PRIOR             ((reg8 *) LineInterrupt__INTC_PRIOR_REG)

/* Priority of the LineInterrupt interrupt. */
#define LineInterrupt_INTC_PRIOR_NUMBER      LineInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LineInterrupt interrupt. */
#define LineInterrupt_INTC_SET_EN            ((reg8 *) LineInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LineInterrupt interrupt. */
#define LineInterrupt_INTC_CLR_EN            ((reg8 *) LineInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LineInterrupt interrupt state to pending. */
#define LineInterrupt_INTC_SET_PD            ((reg8 *) LineInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LineInterrupt interrupt. */
#define LineInterrupt_INTC_CLR_PD            ((reg8 *) LineInterrupt__INTC_CLR_PD_REG)



/* __LineInterrupt_INTC_H__ */
#endif
