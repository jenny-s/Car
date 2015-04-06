/*******************************************************************************
* File Name: Vref_DAC_PM.c  
* Version 1.80
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Vref_DAC.h"

static Vref_DAC_backupStruct Vref_DAC_backup;


/*******************************************************************************
* Function Name: Vref_DAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Vref_DAC_SaveConfig(void) 
{
    if (!((Vref_DAC_CR1 & Vref_DAC_SRC_MASK) == Vref_DAC_SRC_UDB))
    {
        Vref_DAC_backup.data_value = Vref_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: Vref_DAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Vref_DAC_RestoreConfig(void) 
{
    if (!((Vref_DAC_CR1 & Vref_DAC_SRC_MASK) == Vref_DAC_SRC_UDB))
    {
        if((Vref_DAC_Strobe & Vref_DAC_STRB_MASK) == Vref_DAC_STRB_EN)
        {
            Vref_DAC_Strobe &= ~Vref_DAC_STRB_MASK;
            Vref_DAC_Data = Vref_DAC_backup.data_value;
            Vref_DAC_Strobe |= Vref_DAC_STRB_EN;
        }
        else
        {
            Vref_DAC_Data = Vref_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Vref_DAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Vref_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Vref_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Vref_DAC_ACT_PWR_EN == (Vref_DAC_PWRMGR & Vref_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Vref_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Vref_DAC_backup.enableState = 0u;
    }
    
    Vref_DAC_Stop();
    Vref_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: Vref_DAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Vref_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Vref_DAC_Wakeup(void) 
{
    Vref_DAC_RestoreConfig();
    
    if(Vref_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Vref_DAC_Enable();

        /* Restore the data register */
        Vref_DAC_SetValue(Vref_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
