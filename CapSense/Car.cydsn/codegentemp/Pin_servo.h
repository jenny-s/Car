/*******************************************************************************
* File Name: Pin_servo.h  
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

#if !defined(CY_PINS_Pin_servo_H) /* Pins Pin_servo_H */
#define CY_PINS_Pin_servo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_servo_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_servo_Write(uint8 value) ;
void    Pin_servo_SetDriveMode(uint8 mode) ;
uint8   Pin_servo_ReadDataReg(void) ;
uint8   Pin_servo_Read(void) ;
uint8   Pin_servo_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_servo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_servo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_servo_DM_RES_UP          PIN_DM_RES_UP
#define Pin_servo_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_servo_DM_OD_LO           PIN_DM_OD_LO
#define Pin_servo_DM_OD_HI           PIN_DM_OD_HI
#define Pin_servo_DM_STRONG          PIN_DM_STRONG
#define Pin_servo_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_servo_MASK               Pin_servo__MASK
#define Pin_servo_SHIFT              Pin_servo__SHIFT
#define Pin_servo_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_servo_PS                     (* (reg8 *) Pin_servo__PS)
/* Data Register */
#define Pin_servo_DR                     (* (reg8 *) Pin_servo__DR)
/* Port Number */
#define Pin_servo_PRT_NUM                (* (reg8 *) Pin_servo__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_servo_AG                     (* (reg8 *) Pin_servo__AG)                       
/* Analog MUX bux enable */
#define Pin_servo_AMUX                   (* (reg8 *) Pin_servo__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_servo_BIE                    (* (reg8 *) Pin_servo__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_servo_BIT_MASK               (* (reg8 *) Pin_servo__BIT_MASK)
/* Bypass Enable */
#define Pin_servo_BYP                    (* (reg8 *) Pin_servo__BYP)
/* Port wide control signals */                                                   
#define Pin_servo_CTL                    (* (reg8 *) Pin_servo__CTL)
/* Drive Modes */
#define Pin_servo_DM0                    (* (reg8 *) Pin_servo__DM0) 
#define Pin_servo_DM1                    (* (reg8 *) Pin_servo__DM1)
#define Pin_servo_DM2                    (* (reg8 *) Pin_servo__DM2) 
/* Input Buffer Disable Override */
#define Pin_servo_INP_DIS                (* (reg8 *) Pin_servo__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_servo_LCD_COM_SEG            (* (reg8 *) Pin_servo__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_servo_LCD_EN                 (* (reg8 *) Pin_servo__LCD_EN)
/* Slew Rate Control */
#define Pin_servo_SLW                    (* (reg8 *) Pin_servo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_servo_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_servo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_servo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_servo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_servo_PRTDSI__OE_SEL0        (* (reg8 *) Pin_servo__PRTDSI__OE_SEL0) 
#define Pin_servo_PRTDSI__OE_SEL1        (* (reg8 *) Pin_servo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_servo_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_servo__PRTDSI__OUT_SEL0) 
#define Pin_servo_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_servo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_servo_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_servo__PRTDSI__SYNC_OUT) 


#if defined(Pin_servo__INTSTAT)  /* Interrupt Registers */

    #define Pin_servo_INTSTAT                (* (reg8 *) Pin_servo__INTSTAT)
    #define Pin_servo_SNAP                   (* (reg8 *) Pin_servo__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_servo_H */


/* [] END OF FILE */
