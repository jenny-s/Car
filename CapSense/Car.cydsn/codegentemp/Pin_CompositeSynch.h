/*******************************************************************************
* File Name: Pin_CompositeSynch.h  
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

#if !defined(CY_PINS_Pin_CompositeSynch_H) /* Pins Pin_CompositeSynch_H */
#define CY_PINS_Pin_CompositeSynch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_CompositeSynch_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_CompositeSynch_Write(uint8 value) ;
void    Pin_CompositeSynch_SetDriveMode(uint8 mode) ;
uint8   Pin_CompositeSynch_ReadDataReg(void) ;
uint8   Pin_CompositeSynch_Read(void) ;
uint8   Pin_CompositeSynch_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_CompositeSynch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_CompositeSynch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_CompositeSynch_DM_RES_UP          PIN_DM_RES_UP
#define Pin_CompositeSynch_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_CompositeSynch_DM_OD_LO           PIN_DM_OD_LO
#define Pin_CompositeSynch_DM_OD_HI           PIN_DM_OD_HI
#define Pin_CompositeSynch_DM_STRONG          PIN_DM_STRONG
#define Pin_CompositeSynch_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_CompositeSynch_MASK               Pin_CompositeSynch__MASK
#define Pin_CompositeSynch_SHIFT              Pin_CompositeSynch__SHIFT
#define Pin_CompositeSynch_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_CompositeSynch_PS                     (* (reg8 *) Pin_CompositeSynch__PS)
/* Data Register */
#define Pin_CompositeSynch_DR                     (* (reg8 *) Pin_CompositeSynch__DR)
/* Port Number */
#define Pin_CompositeSynch_PRT_NUM                (* (reg8 *) Pin_CompositeSynch__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_CompositeSynch_AG                     (* (reg8 *) Pin_CompositeSynch__AG)                       
/* Analog MUX bux enable */
#define Pin_CompositeSynch_AMUX                   (* (reg8 *) Pin_CompositeSynch__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_CompositeSynch_BIE                    (* (reg8 *) Pin_CompositeSynch__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_CompositeSynch_BIT_MASK               (* (reg8 *) Pin_CompositeSynch__BIT_MASK)
/* Bypass Enable */
#define Pin_CompositeSynch_BYP                    (* (reg8 *) Pin_CompositeSynch__BYP)
/* Port wide control signals */                                                   
#define Pin_CompositeSynch_CTL                    (* (reg8 *) Pin_CompositeSynch__CTL)
/* Drive Modes */
#define Pin_CompositeSynch_DM0                    (* (reg8 *) Pin_CompositeSynch__DM0) 
#define Pin_CompositeSynch_DM1                    (* (reg8 *) Pin_CompositeSynch__DM1)
#define Pin_CompositeSynch_DM2                    (* (reg8 *) Pin_CompositeSynch__DM2) 
/* Input Buffer Disable Override */
#define Pin_CompositeSynch_INP_DIS                (* (reg8 *) Pin_CompositeSynch__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_CompositeSynch_LCD_COM_SEG            (* (reg8 *) Pin_CompositeSynch__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_CompositeSynch_LCD_EN                 (* (reg8 *) Pin_CompositeSynch__LCD_EN)
/* Slew Rate Control */
#define Pin_CompositeSynch_SLW                    (* (reg8 *) Pin_CompositeSynch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_CompositeSynch_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_CompositeSynch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_CompositeSynch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_CompositeSynch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_CompositeSynch_PRTDSI__OE_SEL0        (* (reg8 *) Pin_CompositeSynch__PRTDSI__OE_SEL0) 
#define Pin_CompositeSynch_PRTDSI__OE_SEL1        (* (reg8 *) Pin_CompositeSynch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_CompositeSynch_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_CompositeSynch__PRTDSI__OUT_SEL0) 
#define Pin_CompositeSynch_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_CompositeSynch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_CompositeSynch_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_CompositeSynch__PRTDSI__SYNC_OUT) 


#if defined(Pin_CompositeSynch__INTSTAT)  /* Interrupt Registers */

    #define Pin_CompositeSynch_INTSTAT                (* (reg8 *) Pin_CompositeSynch__INTSTAT)
    #define Pin_CompositeSynch_SNAP                   (* (reg8 *) Pin_CompositeSynch__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_CompositeSynch_H */


/* [] END OF FILE */
