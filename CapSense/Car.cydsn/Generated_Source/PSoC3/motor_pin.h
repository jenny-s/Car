/*******************************************************************************
* File Name: motor_pin.h  
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

#if !defined(CY_PINS_motor_pin_H) /* Pins motor_pin_H */
#define CY_PINS_motor_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "motor_pin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    motor_pin_Write(uint8 value) ;
void    motor_pin_SetDriveMode(uint8 mode) ;
uint8   motor_pin_ReadDataReg(void) ;
uint8   motor_pin_Read(void) ;
uint8   motor_pin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define motor_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define motor_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define motor_pin_DM_RES_UP          PIN_DM_RES_UP
#define motor_pin_DM_RES_DWN         PIN_DM_RES_DWN
#define motor_pin_DM_OD_LO           PIN_DM_OD_LO
#define motor_pin_DM_OD_HI           PIN_DM_OD_HI
#define motor_pin_DM_STRONG          PIN_DM_STRONG
#define motor_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define motor_pin_MASK               motor_pin__MASK
#define motor_pin_SHIFT              motor_pin__SHIFT
#define motor_pin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define motor_pin_PS                     (* (reg8 *) motor_pin__PS)
/* Data Register */
#define motor_pin_DR                     (* (reg8 *) motor_pin__DR)
/* Port Number */
#define motor_pin_PRT_NUM                (* (reg8 *) motor_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define motor_pin_AG                     (* (reg8 *) motor_pin__AG)                       
/* Analog MUX bux enable */
#define motor_pin_AMUX                   (* (reg8 *) motor_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define motor_pin_BIE                    (* (reg8 *) motor_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define motor_pin_BIT_MASK               (* (reg8 *) motor_pin__BIT_MASK)
/* Bypass Enable */
#define motor_pin_BYP                    (* (reg8 *) motor_pin__BYP)
/* Port wide control signals */                                                   
#define motor_pin_CTL                    (* (reg8 *) motor_pin__CTL)
/* Drive Modes */
#define motor_pin_DM0                    (* (reg8 *) motor_pin__DM0) 
#define motor_pin_DM1                    (* (reg8 *) motor_pin__DM1)
#define motor_pin_DM2                    (* (reg8 *) motor_pin__DM2) 
/* Input Buffer Disable Override */
#define motor_pin_INP_DIS                (* (reg8 *) motor_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define motor_pin_LCD_COM_SEG            (* (reg8 *) motor_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define motor_pin_LCD_EN                 (* (reg8 *) motor_pin__LCD_EN)
/* Slew Rate Control */
#define motor_pin_SLW                    (* (reg8 *) motor_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define motor_pin_PRTDSI__CAPS_SEL       (* (reg8 *) motor_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define motor_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) motor_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define motor_pin_PRTDSI__OE_SEL0        (* (reg8 *) motor_pin__PRTDSI__OE_SEL0) 
#define motor_pin_PRTDSI__OE_SEL1        (* (reg8 *) motor_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define motor_pin_PRTDSI__OUT_SEL0       (* (reg8 *) motor_pin__PRTDSI__OUT_SEL0) 
#define motor_pin_PRTDSI__OUT_SEL1       (* (reg8 *) motor_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define motor_pin_PRTDSI__SYNC_OUT       (* (reg8 *) motor_pin__PRTDSI__SYNC_OUT) 


#if defined(motor_pin__INTSTAT)  /* Interrupt Registers */

    #define motor_pin_INTSTAT                (* (reg8 *) motor_pin__INTSTAT)
    #define motor_pin_SNAP                   (* (reg8 *) motor_pin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins motor_pin_H */


/* [] END OF FILE */
