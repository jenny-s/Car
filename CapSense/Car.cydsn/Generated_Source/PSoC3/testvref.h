/*******************************************************************************
* File Name: testvref.h  
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

#if !defined(CY_PINS_testvref_H) /* Pins testvref_H */
#define CY_PINS_testvref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testvref_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    testvref_Write(uint8 value) ;
void    testvref_SetDriveMode(uint8 mode) ;
uint8   testvref_ReadDataReg(void) ;
uint8   testvref_Read(void) ;
uint8   testvref_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define testvref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define testvref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define testvref_DM_RES_UP          PIN_DM_RES_UP
#define testvref_DM_RES_DWN         PIN_DM_RES_DWN
#define testvref_DM_OD_LO           PIN_DM_OD_LO
#define testvref_DM_OD_HI           PIN_DM_OD_HI
#define testvref_DM_STRONG          PIN_DM_STRONG
#define testvref_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define testvref_MASK               testvref__MASK
#define testvref_SHIFT              testvref__SHIFT
#define testvref_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testvref_PS                     (* (reg8 *) testvref__PS)
/* Data Register */
#define testvref_DR                     (* (reg8 *) testvref__DR)
/* Port Number */
#define testvref_PRT_NUM                (* (reg8 *) testvref__PRT) 
/* Connect to Analog Globals */                                                  
#define testvref_AG                     (* (reg8 *) testvref__AG)                       
/* Analog MUX bux enable */
#define testvref_AMUX                   (* (reg8 *) testvref__AMUX) 
/* Bidirectional Enable */                                                        
#define testvref_BIE                    (* (reg8 *) testvref__BIE)
/* Bit-mask for Aliased Register Access */
#define testvref_BIT_MASK               (* (reg8 *) testvref__BIT_MASK)
/* Bypass Enable */
#define testvref_BYP                    (* (reg8 *) testvref__BYP)
/* Port wide control signals */                                                   
#define testvref_CTL                    (* (reg8 *) testvref__CTL)
/* Drive Modes */
#define testvref_DM0                    (* (reg8 *) testvref__DM0) 
#define testvref_DM1                    (* (reg8 *) testvref__DM1)
#define testvref_DM2                    (* (reg8 *) testvref__DM2) 
/* Input Buffer Disable Override */
#define testvref_INP_DIS                (* (reg8 *) testvref__INP_DIS)
/* LCD Common or Segment Drive */
#define testvref_LCD_COM_SEG            (* (reg8 *) testvref__LCD_COM_SEG)
/* Enable Segment LCD */
#define testvref_LCD_EN                 (* (reg8 *) testvref__LCD_EN)
/* Slew Rate Control */
#define testvref_SLW                    (* (reg8 *) testvref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testvref_PRTDSI__CAPS_SEL       (* (reg8 *) testvref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testvref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testvref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testvref_PRTDSI__OE_SEL0        (* (reg8 *) testvref__PRTDSI__OE_SEL0) 
#define testvref_PRTDSI__OE_SEL1        (* (reg8 *) testvref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testvref_PRTDSI__OUT_SEL0       (* (reg8 *) testvref__PRTDSI__OUT_SEL0) 
#define testvref_PRTDSI__OUT_SEL1       (* (reg8 *) testvref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testvref_PRTDSI__SYNC_OUT       (* (reg8 *) testvref__PRTDSI__SYNC_OUT) 


#if defined(testvref__INTSTAT)  /* Interrupt Registers */

    #define testvref_INTSTAT                (* (reg8 *) testvref__INTSTAT)
    #define testvref_SNAP                   (* (reg8 *) testvref__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins testvref_H */


/* [] END OF FILE */
