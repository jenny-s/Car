/*******************************************************************************
* File Name: Clock_cam.h
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

#if !defined(CY_CLOCK_Clock_cam_H)
#define CY_CLOCK_Clock_cam_H

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

void Clock_cam_Start(void) ;
void Clock_cam_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_cam_StopBlock(void) ;
#endif

void Clock_cam_StandbyPower(uint8 state) ;
void Clock_cam_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 Clock_cam_GetDividerRegister(void) ;
void Clock_cam_SetModeRegister(uint8 modeBitMask) ;
void Clock_cam_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_cam_GetModeRegister(void) ;
void Clock_cam_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_cam_GetSourceRegister(void) ;
#if defined(Clock_cam__CFG3)
void Clock_cam_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_cam_GetPhaseRegister(void) ;
#endif

#define Clock_cam_Enable()                       Clock_cam_Start()
#define Clock_cam_Disable()                      Clock_cam_Stop()
#define Clock_cam_SetDivider(clkDivider)         Clock_cam_SetDividerRegister(clkDivider, 1)
#define Clock_cam_SetDividerValue(clkDivider)    Clock_cam_SetDividerRegister((clkDivider) - 1, 1)
#define Clock_cam_SetMode(clkMode)               Clock_cam_SetModeRegister(clkMode)
#define Clock_cam_SetSource(clkSource)           Clock_cam_SetSourceRegister(clkSource)
#if defined(Clock_cam__CFG3)
#define Clock_cam_SetPhase(clkPhase)             Clock_cam_SetPhaseRegister(clkPhase)
#define Clock_cam_SetPhaseValue(clkPhase)        Clock_cam_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_cam_CLKEN              (* (reg8 *) Clock_cam__PM_ACT_CFG)
#define Clock_cam_CLKEN_PTR          ((reg8 *) Clock_cam__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_cam_CLKSTBY            (* (reg8 *) Clock_cam__PM_STBY_CFG)
#define Clock_cam_CLKSTBY_PTR        ((reg8 *) Clock_cam__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_cam_DIV_LSB            (* (reg8 *) Clock_cam__CFG0)
#define Clock_cam_DIV_LSB_PTR        ((reg8 *) Clock_cam__CFG0)
#define Clock_cam_DIV_PTR            ((reg16 *) Clock_cam__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_cam_DIV_MSB            (* (reg8 *) Clock_cam__CFG1)
#define Clock_cam_DIV_MSB_PTR        ((reg8 *) Clock_cam__CFG1)

/* Mode and source configuration register */
#define Clock_cam_MOD_SRC            (* (reg8 *) Clock_cam__CFG2)
#define Clock_cam_MOD_SRC_PTR        ((reg8 *) Clock_cam__CFG2)

#if defined(Clock_cam__CFG3)
/* Analog clock phase configuration register */
#define Clock_cam_PHASE              (* (reg8 *) Clock_cam__CFG3)
#define Clock_cam_PHASE_PTR          ((reg8 *) Clock_cam__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_cam_CLKEN_MASK         Clock_cam__PM_ACT_MSK
#define Clock_cam_CLKSTBY_MASK       Clock_cam__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_cam_SRC_SEL_MSK        Clock_cam__CFG2_SRC_SEL_MASK
#define Clock_cam_MODE_MASK          (~(Clock_cam_SRC_SEL_MSK))

#if defined(Clock_cam__CFG3)
/* CFG3 phase mask */
#define Clock_cam_PHASE_MASK         Clock_cam__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_Clock_cam_H */


/* [] END OF FILE */
