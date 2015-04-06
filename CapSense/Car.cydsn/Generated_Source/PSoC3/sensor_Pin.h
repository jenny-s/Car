/*******************************************************************************
* File Name: sensor_Pin.h  
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

#if !defined(CY_PINS_sensor_Pin_H) /* Pins sensor_Pin_H */
#define CY_PINS_sensor_Pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sensor_Pin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    sensor_Pin_Write(uint8 value) ;
void    sensor_Pin_SetDriveMode(uint8 mode) ;
uint8   sensor_Pin_ReadDataReg(void) ;
uint8   sensor_Pin_Read(void) ;
uint8   sensor_Pin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define sensor_Pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define sensor_Pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define sensor_Pin_DM_RES_UP          PIN_DM_RES_UP
#define sensor_Pin_DM_RES_DWN         PIN_DM_RES_DWN
#define sensor_Pin_DM_OD_LO           PIN_DM_OD_LO
#define sensor_Pin_DM_OD_HI           PIN_DM_OD_HI
#define sensor_Pin_DM_STRONG          PIN_DM_STRONG
#define sensor_Pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define sensor_Pin_MASK               sensor_Pin__MASK
#define sensor_Pin_SHIFT              sensor_Pin__SHIFT
#define sensor_Pin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sensor_Pin_PS                     (* (reg8 *) sensor_Pin__PS)
/* Data Register */
#define sensor_Pin_DR                     (* (reg8 *) sensor_Pin__DR)
/* Port Number */
#define sensor_Pin_PRT_NUM                (* (reg8 *) sensor_Pin__PRT) 
/* Connect to Analog Globals */                                                  
#define sensor_Pin_AG                     (* (reg8 *) sensor_Pin__AG)                       
/* Analog MUX bux enable */
#define sensor_Pin_AMUX                   (* (reg8 *) sensor_Pin__AMUX) 
/* Bidirectional Enable */                                                        
#define sensor_Pin_BIE                    (* (reg8 *) sensor_Pin__BIE)
/* Bit-mask for Aliased Register Access */
#define sensor_Pin_BIT_MASK               (* (reg8 *) sensor_Pin__BIT_MASK)
/* Bypass Enable */
#define sensor_Pin_BYP                    (* (reg8 *) sensor_Pin__BYP)
/* Port wide control signals */                                                   
#define sensor_Pin_CTL                    (* (reg8 *) sensor_Pin__CTL)
/* Drive Modes */
#define sensor_Pin_DM0                    (* (reg8 *) sensor_Pin__DM0) 
#define sensor_Pin_DM1                    (* (reg8 *) sensor_Pin__DM1)
#define sensor_Pin_DM2                    (* (reg8 *) sensor_Pin__DM2) 
/* Input Buffer Disable Override */
#define sensor_Pin_INP_DIS                (* (reg8 *) sensor_Pin__INP_DIS)
/* LCD Common or Segment Drive */
#define sensor_Pin_LCD_COM_SEG            (* (reg8 *) sensor_Pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define sensor_Pin_LCD_EN                 (* (reg8 *) sensor_Pin__LCD_EN)
/* Slew Rate Control */
#define sensor_Pin_SLW                    (* (reg8 *) sensor_Pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sensor_Pin_PRTDSI__CAPS_SEL       (* (reg8 *) sensor_Pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sensor_Pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sensor_Pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sensor_Pin_PRTDSI__OE_SEL0        (* (reg8 *) sensor_Pin__PRTDSI__OE_SEL0) 
#define sensor_Pin_PRTDSI__OE_SEL1        (* (reg8 *) sensor_Pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sensor_Pin_PRTDSI__OUT_SEL0       (* (reg8 *) sensor_Pin__PRTDSI__OUT_SEL0) 
#define sensor_Pin_PRTDSI__OUT_SEL1       (* (reg8 *) sensor_Pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sensor_Pin_PRTDSI__SYNC_OUT       (* (reg8 *) sensor_Pin__PRTDSI__SYNC_OUT) 


#if defined(sensor_Pin__INTSTAT)  /* Interrupt Registers */

    #define sensor_Pin_INTSTAT                (* (reg8 *) sensor_Pin__INTSTAT)
    #define sensor_Pin_SNAP                   (* (reg8 *) sensor_Pin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins sensor_Pin_H */


/* [] END OF FILE */
