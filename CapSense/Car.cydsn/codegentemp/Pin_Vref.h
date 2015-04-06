/*******************************************************************************
* File Name: Pin_Vref.h  
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

#if !defined(CY_PINS_Pin_Vref_H) /* Pins Pin_Vref_H */
#define CY_PINS_Pin_Vref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_Vref_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_Vref_Write(uint8 value) ;
void    Pin_Vref_SetDriveMode(uint8 mode) ;
uint8   Pin_Vref_ReadDataReg(void) ;
uint8   Pin_Vref_Read(void) ;
uint8   Pin_Vref_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_Vref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_Vref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_Vref_DM_RES_UP          PIN_DM_RES_UP
#define Pin_Vref_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_Vref_DM_OD_LO           PIN_DM_OD_LO
#define Pin_Vref_DM_OD_HI           PIN_DM_OD_HI
#define Pin_Vref_DM_STRONG          PIN_DM_STRONG
#define Pin_Vref_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_Vref_MASK               Pin_Vref__MASK
#define Pin_Vref_SHIFT              Pin_Vref__SHIFT
#define Pin_Vref_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_Vref_PS                     (* (reg8 *) Pin_Vref__PS)
/* Data Register */
#define Pin_Vref_DR                     (* (reg8 *) Pin_Vref__DR)
/* Port Number */
#define Pin_Vref_PRT_NUM                (* (reg8 *) Pin_Vref__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_Vref_AG                     (* (reg8 *) Pin_Vref__AG)                       
/* Analog MUX bux enable */
#define Pin_Vref_AMUX                   (* (reg8 *) Pin_Vref__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_Vref_BIE                    (* (reg8 *) Pin_Vref__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_Vref_BIT_MASK               (* (reg8 *) Pin_Vref__BIT_MASK)
/* Bypass Enable */
#define Pin_Vref_BYP                    (* (reg8 *) Pin_Vref__BYP)
/* Port wide control signals */                                                   
#define Pin_Vref_CTL                    (* (reg8 *) Pin_Vref__CTL)
/* Drive Modes */
#define Pin_Vref_DM0                    (* (reg8 *) Pin_Vref__DM0) 
#define Pin_Vref_DM1                    (* (reg8 *) Pin_Vref__DM1)
#define Pin_Vref_DM2                    (* (reg8 *) Pin_Vref__DM2) 
/* Input Buffer Disable Override */
#define Pin_Vref_INP_DIS                (* (reg8 *) Pin_Vref__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_Vref_LCD_COM_SEG            (* (reg8 *) Pin_Vref__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_Vref_LCD_EN                 (* (reg8 *) Pin_Vref__LCD_EN)
/* Slew Rate Control */
#define Pin_Vref_SLW                    (* (reg8 *) Pin_Vref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_Vref_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_Vref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_Vref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_Vref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_Vref_PRTDSI__OE_SEL0        (* (reg8 *) Pin_Vref__PRTDSI__OE_SEL0) 
#define Pin_Vref_PRTDSI__OE_SEL1        (* (reg8 *) Pin_Vref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_Vref_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_Vref__PRTDSI__OUT_SEL0) 
#define Pin_Vref_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_Vref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_Vref_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_Vref__PRTDSI__SYNC_OUT) 


#if defined(Pin_Vref__INTSTAT)  /* Interrupt Registers */

    #define Pin_Vref_INTSTAT                (* (reg8 *) Pin_Vref__INTSTAT)
    #define Pin_Vref_SNAP                   (* (reg8 *) Pin_Vref__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_Vref_H */


/* [] END OF FILE */
