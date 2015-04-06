/*******************************************************************************
* File Name: Pin_vSynch.h  
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

#if !defined(CY_PINS_Pin_vSynch_H) /* Pins Pin_vSynch_H */
#define CY_PINS_Pin_vSynch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_vSynch_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_vSynch_Write(uint8 value) ;
void    Pin_vSynch_SetDriveMode(uint8 mode) ;
uint8   Pin_vSynch_ReadDataReg(void) ;
uint8   Pin_vSynch_Read(void) ;
uint8   Pin_vSynch_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_vSynch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_vSynch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_vSynch_DM_RES_UP          PIN_DM_RES_UP
#define Pin_vSynch_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_vSynch_DM_OD_LO           PIN_DM_OD_LO
#define Pin_vSynch_DM_OD_HI           PIN_DM_OD_HI
#define Pin_vSynch_DM_STRONG          PIN_DM_STRONG
#define Pin_vSynch_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_vSynch_MASK               Pin_vSynch__MASK
#define Pin_vSynch_SHIFT              Pin_vSynch__SHIFT
#define Pin_vSynch_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_vSynch_PS                     (* (reg8 *) Pin_vSynch__PS)
/* Data Register */
#define Pin_vSynch_DR                     (* (reg8 *) Pin_vSynch__DR)
/* Port Number */
#define Pin_vSynch_PRT_NUM                (* (reg8 *) Pin_vSynch__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_vSynch_AG                     (* (reg8 *) Pin_vSynch__AG)                       
/* Analog MUX bux enable */
#define Pin_vSynch_AMUX                   (* (reg8 *) Pin_vSynch__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_vSynch_BIE                    (* (reg8 *) Pin_vSynch__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_vSynch_BIT_MASK               (* (reg8 *) Pin_vSynch__BIT_MASK)
/* Bypass Enable */
#define Pin_vSynch_BYP                    (* (reg8 *) Pin_vSynch__BYP)
/* Port wide control signals */                                                   
#define Pin_vSynch_CTL                    (* (reg8 *) Pin_vSynch__CTL)
/* Drive Modes */
#define Pin_vSynch_DM0                    (* (reg8 *) Pin_vSynch__DM0) 
#define Pin_vSynch_DM1                    (* (reg8 *) Pin_vSynch__DM1)
#define Pin_vSynch_DM2                    (* (reg8 *) Pin_vSynch__DM2) 
/* Input Buffer Disable Override */
#define Pin_vSynch_INP_DIS                (* (reg8 *) Pin_vSynch__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_vSynch_LCD_COM_SEG            (* (reg8 *) Pin_vSynch__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_vSynch_LCD_EN                 (* (reg8 *) Pin_vSynch__LCD_EN)
/* Slew Rate Control */
#define Pin_vSynch_SLW                    (* (reg8 *) Pin_vSynch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_vSynch_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_vSynch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_vSynch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_vSynch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_vSynch_PRTDSI__OE_SEL0        (* (reg8 *) Pin_vSynch__PRTDSI__OE_SEL0) 
#define Pin_vSynch_PRTDSI__OE_SEL1        (* (reg8 *) Pin_vSynch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_vSynch_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_vSynch__PRTDSI__OUT_SEL0) 
#define Pin_vSynch_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_vSynch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_vSynch_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_vSynch__PRTDSI__SYNC_OUT) 


#if defined(Pin_vSynch__INTSTAT)  /* Interrupt Registers */

    #define Pin_vSynch_INTSTAT                (* (reg8 *) Pin_vSynch__INTSTAT)
    #define Pin_vSynch_SNAP                   (* (reg8 *) Pin_vSynch__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_vSynch_H */


/* [] END OF FILE */
