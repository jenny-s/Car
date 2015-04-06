/*******************************************************************************
* File Name: FrameInterrupt.h
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
#if !defined(__FrameInterrupt_INTC_H__)
#define __FrameInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define FrameInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void FrameInterrupt_Start(void);
void FrameInterrupt_StartEx(cyisraddress address);
void FrameInterrupt_Stop(void) ;

CY_ISR_PROTO(FrameInterrupt_Interrupt);

void FrameInterrupt_SetVector(cyisraddress address) ;
cyisraddress FrameInterrupt_GetVector(void) ;

void FrameInterrupt_SetPriority(uint8 priority) ;
uint8 FrameInterrupt_GetPriority(void) ;

void FrameInterrupt_Enable(void) ;
uint8 FrameInterrupt_GetState(void) ;
void FrameInterrupt_Disable(void) ;

void FrameInterrupt_SetPending(void) ;
void FrameInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the FrameInterrupt ISR. */
#define FrameInterrupt_INTC_VECTOR            ((reg16 *) FrameInterrupt__INTC_VECT)

/* Address of the FrameInterrupt ISR priority. */
#define FrameInterrupt_INTC_PRIOR             ((reg8 *) FrameInterrupt__INTC_PRIOR_REG)

/* Priority of the FrameInterrupt interrupt. */
#define FrameInterrupt_INTC_PRIOR_NUMBER      FrameInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable FrameInterrupt interrupt. */
#define FrameInterrupt_INTC_SET_EN            ((reg8 *) FrameInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the FrameInterrupt interrupt. */
#define FrameInterrupt_INTC_CLR_EN            ((reg8 *) FrameInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the FrameInterrupt interrupt state to pending. */
#define FrameInterrupt_INTC_SET_PD            ((reg8 *) FrameInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the FrameInterrupt interrupt. */
#define FrameInterrupt_INTC_CLR_PD            ((reg8 *) FrameInterrupt__INTC_CLR_PD_REG)



/* __FrameInterrupt_INTC_H__ */
#endif
