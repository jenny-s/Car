/*******************************************************************************
* File Name: Vref_DAC.c  
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
#include "Vref_DAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Vref_DAC_initVar = 0;

#if (CY_PSOC5A)
    uint8 Vref_DAC_restoreVal = 0;
    uint8 Vref_DAC_intrStatus = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Vref_DAC_backupStruct Vref_DAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Vref_DAC_Init
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
void Vref_DAC_Init(void) 
{
    Vref_DAC_CR0 = (Vref_DAC_MODE_V );

    /* Set default data source */
    if(Vref_DAC_DEFAULT_DATA_SRC != 0 )
    {
        Vref_DAC_CR1 = (Vref_DAC_DEFAULT_CNTL | Vref_DAC_DACBUS_ENABLE) ;
    }
    else
    {
        Vref_DAC_CR1 = (Vref_DAC_DEFAULT_CNTL | Vref_DAC_DACBUS_DISABLE) ;
    }

    /* Set default strobe mode */
    if(Vref_DAC_DEFAULT_STRB != 0)
    {
        Vref_DAC_Strobe |= Vref_DAC_STRB_EN ;
    }

    /* Set default range */
    Vref_DAC_SetRange(Vref_DAC_DEFAULT_RANGE); 

    /* Set default speed */
    Vref_DAC_SetSpeed(Vref_DAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Vref_DAC_Enable
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
void Vref_DAC_Enable(void) 
{
    Vref_DAC_PWRMGR |= Vref_DAC_ACT_PWR_EN;
    Vref_DAC_STBY_PWRMGR |= Vref_DAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Vref_DAC_restoreVal == 1) 
        {
             Vref_DAC_CR0 = Vref_DAC_backup.data_value;
             Vref_DAC_restoreVal = 0;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Vref_DAC_Start
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
*  Vref_DAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Vref_DAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Vref_DAC_initVar == 0)
    { 
        Vref_DAC_Init();
        Vref_DAC_initVar = 1;
    }

    /* Enable power to DAC */
    Vref_DAC_Enable();

    /* Set default value */
    Vref_DAC_SetValue(Vref_DAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Vref_DAC_Stop
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
void Vref_DAC_Stop(void) 
{
    /* Disble power to DAC */
    Vref_DAC_PWRMGR &= ~Vref_DAC_ACT_PWR_EN;
    Vref_DAC_STBY_PWRMGR &= ~Vref_DAC_STBY_PWR_EN;

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Vref_DAC_backup.data_value = Vref_DAC_CR0;
        Vref_DAC_CR0 = Vref_DAC_CUR_MODE_OUT_OFF;
        Vref_DAC_restoreVal = 1;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Vref_DAC_SetSpeed
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
void Vref_DAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Vref_DAC_CR0 &= ~Vref_DAC_HS_MASK ;
    Vref_DAC_CR0 |=  ( speed & Vref_DAC_HS_MASK) ;
}


/*******************************************************************************
* Function Name: Vref_DAC_SetRange
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
void Vref_DAC_SetRange(uint8 range) 
{
    Vref_DAC_CR0 &= ~Vref_DAC_RANGE_MASK ;      /* Clear existing mode */
    Vref_DAC_CR0 |= ( range & Vref_DAC_RANGE_MASK ) ; /*  Set Range  */
    Vref_DAC_DacTrim();
}


/*******************************************************************************
* Function Name: Vref_DAC_SetValue
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
void Vref_DAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        Vref_DAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Vref_DAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Vref_DAC_Data = value;
        CyExitCriticalSection(Vref_DAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Vref_DAC_DacTrim
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
void Vref_DAC_DacTrim(void) 
{
    uint8 mode;

    mode = ((Vref_DAC_CR0 & Vref_DAC_RANGE_MASK) >> 2) + Vref_DAC_TRIM_M7_1V_RNG_OFFSET;
    Vref_DAC_TR = CY_GET_XTND_REG8((uint8 *)(Vref_DAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
