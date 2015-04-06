/*******************************************************************************
* File Name: testtimer.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_testtimer_H) /* Pins testtimer_H */
#define CY_PINS_testtimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testtimer_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    testtimer_Write(uint8 value) ;
void    testtimer_SetDriveMode(uint8 mode) ;
uint8   testtimer_ReadDataReg(void) ;
uint8   testtimer_Read(void) ;
uint8   testtimer_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define testtimer_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define testtimer_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define testtimer_DM_RES_UP          PIN_DM_RES_UP
#define testtimer_DM_RES_DWN         PIN_DM_RES_DWN
#define testtimer_DM_OD_LO           PIN_DM_OD_LO
#define testtimer_DM_OD_HI           PIN_DM_OD_HI
#define testtimer_DM_STRONG          PIN_DM_STRONG
#define testtimer_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define testtimer_MASK               testtimer__MASK
#define testtimer_SHIFT              testtimer__SHIFT
#define testtimer_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testtimer_PS                     (* (reg8 *) testtimer__PS)
/* Data Register */
#define testtimer_DR                     (* (reg8 *) testtimer__DR)
/* Port Number */
#define testtimer_PRT_NUM                (* (reg8 *) testtimer__PRT) 
/* Connect to Analog Globals */                                                  
#define testtimer_AG                     (* (reg8 *) testtimer__AG)                       
/* Analog MUX bux enable */
#define testtimer_AMUX                   (* (reg8 *) testtimer__AMUX) 
/* Bidirectional Enable */                                                        
#define testtimer_BIE                    (* (reg8 *) testtimer__BIE)
/* Bit-mask for Aliased Register Access */
#define testtimer_BIT_MASK               (* (reg8 *) testtimer__BIT_MASK)
/* Bypass Enable */
#define testtimer_BYP                    (* (reg8 *) testtimer__BYP)
/* Port wide control signals */                                                   
#define testtimer_CTL                    (* (reg8 *) testtimer__CTL)
/* Drive Modes */
#define testtimer_DM0                    (* (reg8 *) testtimer__DM0) 
#define testtimer_DM1                    (* (reg8 *) testtimer__DM1)
#define testtimer_DM2                    (* (reg8 *) testtimer__DM2) 
/* Input Buffer Disable Override */
#define testtimer_INP_DIS                (* (reg8 *) testtimer__INP_DIS)
/* LCD Common or Segment Drive */
#define testtimer_LCD_COM_SEG            (* (reg8 *) testtimer__LCD_COM_SEG)
/* Enable Segment LCD */
#define testtimer_LCD_EN                 (* (reg8 *) testtimer__LCD_EN)
/* Slew Rate Control */
#define testtimer_SLW                    (* (reg8 *) testtimer__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testtimer_PRTDSI__CAPS_SEL       (* (reg8 *) testtimer__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testtimer_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testtimer__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testtimer_PRTDSI__OE_SEL0        (* (reg8 *) testtimer__PRTDSI__OE_SEL0) 
#define testtimer_PRTDSI__OE_SEL1        (* (reg8 *) testtimer__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testtimer_PRTDSI__OUT_SEL0       (* (reg8 *) testtimer__PRTDSI__OUT_SEL0) 
#define testtimer_PRTDSI__OUT_SEL1       (* (reg8 *) testtimer__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testtimer_PRTDSI__SYNC_OUT       (* (reg8 *) testtimer__PRTDSI__SYNC_OUT) 


#if defined(testtimer__INTSTAT)  /* Interrupt Registers */

    #define testtimer_INTSTAT                (* (reg8 *) testtimer__INTSTAT)
    #define testtimer_SNAP                   (* (reg8 *) testtimer__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins testtimer_H */


/* [] END OF FILE */
