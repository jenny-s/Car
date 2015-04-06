/*******************************************************************************
* File Name: VrefDAC.h  
* Version 1.80
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the 8-bit Voltage DAC (vDAC8) User Module.
*
*   Note:
*     
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VDAC8_VrefDAC_H) 
#define CY_VDAC8_VrefDAC_H

#include "cytypes.h"
#include "cyfitter.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component VDAC8_v1_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct VrefDAC_backupStruct
{
    uint8 enableState; 
    uint8 data_value;
}VrefDAC_backupStruct;


/***************************************
*        Function Prototypes 
***************************************/

void VrefDAC_Start(void)           ;
void VrefDAC_Stop(void)            ;
void VrefDAC_SetSpeed(uint8 speed) ;
void VrefDAC_SetRange(uint8 range) ;
void VrefDAC_SetValue(uint8 value) ;
void VrefDAC_DacTrim(void)         ;
void VrefDAC_Init(void)            ;
void VrefDAC_Enable(void)          ;
void VrefDAC_SaveConfig(void)      ;
void VrefDAC_RestoreConfig(void)   ;
void VrefDAC_Sleep(void)           ;
void VrefDAC_Wakeup(void)          ;


/***************************************
*            API Constants
***************************************/

/* SetRange constants */

#define VrefDAC_RANGE_1V       0x00u
#define VrefDAC_RANGE_4V       0x04u


/* Power setting for Start API  */
#define VrefDAC_LOWSPEED       0x00u
#define VrefDAC_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

 /* Default DAC range */
#define VrefDAC_DEFAULT_RANGE    0u
 /* Default DAC speed */
#define VrefDAC_DEFAULT_SPEED    2u
 /* Default Control */
#define VrefDAC_DEFAULT_CNTL      0x00u
/* Default Strobe mode */
#define VrefDAC_DEFAULT_STRB     0u
 /* Initial DAC value */
#define VrefDAC_DEFAULT_DATA     90u
 /* Default Data Source */
#define VrefDAC_DEFAULT_DATA_SRC 0u


/***************************************
*              Registers        
***************************************/

#define VrefDAC_CR0         (* (reg8 *) VrefDAC_viDAC8__CR0 )
#define VrefDAC_CR1         (* (reg8 *) VrefDAC_viDAC8__CR1 )
#define VrefDAC_Data        (* (reg8 *) VrefDAC_viDAC8__D )
#define VrefDAC_Data_PTR    (  (reg8 *) VrefDAC_viDAC8__D )
#define VrefDAC_Strobe      (* (reg8 *) VrefDAC_viDAC8__STROBE )
#define VrefDAC_SW0         (* (reg8 *) VrefDAC_viDAC8__SW0 )
#define VrefDAC_SW2         (* (reg8 *) VrefDAC_viDAC8__SW2 )
#define VrefDAC_SW3         (* (reg8 *) VrefDAC_viDAC8__SW3 )
#define VrefDAC_SW4         (* (reg8 *) VrefDAC_viDAC8__SW4 )
#define VrefDAC_TR          (* (reg8 *) VrefDAC_viDAC8__TR )
/* Power manager */
#define VrefDAC_PWRMGR      (* (reg8 *) VrefDAC_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define VrefDAC_STBY_PWRMGR (* (reg8 *) VrefDAC_viDAC8__PM_STBY_CFG )


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define VrefDAC_HS_MASK        0x02u
#define VrefDAC_HS_LOWPOWER    0x00u
#define VrefDAC_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define VrefDAC_MODE_MASK      0x10u
#define VrefDAC_MODE_V         0x00u
#define VrefDAC_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define VrefDAC_RANGE_MASK     0x0Cu
#define VrefDAC_RANGE_0        0x00u
#define VrefDAC_RANGE_1        0x04u

/* CR1 iDac Control Register 1 definitions */

/* Bit Field  DAC_MX_DATA                  */
#define VrefDAC_SRC_MASK       0x20u
#define VrefDAC_SRC_REG        0x00u
#define VrefDAC_SRC_UDB        0x20u

/* This bit enable reset from UDB array      */
#define VrefDAC_RESET_MASK     0x10u
#define VrefDAC_RESET_ENABLE   0x10u
#define VrefDAC_RESET_DISABLE  0x00u

/* This bit enables data from DAC bus      */
#define VrefDAC_DACBUS_MASK     0x20u
#define VrefDAC_DACBUS_ENABLE   0x20u
#define VrefDAC_DACBUS_DISABLE  0x00u

/* DAC STROBE Strobe Control Register definitions */

/* Bit Field  DAC_MX_STROBE                  */
#define VrefDAC_STRB_MASK     0x08u
#define VrefDAC_STRB_EN       0x08u
#define VrefDAC_STRB_DIS      0x00u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define VrefDAC_ACT_PWR_EN   VrefDAC_viDAC8__PM_ACT_MSK
  /* Standby Power enable mask */
#define VrefDAC_STBY_PWR_EN  VrefDAC_viDAC8__PM_STBY_MSK


/*******************************************************************************
*              Trim    
* Note - VDAC trim values are stored in the "Customer Table" area in * Row 1 of
*the Hidden Flash.  There are 8 bytes of trim data for each VDAC block.
* The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* The data set for the 4 VDACs are arranged using a left side/right side
* approach:
*   Left 0, Left 1, Right 0, Right 1.
* When mapped to the VDAC0 thru VDAC3 as:
*   VDAC 0, VDAC 2, VDAC 1, VDAC 3
*******************************************************************************/
#define VrefDAC_TRIM_M7_1V_RNG_OFFSET  0x06u
#define VrefDAC_TRIM_M8_4V_RNG_OFFSET  0x07u
/*Constatnt to set DAC in current mode and turnoff output */
#define VrefDAC_CUR_MODE_OUT_OFF       0x1Eu 
#define VrefDAC_DAC_TRIM_BASE     (VrefDAC_viDAC8__TRIM__M1)

#endif /* CY_VDAC8_VrefDAC_H  */


/* [] END OF FILE */


