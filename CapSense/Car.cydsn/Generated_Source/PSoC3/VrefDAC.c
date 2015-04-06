/*******************************************************************************
* File Name: VrefDAC.c  
* Version 1.80
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "VrefDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 VrefDAC_initVar = 0;

#if (CY_PSOC5A)
    uint8 VrefDAC_restoreVal = 0;
    uint8 VrefDAC_intrStatus = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static VrefDAC_backupStruct VrefDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: VrefDAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_Init(void) 
{
    VrefDAC_CR0 = (VrefDAC_MODE_V );

    /* Set default data source */
    if(VrefDAC_DEFAULT_DATA_SRC != 0 )
    {
        VrefDAC_CR1 = (VrefDAC_DEFAULT_CNTL | VrefDAC_DACBUS_ENABLE) ;
    }
    else
    {
        VrefDAC_CR1 = (VrefDAC_DEFAULT_CNTL | VrefDAC_DACBUS_DISABLE) ;
    }

    /* Set default strobe mode */
    if(VrefDAC_DEFAULT_STRB != 0)
    {
        VrefDAC_Strobe |= VrefDAC_STRB_EN ;
    }

    /* Set default range */
    VrefDAC_SetRange(VrefDAC_DEFAULT_RANGE); 

    /* Set default speed */
    VrefDAC_SetSpeed(VrefDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: VrefDAC_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_Enable(void) 
{
    VrefDAC_PWRMGR |= VrefDAC_ACT_PWR_EN;
    VrefDAC_STBY_PWRMGR |= VrefDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(VrefDAC_restoreVal == 1) 
        {
             VrefDAC_CR0 = VrefDAC_backup.data_value;
             VrefDAC_restoreVal = 0;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VrefDAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  VrefDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void VrefDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(VrefDAC_initVar == 0)
    { 
        VrefDAC_Init();
        VrefDAC_initVar = 1;
    }

    /* Enable power to DAC */
    VrefDAC_Enable();

    /* Set default value */
    VrefDAC_SetValue(VrefDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: VrefDAC_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_Stop(void) 
{
    /* Disble power to DAC */
    VrefDAC_PWRMGR &= ~VrefDAC_ACT_PWR_EN;
    VrefDAC_STBY_PWRMGR &= ~VrefDAC_STBY_PWR_EN;

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        VrefDAC_backup.data_value = VrefDAC_CR0;
        VrefDAC_CR0 = VrefDAC_CUR_MODE_OUT_OFF;
        VrefDAC_restoreVal = 1;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VrefDAC_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    VrefDAC_CR0 &= ~VrefDAC_HS_MASK ;
    VrefDAC_CR0 |=  ( speed & VrefDAC_HS_MASK) ;
}


/*******************************************************************************
* Function Name: VrefDAC_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_SetRange(uint8 range) 
{
    VrefDAC_CR0 &= ~VrefDAC_RANGE_MASK ;      /* Clear existing mode */
    VrefDAC_CR0 |= ( range & VrefDAC_RANGE_MASK ) ; /*  Set Range  */
    VrefDAC_DacTrim();
}


/*******************************************************************************
* Function Name: VrefDAC_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        VrefDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    VrefDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        VrefDAC_Data = value;
        CyExitCriticalSection(VrefDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VrefDAC_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VrefDAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((VrefDAC_CR0 & VrefDAC_RANGE_MASK) >> 2) + VrefDAC_TRIM_M7_1V_RNG_OFFSET;
    VrefDAC_TR = CY_GET_XTND_REG8((uint8 *)(VrefDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
