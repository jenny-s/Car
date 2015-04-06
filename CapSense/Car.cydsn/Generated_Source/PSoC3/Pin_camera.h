/*******************************************************************************
* File Name: Pin_Camera.h  
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

#if !defined(CY_PINS_Pin_Camera_H) /* Pins Pin_Camera_H */
#define CY_PINS_Pin_Camera_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_Camera_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_Camera_Write(uint8 value) ;
void    Pin_Camera_SetDriveMode(uint8 mode) ;
uint8   Pin_Camera_ReadDataReg(void) ;
uint8   Pin_Camera_Read(void) ;
uint8   Pin_Camera_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_Camera_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_Camera_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_Camera_DM_RES_UP          PIN_DM_RES_UP
#define Pin_Camera_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_Camera_DM_OD_LO           PIN_DM_OD_LO
#define Pin_Camera_DM_OD_HI           PIN_DM_OD_HI
#define Pin_Camera_DM_STRONG          PIN_DM_STRONG
#define Pin_Camera_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_Camera_MASK               Pin_Camera__MASK
#define Pin_Camera_SHIFT              Pin_Camera__SHIFT
#define Pin_Camera_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_Camera_PS                     (* (reg8 *) Pin_Camera__PS)
/* Data Register */
#define Pin_Camera_DR                     (* (reg8 *) Pin_Camera__DR)
/* Port Number */
#define Pin_Camera_PRT_NUM                (* (reg8 *) Pin_Camera__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_Camera_AG                     (* (reg8 *) Pin_Camera__AG)                       
/* Analog MUX bux enable */
#define Pin_Camera_AMUX                   (* (reg8 *) Pin_Camera__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_Camera_BIE                    (* (reg8 *) Pin_Camera__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_Camera_BIT_MASK               (* (reg8 *) Pin_Camera__BIT_MASK)
/* Bypass Enable */
#define Pin_Camera_BYP                    (* (reg8 *) Pin_Camera__BYP)
/* Port wide control signals */                                                   
#define Pin_Camera_CTL                    (* (reg8 *) Pin_Camera__CTL)
/* Drive Modes */
#define Pin_Camera_DM0                    (* (reg8 *) Pin_Camera__DM0) 
#define Pin_Camera_DM1                    (* (reg8 *) Pin_Camera__DM1)
#define Pin_Camera_DM2                    (* (reg8 *) Pin_Camera__DM2) 
/* Input Buffer Disable Override */
#define Pin_Camera_INP_DIS                (* (reg8 *) Pin_Camera__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_Camera_LCD_COM_SEG            (* (reg8 *) Pin_Camera__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_Camera_LCD_EN                 (* (reg8 *) Pin_Camera__LCD_EN)
/* Slew Rate Control */
#define Pin_Camera_SLW                    (* (reg8 *) Pin_Camera__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_Camera_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_Camera__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_Camera_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_Camera__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_Camera_PRTDSI__OE_SEL0        (* (reg8 *) Pin_Camera__PRTDSI__OE_SEL0) 
#define Pin_Camera_PRTDSI__OE_SEL1        (* (reg8 *) Pin_Camera__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_Camera_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_Camera__PRTDSI__OUT_SEL0) 
#define Pin_Camera_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_Camera__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_Camera_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_Camera__PRTDSI__SYNC_OUT) 


#if defined(Pin_Camera__INTSTAT)  /* Interrupt Registers */

    #define Pin_Camera_INTSTAT                (* (reg8 *) Pin_Camera__INTSTAT)
    #define Pin_Camera_SNAP                   (* (reg8 *) Pin_Camera__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_Camera_H */


/* [] END OF FILE */
