/*******************************************************************************
* File Name: Button_right.h  
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

#if !defined(CY_PINS_Button_right_H) /* Pins Button_right_H */
#define CY_PINS_Button_right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_right_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_right_Write(uint8 value) ;
void    Button_right_SetDriveMode(uint8 mode) ;
uint8   Button_right_ReadDataReg(void) ;
uint8   Button_right_Read(void) ;
uint8   Button_right_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_right_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_right_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_right_DM_RES_UP          PIN_DM_RES_UP
#define Button_right_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_right_DM_OD_LO           PIN_DM_OD_LO
#define Button_right_DM_OD_HI           PIN_DM_OD_HI
#define Button_right_DM_STRONG          PIN_DM_STRONG
#define Button_right_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_right_MASK               Button_right__MASK
#define Button_right_SHIFT              Button_right__SHIFT
#define Button_right_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_right_PS                     (* (reg8 *) Button_right__PS)
/* Data Register */
#define Button_right_DR                     (* (reg8 *) Button_right__DR)
/* Port Number */
#define Button_right_PRT_NUM                (* (reg8 *) Button_right__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_right_AG                     (* (reg8 *) Button_right__AG)                       
/* Analog MUX bux enable */
#define Button_right_AMUX                   (* (reg8 *) Button_right__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_right_BIE                    (* (reg8 *) Button_right__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_right_BIT_MASK               (* (reg8 *) Button_right__BIT_MASK)
/* Bypass Enable */
#define Button_right_BYP                    (* (reg8 *) Button_right__BYP)
/* Port wide control signals */                                                   
#define Button_right_CTL                    (* (reg8 *) Button_right__CTL)
/* Drive Modes */
#define Button_right_DM0                    (* (reg8 *) Button_right__DM0) 
#define Button_right_DM1                    (* (reg8 *) Button_right__DM1)
#define Button_right_DM2                    (* (reg8 *) Button_right__DM2) 
/* Input Buffer Disable Override */
#define Button_right_INP_DIS                (* (reg8 *) Button_right__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_right_LCD_COM_SEG            (* (reg8 *) Button_right__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_right_LCD_EN                 (* (reg8 *) Button_right__LCD_EN)
/* Slew Rate Control */
#define Button_right_SLW                    (* (reg8 *) Button_right__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_right_PRTDSI__CAPS_SEL       (* (reg8 *) Button_right__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_right_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button_right__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_right_PRTDSI__OE_SEL0        (* (reg8 *) Button_right__PRTDSI__OE_SEL0) 
#define Button_right_PRTDSI__OE_SEL1        (* (reg8 *) Button_right__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_right_PRTDSI__OUT_SEL0       (* (reg8 *) Button_right__PRTDSI__OUT_SEL0) 
#define Button_right_PRTDSI__OUT_SEL1       (* (reg8 *) Button_right__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_right_PRTDSI__SYNC_OUT       (* (reg8 *) Button_right__PRTDSI__SYNC_OUT) 


#if defined(Button_right__INTSTAT)  /* Interrupt Registers */

    #define Button_right_INTSTAT                (* (reg8 *) Button_right__INTSTAT)
    #define Button_right_SNAP                   (* (reg8 *) Button_right__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Button_right_H */


/* [] END OF FILE */
