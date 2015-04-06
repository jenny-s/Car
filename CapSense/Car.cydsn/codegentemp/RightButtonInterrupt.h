/*******************************************************************************
* File Name: RightButtonInterrupt.h
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
#if !defined(__RightButtonInterrupt_INTC_H__)
#define __RightButtonInterrupt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

#if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)     
    #if(CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2)      
        #include <intrins.h>
        #define RightButtonInterrupt_ISR_PATCH() _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    #endif
#endif


/* Interrupt Controller API. */
void RightButtonInterrupt_Start(void);
void RightButtonInterrupt_StartEx(cyisraddress address);
void RightButtonInterrupt_Stop(void) ;

CY_ISR_PROTO(RightButtonInterrupt_Interrupt);

void RightButtonInterrupt_SetVector(cyisraddress address) ;
cyisraddress RightButtonInterrupt_GetVector(void) ;

void RightButtonInterrupt_SetPriority(uint8 priority) ;
uint8 RightButtonInterrupt_GetPriority(void) ;

void RightButtonInterrupt_Enable(void) ;
uint8 RightButtonInterrupt_GetState(void) ;
void RightButtonInterrupt_Disable(void) ;

void RightButtonInterrupt_SetPending(void) ;
void RightButtonInterrupt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RightButtonInterrupt ISR. */
#define RightButtonInterrupt_INTC_VECTOR            ((reg16 *) RightButtonInterrupt__INTC_VECT)

/* Address of the RightButtonInterrupt ISR priority. */
#define RightButtonInterrupt_INTC_PRIOR             ((reg8 *) RightButtonInterrupt__INTC_PRIOR_REG)

/* Priority of the RightButtonInterrupt interrupt. */
#define RightButtonInterrupt_INTC_PRIOR_NUMBER      RightButtonInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RightButtonInterrupt interrupt. */
#define RightButtonInterrupt_INTC_SET_EN            ((reg8 *) RightButtonInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RightButtonInterrupt interrupt. */
#define RightButtonInterrupt_INTC_CLR_EN            ((reg8 *) RightButtonInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RightButtonInterrupt interrupt state to pending. */
#define RightButtonInterrupt_INTC_SET_PD            ((reg8 *) RightButtonInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RightButtonInterrupt interrupt. */
#define RightButtonInterrupt_INTC_CLR_PD            ((reg8 *) RightButtonInterrupt__INTC_CLR_PD_REG)



/* __RightButtonInterrupt_INTC_H__ */
#endif
