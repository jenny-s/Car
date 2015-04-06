/*******************************************************************************
* File Name: LeftButtonInterrupt.h
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
#if !defined(__LeftButtonInterrupt_INTC_H__)
#define __LeftButtonInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define LeftButtonInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void LeftButtonInterrupt_Start(void);
void LeftButtonInterrupt_StartEx(cyisraddress address);
void LeftButtonInterrupt_Stop(void) ;

CY_ISR_PROTO(LeftButtonInterrupt_Interrupt);

void LeftButtonInterrupt_SetVector(cyisraddress address) ;
cyisraddress LeftButtonInterrupt_GetVector(void) ;

void LeftButtonInterrupt_SetPriority(uint8 priority) ;
uint8 LeftButtonInterrupt_GetPriority(void) ;

void LeftButtonInterrupt_Enable(void) ;
uint8 LeftButtonInterrupt_GetState(void) ;
void LeftButtonInterrupt_Disable(void) ;

void LeftButtonInterrupt_SetPending(void) ;
void LeftButtonInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LeftButtonInterrupt ISR. */
#define LeftButtonInterrupt_INTC_VECTOR            ((reg16 *) LeftButtonInterrupt__INTC_VECT)

/* Address of the LeftButtonInterrupt ISR priority. */
#define LeftButtonInterrupt_INTC_PRIOR             ((reg8 *) LeftButtonInterrupt__INTC_PRIOR_REG)

/* Priority of the LeftButtonInterrupt interrupt. */
#define LeftButtonInterrupt_INTC_PRIOR_NUMBER      LeftButtonInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LeftButtonInterrupt interrupt. */
#define LeftButtonInterrupt_INTC_SET_EN            ((reg8 *) LeftButtonInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LeftButtonInterrupt interrupt. */
#define LeftButtonInterrupt_INTC_CLR_EN            ((reg8 *) LeftButtonInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LeftButtonInterrupt interrupt state to pending. */
#define LeftButtonInterrupt_INTC_SET_PD            ((reg8 *) LeftButtonInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LeftButtonInterrupt interrupt. */
#define LeftButtonInterrupt_INTC_CLR_PD            ((reg8 *) LeftButtonInterrupt__INTC_CLR_PD_REG)



/* __LeftButtonInterrupt_INTC_H__ */
#endif
