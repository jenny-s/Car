/*******************************************************************************
* File Name: TimerClock.h
* Version 1.70
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_TimerClock_H)
#define CY_CLOCK_TimerClock_H

#include <cytypes.h>
#include <cyfitter.h>

/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

/***************************************
*        Function Prototypes
***************************************/

void TimerClock_Start(void) ;
void TimerClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void TimerClock_StopBlock(void) ;
#endif

void TimerClock_StandbyPower(uint8 state) ;
void TimerClock_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 TimerClock_GetDividerRegister(void) ;
void TimerClock_SetModeRegister(uint8 modeBitMask) ;
void TimerClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 TimerClock_GetModeRegister(void) ;
void TimerClock_SetSourceRegister(uint8 clkSource) ;
uint8 TimerClock_GetSourceRegister(void) ;
#if defined(TimerClock__CFG3)
void TimerClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 TimerClock_GetPhaseRegister(void) ;
#endif

#define TimerClock_Enable()                       TimerClock_Start()
#define TimerClock_Disable()                      TimerClock_Stop()
#define TimerClock_SetDivider(clkDivider)         TimerClock_SetDividerRegister(clkDivider, 1)
#define TimerClock_SetDividerValue(clkDivider)    TimerClock_SetDividerRegister((clkDivider) - 1, 1)
#define TimerClock_SetMode(clkMode)               TimerClock_SetModeRegister(clkMode)
#define TimerClock_SetSource(clkSource)           TimerClock_SetSourceRegister(clkSource)
#if defined(TimerClock__CFG3)
#define TimerClock_SetPhase(clkPhase)             TimerClock_SetPhaseRegister(clkPhase)
#define TimerClock_SetPhaseValue(clkPhase)        TimerClock_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define TimerClock_CLKEN              (* (reg8 *) TimerClock__PM_ACT_CFG)
#define TimerClock_CLKEN_PTR          ((reg8 *) TimerClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define TimerClock_CLKSTBY            (* (reg8 *) TimerClock__PM_STBY_CFG)
#define TimerClock_CLKSTBY_PTR        ((reg8 *) TimerClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define TimerClock_DIV_LSB            (* (reg8 *) TimerClock__CFG0)
#define TimerClock_DIV_LSB_PTR        ((reg8 *) TimerClock__CFG0)
#define TimerClock_DIV_PTR            ((reg16 *) TimerClock__CFG0)

/* Clock MSB divider configuration register. */
#define TimerClock_DIV_MSB            (* (reg8 *) TimerClock__CFG1)
#define TimerClock_DIV_MSB_PTR        ((reg8 *) TimerClock__CFG1)

/* Mode and source configuration register */
#define TimerClock_MOD_SRC            (* (reg8 *) TimerClock__CFG2)
#define TimerClock_MOD_SRC_PTR        ((reg8 *) TimerClock__CFG2)

#if defined(TimerClock__CFG3)
/* Analog clock phase configuration register */
#define TimerClock_PHASE              (* (reg8 *) TimerClock__CFG3)
#define TimerClock_PHASE_PTR          ((reg8 *) TimerClock__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define TimerClock_CLKEN_MASK         TimerClock__PM_ACT_MSK
#define TimerClock_CLKSTBY_MASK       TimerClock__PM_STBY_MSK

/* CFG2 field masks */
#define TimerClock_SRC_SEL_MSK        TimerClock__CFG2_SRC_SEL_MASK
#define TimerClock_MODE_MASK          (~(TimerClock_SRC_SEL_MSK))

#if defined(TimerClock__CFG3)
/* CFG3 phase mask */
#define TimerClock_PHASE_MASK         TimerClock__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_TimerClock_H */


/* [] END OF FILE */
