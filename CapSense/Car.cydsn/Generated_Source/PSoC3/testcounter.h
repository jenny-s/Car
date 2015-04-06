/*******************************************************************************
* File Name: testcounter.h  
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

#if !defined(CY_PINS_testcounter_H) /* Pins testcounter_H */
#define CY_PINS_testcounter_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testcounter_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    testcounter_Write(uint8 value) ;
void    testcounter_SetDriveMode(uint8 mode) ;
uint8   testcounter_ReadDataReg(void) ;
uint8   testcounter_Read(void) ;
uint8   testcounter_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define testcounter_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define testcounter_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define testcounter_DM_RES_UP          PIN_DM_RES_UP
#define testcounter_DM_RES_DWN         PIN_DM_RES_DWN
#define testcounter_DM_OD_LO           PIN_DM_OD_LO
#define testcounter_DM_OD_HI           PIN_DM_OD_HI
#define testcounter_DM_STRONG          PIN_DM_STRONG
#define testcounter_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define testcounter_MASK               testcounter__MASK
#define testcounter_SHIFT              testcounter__SHIFT
#define testcounter_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testcounter_PS                     (* (reg8 *) testcounter__PS)
/* Data Register */
#define testcounter_DR                     (* (reg8 *) testcounter__DR)
/* Port Number */
#define testcounter_PRT_NUM                (* (reg8 *) testcounter__PRT) 
/* Connect to Analog Globals */                                                  
#define testcounter_AG                     (* (reg8 *) testcounter__AG)                       
/* Analog MUX bux enable */
#define testcounter_AMUX                   (* (reg8 *) testcounter__AMUX) 
/* Bidirectional Enable */                                                        
#define testcounter_BIE                    (* (reg8 *) testcounter__BIE)
/* Bit-mask for Aliased Register Access */
#define testcounter_BIT_MASK               (* (reg8 *) testcounter__BIT_MASK)
/* Bypass Enable */
#define testcounter_BYP                    (* (reg8 *) testcounter__BYP)
/* Port wide control signals */                                                   
#define testcounter_CTL                    (* (reg8 *) testcounter__CTL)
/* Drive Modes */
#define testcounter_DM0                    (* (reg8 *) testcounter__DM0) 
#define testcounter_DM1                    (* (reg8 *) testcounter__DM1)
#define testcounter_DM2                    (* (reg8 *) testcounter__DM2) 
/* Input Buffer Disable Override */
#define testcounter_INP_DIS                (* (reg8 *) testcounter__INP_DIS)
/* LCD Common or Segment Drive */
#define testcounter_LCD_COM_SEG            (* (reg8 *) testcounter__LCD_COM_SEG)
/* Enable Segment LCD */
#define testcounter_LCD_EN                 (* (reg8 *) testcounter__LCD_EN)
/* Slew Rate Control */
#define testcounter_SLW                    (* (reg8 *) testcounter__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testcounter_PRTDSI__CAPS_SEL       (* (reg8 *) testcounter__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testcounter_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testcounter__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testcounter_PRTDSI__OE_SEL0        (* (reg8 *) testcounter__PRTDSI__OE_SEL0) 
#define testcounter_PRTDSI__OE_SEL1        (* (reg8 *) testcounter__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testcounter_PRTDSI__OUT_SEL0       (* (reg8 *) testcounter__PRTDSI__OUT_SEL0) 
#define testcounter_PRTDSI__OUT_SEL1       (* (reg8 *) testcounter__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testcounter_PRTDSI__SYNC_OUT       (* (reg8 *) testcounter__PRTDSI__SYNC_OUT) 


#if defined(testcounter__INTSTAT)  /* Interrupt Registers */

    #define testcounter_INTSTAT                (* (reg8 *) testcounter__INTSTAT)
    #define testcounter_SNAP                   (* (reg8 *) testcounter__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins testcounter_H */


/* [] END OF FILE */
