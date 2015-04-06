/*******************************************************************************
* File Name: TapeInterrupt.h
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
#if !defined(__TapeInterrupt_INTC_H__)
#define __TapeInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define TapeInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void TapeInterrupt_Start(void);
void TapeInterrupt_StartEx(cyisraddress address);
void TapeInterrupt_Stop(void) ;

CY_ISR_PROTO(TapeInterrupt_Interrupt);

void TapeInterrupt_SetVector(cyisraddress address) ;
cyisraddress TapeInterrupt_GetVector(void) ;

void TapeInterrupt_SetPriority(uint8 priority) ;
uint8 TapeInterrupt_GetPriority(void) ;

void TapeInterrupt_Enable(void) ;
uint8 TapeInterrupt_GetState(void) ;
void TapeInterrupt_Disable(void) ;

void TapeInterrupt_SetPending(void) ;
void TapeInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TapeInterrupt ISR. */
#define TapeInterrupt_INTC_VECTOR            ((reg16 *) TapeInterrupt__INTC_VECT)

/* Address of the TapeInterrupt ISR priority. */
#define TapeInterrupt_INTC_PRIOR             ((reg8 *) TapeInterrupt__INTC_PRIOR_REG)

/* Priority of the TapeInterrupt interrupt. */
#define TapeInterrupt_INTC_PRIOR_NUMBER      TapeInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TapeInterrupt interrupt. */
#define TapeInterrupt_INTC_SET_EN            ((reg8 *) TapeInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TapeInterrupt interrupt. */
#define TapeInterrupt_INTC_CLR_EN            ((reg8 *) TapeInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TapeInterrupt interrupt state to pending. */
#define TapeInterrupt_INTC_SET_PD            ((reg8 *) TapeInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TapeInterrupt interrupt. */
#define TapeInterrupt_INTC_CLR_PD            ((reg8 *) TapeInterrupt__INTC_CLR_PD_REG)



/* __TapeInterrupt_INTC_H__ */
#endif
