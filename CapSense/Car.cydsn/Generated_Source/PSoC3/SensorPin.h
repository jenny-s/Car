/*******************************************************************************
* File Name: SensorPin.h  
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

#if !defined(CY_PINS_SensorPin_H) /* Pins SensorPin_H */
#define CY_PINS_SensorPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SensorPin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SensorPin_Write(uint8 value) ;
void    SensorPin_SetDriveMode(uint8 mode) ;
uint8   SensorPin_ReadDataReg(void) ;
uint8   SensorPin_Read(void) ;
uint8   SensorPin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SensorPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SensorPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SensorPin_DM_RES_UP          PIN_DM_RES_UP
#define SensorPin_DM_RES_DWN         PIN_DM_RES_DWN
#define SensorPin_DM_OD_LO           PIN_DM_OD_LO
#define SensorPin_DM_OD_HI           PIN_DM_OD_HI
#define SensorPin_DM_STRONG          PIN_DM_STRONG
#define SensorPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SensorPin_MASK               SensorPin__MASK
#define SensorPin_SHIFT              SensorPin__SHIFT
#define SensorPin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SensorPin_PS                     (* (reg8 *) SensorPin__PS)
/* Data Register */
#define SensorPin_DR                     (* (reg8 *) SensorPin__DR)
/* Port Number */
#define SensorPin_PRT_NUM                (* (reg8 *) SensorPin__PRT) 
/* Connect to Analog Globals */                                                  
#define SensorPin_AG                     (* (reg8 *) SensorPin__AG)                       
/* Analog MUX bux enable */
#define SensorPin_AMUX                   (* (reg8 *) SensorPin__AMUX) 
/* Bidirectional Enable */                                                        
#define SensorPin_BIE                    (* (reg8 *) SensorPin__BIE)
/* Bit-mask for Aliased Register Access */
#define SensorPin_BIT_MASK               (* (reg8 *) SensorPin__BIT_MASK)
/* Bypass Enable */
#define SensorPin_BYP                    (* (reg8 *) SensorPin__BYP)
/* Port wide control signals */                                                   
#define SensorPin_CTL                    (* (reg8 *) SensorPin__CTL)
/* Drive Modes */
#define SensorPin_DM0                    (* (reg8 *) SensorPin__DM0) 
#define SensorPin_DM1                    (* (reg8 *) SensorPin__DM1)
#define SensorPin_DM2                    (* (reg8 *) SensorPin__DM2) 
/* Input Buffer Disable Override */
#define SensorPin_INP_DIS                (* (reg8 *) SensorPin__INP_DIS)
/* LCD Common or Segment Drive */
#define SensorPin_LCD_COM_SEG            (* (reg8 *) SensorPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define SensorPin_LCD_EN                 (* (reg8 *) SensorPin__LCD_EN)
/* Slew Rate Control */
#define SensorPin_SLW                    (* (reg8 *) SensorPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SensorPin_PRTDSI__CAPS_SEL       (* (reg8 *) SensorPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SensorPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SensorPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SensorPin_PRTDSI__OE_SEL0        (* (reg8 *) SensorPin__PRTDSI__OE_SEL0) 
#define SensorPin_PRTDSI__OE_SEL1        (* (reg8 *) SensorPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SensorPin_PRTDSI__OUT_SEL0       (* (reg8 *) SensorPin__PRTDSI__OUT_SEL0) 
#define SensorPin_PRTDSI__OUT_SEL1       (* (reg8 *) SensorPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SensorPin_PRTDSI__SYNC_OUT       (* (reg8 *) SensorPin__PRTDSI__SYNC_OUT) 


#if defined(SensorPin__INTSTAT)  /* Interrupt Registers */

    #define SensorPin_INTSTAT                (* (reg8 *) SensorPin__INTSTAT)
    #define SensorPin_SNAP                   (* (reg8 *) SensorPin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins SensorPin_H */


/* [] END OF FILE */
