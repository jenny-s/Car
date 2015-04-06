/*******************************************************************************
* File Name: sensor_clock.h
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

#if !defined(CY_CLOCK_sensor_clock_H)
#define CY_CLOCK_sensor_clock_H

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

void sensor_clock_Start(void) ;
void sensor_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void sensor_clock_StopBlock(void) ;
#endif

void sensor_clock_StandbyPower(uint8 state) ;
void sensor_clock_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 sensor_clock_GetDividerRegister(void) ;
void sensor_clock_SetModeRegister(uint8 modeBitMask) ;
void sensor_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 sensor_clock_GetModeRegister(void) ;
void sensor_clock_SetSourceRegister(uint8 clkSource) ;
uint8 sensor_clock_GetSourceRegister(void) ;
#if defined(sensor_clock__CFG3)
void sensor_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 sensor_clock_GetPhaseRegister(void) ;
#endif

#define sensor_clock_Enable()                       sensor_clock_Start()
#define sensor_clock_Disable()                      sensor_clock_Stop()
#define sensor_clock_SetDivider(clkDivider)         sensor_clock_SetDividerRegister(clkDivider, 1)
#define sensor_clock_SetDividerValue(clkDivider)    sensor_clock_SetDividerRegister((clkDivider) - 1, 1)
#define sensor_clock_SetMode(clkMode)               sensor_clock_SetModeRegister(clkMode)
#define sensor_clock_SetSource(clkSource)           sensor_clock_SetSourceRegister(clkSource)
#if defined(sensor_clock__CFG3)
#define sensor_clock_SetPhase(clkPhase)             sensor_clock_SetPhaseRegister(clkPhase)
#define sensor_clock_SetPhaseValue(clkPhase)        sensor_clock_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define sensor_clock_CLKEN              (* (reg8 *) sensor_clock__PM_ACT_CFG)
#define sensor_clock_CLKEN_PTR          ((reg8 *) sensor_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define sensor_clock_CLKSTBY            (* (reg8 *) sensor_clock__PM_STBY_CFG)
#define sensor_clock_CLKSTBY_PTR        ((reg8 *) sensor_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define sensor_clock_DIV_LSB            (* (reg8 *) sensor_clock__CFG0)
#define sensor_clock_DIV_LSB_PTR        ((reg8 *) sensor_clock__CFG0)
#define sensor_clock_DIV_PTR            ((reg16 *) sensor_clock__CFG0)

/* Clock MSB divider configuration register. */
#define sensor_clock_DIV_MSB            (* (reg8 *) sensor_clock__CFG1)
#define sensor_clock_DIV_MSB_PTR        ((reg8 *) sensor_clock__CFG1)

/* Mode and source configuration register */
#define sensor_clock_MOD_SRC            (* (reg8 *) sensor_clock__CFG2)
#define sensor_clock_MOD_SRC_PTR        ((reg8 *) sensor_clock__CFG2)

#if defined(sensor_clock__CFG3)
/* Analog clock phase configuration register */
#define sensor_clock_PHASE              (* (reg8 *) sensor_clock__CFG3)
#define sensor_clock_PHASE_PTR          ((reg8 *) sensor_clock__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define sensor_clock_CLKEN_MASK         sensor_clock__PM_ACT_MSK
#define sensor_clock_CLKSTBY_MASK       sensor_clock__PM_STBY_MSK

/* CFG2 field masks */
#define sensor_clock_SRC_SEL_MSK        sensor_clock__CFG2_SRC_SEL_MASK
#define sensor_clock_MODE_MASK          (~(sensor_clock_SRC_SEL_MSK))

#if defined(sensor_clock__CFG3)
/* CFG3 phase mask */
#define sensor_clock_PHASE_MASK         sensor_clock__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_sensor_clock_H */


/* [] END OF FILE */
