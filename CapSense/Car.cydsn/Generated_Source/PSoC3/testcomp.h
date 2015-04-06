/*******************************************************************************
* File Name: testcomp.h  
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

#if !defined(CY_PINS_testcomp_H) /* Pins testcomp_H */
#define CY_PINS_testcomp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testcomp_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    testcomp_Write(uint8 value) ;
void    testcomp_SetDriveMode(uint8 mode) ;
uint8   testcomp_ReadDataReg(void) ;
uint8   testcomp_Read(void) ;
uint8   testcomp_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define testcomp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define testcomp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define testcomp_DM_RES_UP          PIN_DM_RES_UP
#define testcomp_DM_RES_DWN         PIN_DM_RES_DWN
#define testcomp_DM_OD_LO           PIN_DM_OD_LO
#define testcomp_DM_OD_HI           PIN_DM_OD_HI
#define testcomp_DM_STRONG          PIN_DM_STRONG
#define testcomp_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define testcomp_MASK               testcomp__MASK
#define testcomp_SHIFT              testcomp__SHIFT
#define testcomp_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testcomp_PS                     (* (reg8 *) testcomp__PS)
/* Data Register */
#define testcomp_DR                     (* (reg8 *) testcomp__DR)
/* Port Number */
#define testcomp_PRT_NUM                (* (reg8 *) testcomp__PRT) 
/* Connect to Analog Globals */                                                  
#define testcomp_AG                     (* (reg8 *) testcomp__AG)                       
/* Analog MUX bux enable */
#define testcomp_AMUX                   (* (reg8 *) testcomp__AMUX) 
/* Bidirectional Enable */                                                        
#define testcomp_BIE                    (* (reg8 *) testcomp__BIE)
/* Bit-mask for Aliased Register Access */
#define testcomp_BIT_MASK               (* (reg8 *) testcomp__BIT_MASK)
/* Bypass Enable */
#define testcomp_BYP                    (* (reg8 *) testcomp__BYP)
/* Port wide control signals */                                                   
#define testcomp_CTL                    (* (reg8 *) testcomp__CTL)
/* Drive Modes */
#define testcomp_DM0                    (* (reg8 *) testcomp__DM0) 
#define testcomp_DM1                    (* (reg8 *) testcomp__DM1)
#define testcomp_DM2                    (* (reg8 *) testcomp__DM2) 
/* Input Buffer Disable Override */
#define testcomp_INP_DIS                (* (reg8 *) testcomp__INP_DIS)
/* LCD Common or Segment Drive */
#define testcomp_LCD_COM_SEG            (* (reg8 *) testcomp__LCD_COM_SEG)
/* Enable Segment LCD */
#define testcomp_LCD_EN                 (* (reg8 *) testcomp__LCD_EN)
/* Slew Rate Control */
#define testcomp_SLW                    (* (reg8 *) testcomp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testcomp_PRTDSI__CAPS_SEL       (* (reg8 *) testcomp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testcomp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testcomp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testcomp_PRTDSI__OE_SEL0        (* (reg8 *) testcomp__PRTDSI__OE_SEL0) 
#define testcomp_PRTDSI__OE_SEL1        (* (reg8 *) testcomp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testcomp_PRTDSI__OUT_SEL0       (* (reg8 *) testcomp__PRTDSI__OUT_SEL0) 
#define testcomp_PRTDSI__OUT_SEL1       (* (reg8 *) testcomp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testcomp_PRTDSI__SYNC_OUT       (* (reg8 *) testcomp__PRTDSI__SYNC_OUT) 


#if defined(testcomp__INTSTAT)  /* Interrupt Registers */

    #define testcomp_INTSTAT                (* (reg8 *) testcomp__INTSTAT)
    #define testcomp_SNAP                   (* (reg8 *) testcomp__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins testcomp_H */


/* [] END OF FILE */
