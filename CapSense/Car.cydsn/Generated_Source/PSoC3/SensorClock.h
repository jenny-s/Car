/*******************************************************************************
* File Name: SensorClock.h
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

#if !defined(CY_CLOCK_SensorClock_H)
#define CY_CLOCK_SensorClock_H

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

void SensorClock_Start(void) ;
void SensorClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SensorClock_StopBlock(void) ;
#endif

void SensorClock_StandbyPower(uint8 state) ;
void SensorClock_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 SensorClock_GetDividerRegister(void) ;
void SensorClock_SetModeRegister(uint8 modeBitMask) ;
void SensorClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 SensorClock_GetModeRegister(void) ;
void SensorClock_SetSourceRegister(uint8 clkSource) ;
uint8 SensorClock_GetSourceRegister(void) ;
#if defined(SensorClock__CFG3)
void SensorClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 SensorClock_GetPhaseRegister(void) ;
#endif

#define SensorClock_Enable()                       SensorClock_Start()
#define SensorClock_Disable()                      SensorClock_Stop()
#define SensorClock_SetDivider(clkDivider)         SensorClock_SetDividerRegister(clkDivider, 1)
#define SensorClock_SetDividerValue(clkDivider)    SensorClock_SetDividerRegister((clkDivider) - 1, 1)
#define SensorClock_SetMode(clkMode)               SensorClock_SetModeRegister(clkMode)
#define SensorClock_SetSource(clkSource)           SensorClock_SetSourceRegister(clkSource)
#if defined(SensorClock__CFG3)
#define SensorClock_SetPhase(clkPhase)             SensorClock_SetPhaseRegister(clkPhase)
#define SensorClock_SetPhaseValue(clkPhase)        SensorClock_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SensorClock_CLKEN              (* (reg8 *) SensorClock__PM_ACT_CFG)
#define SensorClock_CLKEN_PTR          ((reg8 *) SensorClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SensorClock_CLKSTBY            (* (reg8 *) SensorClock__PM_STBY_CFG)
#define SensorClock_CLKSTBY_PTR        ((reg8 *) SensorClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SensorClock_DIV_LSB            (* (reg8 *) SensorClock__CFG0)
#define SensorClock_DIV_LSB_PTR        ((reg8 *) SensorClock__CFG0)
#define SensorClock_DIV_PTR            ((reg16 *) SensorClock__CFG0)

/* Clock MSB divider configuration register. */
#define SensorClock_DIV_MSB            (* (reg8 *) SensorClock__CFG1)
#define SensorClock_DIV_MSB_PTR        ((reg8 *) SensorClock__CFG1)

/* Mode and source configuration register */
#define SensorClock_MOD_SRC            (* (reg8 *) SensorClock__CFG2)
#define SensorClock_MOD_SRC_PTR        ((reg8 *) SensorClock__CFG2)

#if defined(SensorClock__CFG3)
/* Analog clock phase configuration register */
#define SensorClock_PHASE              (* (reg8 *) SensorClock__CFG3)
#define SensorClock_PHASE_PTR          ((reg8 *) SensorClock__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SensorClock_CLKEN_MASK         SensorClock__PM_ACT_MSK
#define SensorClock_CLKSTBY_MASK       SensorClock__PM_STBY_MSK

/* CFG2 field masks */
#define SensorClock_SRC_SEL_MSK        SensorClock__CFG2_SRC_SEL_MASK
#define SensorClock_MODE_MASK          (~(SensorClock_SRC_SEL_MSK))

#if defined(SensorClock__CFG3)
/* CFG3 phase mask */
#define SensorClock_PHASE_MASK         SensorClock__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_SensorClock_H */


/* [] END OF FILE */
