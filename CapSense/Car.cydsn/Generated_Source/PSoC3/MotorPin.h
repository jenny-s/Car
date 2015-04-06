/*******************************************************************************
* File Name: MotorPin.h  
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

#if !defined(CY_PINS_MotorPin_H) /* Pins MotorPin_H */
#define CY_PINS_MotorPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MotorPin_Write(uint8 value) ;
void    MotorPin_SetDriveMode(uint8 mode) ;
uint8   MotorPin_ReadDataReg(void) ;
uint8   MotorPin_Read(void) ;
uint8   MotorPin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MotorPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MotorPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MotorPin_DM_RES_UP          PIN_DM_RES_UP
#define MotorPin_DM_RES_DWN         PIN_DM_RES_DWN
#define MotorPin_DM_OD_LO           PIN_DM_OD_LO
#define MotorPin_DM_OD_HI           PIN_DM_OD_HI
#define MotorPin_DM_STRONG          PIN_DM_STRONG
#define MotorPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MotorPin_MASK               MotorPin__MASK
#define MotorPin_SHIFT              MotorPin__SHIFT
#define MotorPin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorPin_PS                     (* (reg8 *) MotorPin__PS)
/* Data Register */
#define MotorPin_DR                     (* (reg8 *) MotorPin__DR)
/* Port Number */
#define MotorPin_PRT_NUM                (* (reg8 *) MotorPin__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorPin_AG                     (* (reg8 *) MotorPin__AG)                       
/* Analog MUX bux enable */
#define MotorPin_AMUX                   (* (reg8 *) MotorPin__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorPin_BIE                    (* (reg8 *) MotorPin__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorPin_BIT_MASK               (* (reg8 *) MotorPin__BIT_MASK)
/* Bypass Enable */
#define MotorPin_BYP                    (* (reg8 *) MotorPin__BYP)
/* Port wide control signals */                                                   
#define MotorPin_CTL                    (* (reg8 *) MotorPin__CTL)
/* Drive Modes */
#define MotorPin_DM0                    (* (reg8 *) MotorPin__DM0) 
#define MotorPin_DM1                    (* (reg8 *) MotorPin__DM1)
#define MotorPin_DM2                    (* (reg8 *) MotorPin__DM2) 
/* Input Buffer Disable Override */
#define MotorPin_INP_DIS                (* (reg8 *) MotorPin__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorPin_LCD_COM_SEG            (* (reg8 *) MotorPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorPin_LCD_EN                 (* (reg8 *) MotorPin__LCD_EN)
/* Slew Rate Control */
#define MotorPin_SLW                    (* (reg8 *) MotorPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorPin_PRTDSI__CAPS_SEL       (* (reg8 *) MotorPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorPin_PRTDSI__OE_SEL0        (* (reg8 *) MotorPin__PRTDSI__OE_SEL0) 
#define MotorPin_PRTDSI__OE_SEL1        (* (reg8 *) MotorPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorPin_PRTDSI__OUT_SEL0       (* (reg8 *) MotorPin__PRTDSI__OUT_SEL0) 
#define MotorPin_PRTDSI__OUT_SEL1       (* (reg8 *) MotorPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorPin_PRTDSI__SYNC_OUT       (* (reg8 *) MotorPin__PRTDSI__SYNC_OUT) 


#if defined(MotorPin__INTSTAT)  /* Interrupt Registers */

    #define MotorPin_INTSTAT                (* (reg8 *) MotorPin__INTSTAT)
    #define MotorPin_SNAP                   (* (reg8 *) MotorPin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins MotorPin_H */


/* [] END OF FILE */
