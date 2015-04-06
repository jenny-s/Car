/*******************************************************************************
* File Name: Button_left.h  
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

#if !defined(CY_PINS_Button_left_H) /* Pins Button_left_H */
#define CY_PINS_Button_left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_left_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_left_Write(uint8 value) ;
void    Button_left_SetDriveMode(uint8 mode) ;
uint8   Button_left_ReadDataReg(void) ;
uint8   Button_left_Read(void) ;
uint8   Button_left_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_left_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_left_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_left_DM_RES_UP          PIN_DM_RES_UP
#define Button_left_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_left_DM_OD_LO           PIN_DM_OD_LO
#define Button_left_DM_OD_HI           PIN_DM_OD_HI
#define Button_left_DM_STRONG          PIN_DM_STRONG
#define Button_left_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_left_MASK               Button_left__MASK
#define Button_left_SHIFT              Button_left__SHIFT
#define Button_left_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_left_PS                     (* (reg8 *) Button_left__PS)
/* Data Register */
#define Button_left_DR                     (* (reg8 *) Button_left__DR)
/* Port Number */
#define Button_left_PRT_NUM                (* (reg8 *) Button_left__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_left_AG                     (* (reg8 *) Button_left__AG)                       
/* Analog MUX bux enable */
#define Button_left_AMUX                   (* (reg8 *) Button_left__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_left_BIE                    (* (reg8 *) Button_left__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_left_BIT_MASK               (* (reg8 *) Button_left__BIT_MASK)
/* Bypass Enable */
#define Button_left_BYP                    (* (reg8 *) Button_left__BYP)
/* Port wide control signals */                                                   
#define Button_left_CTL                    (* (reg8 *) Button_left__CTL)
/* Drive Modes */
#define Button_left_DM0                    (* (reg8 *) Button_left__DM0) 
#define Button_left_DM1                    (* (reg8 *) Button_left__DM1)
#define Button_left_DM2                    (* (reg8 *) Button_left__DM2) 
/* Input Buffer Disable Override */
#define Button_left_INP_DIS                (* (reg8 *) Button_left__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_left_LCD_COM_SEG            (* (reg8 *) Button_left__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_left_LCD_EN                 (* (reg8 *) Button_left__LCD_EN)
/* Slew Rate Control */
#define Button_left_SLW                    (* (reg8 *) Button_left__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_left_PRTDSI__CAPS_SEL       (* (reg8 *) Button_left__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_left_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_left__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_left_PRTDSI__OE_SEL0        (* (reg8 *) Button_left__PRTDSI__OE_SEL0) 
#define Button_left_PRTDSI__OE_SEL1        (* (reg8 *) Button_left__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_left_PRTDSI__OUT_SEL0       (* (reg8 *) Button_left__PRTDSI__OUT_SEL0) 
#define Button_left_PRTDSI__OUT_SEL1       (* (reg8 *) Button_left__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_left_PRTDSI__SYNC_OUT       (* (reg8 *) Button_left__PRTDSI__SYNC_OUT) 


#if defined(Button_left__INTSTAT)  /* Interrupt Registers */

    #define Button_left_INTSTAT                (* (reg8 *) Button_left__INTSTAT)
    #define Button_left_SNAP                   (* (reg8 *) Button_left__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Button_left_H */


/* [] END OF FILE */
