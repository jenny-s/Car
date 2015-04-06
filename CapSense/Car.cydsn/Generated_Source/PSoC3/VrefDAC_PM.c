/*******************************************************************************
* File Name: VrefDAC_PM.c  
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

#include "VrefDAC.h"

static VrefDAC_backupStruct VrefDAC_backup;


/*******************************************************************************
* Function Name: VrefDAC_SaveConfig
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
void VrefDAC_SaveConfig(void) 
{
    if (!((VrefDAC_CR1 & VrefDAC_SRC_MASK) == VrefDAC_SRC_UDB))
    {
        VrefDAC_backup.data_value = VrefDAC_Data;
    }
}


/*******************************************************************************
* Function Name: VrefDAC_RestoreConfig
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
void VrefDAC_RestoreConfig(void) 
{
    if (!((VrefDAC_CR1 & VrefDAC_SRC_MASK) == VrefDAC_SRC_UDB))
    {
        if((VrefDAC_Strobe & VrefDAC_STRB_MASK) == VrefDAC_STRB_EN)
        {
            VrefDAC_Strobe &= ~VrefDAC_STRB_MASK;
            VrefDAC_Data = VrefDAC_backup.data_value;
            VrefDAC_Strobe |= VrefDAC_STRB_EN;
        }
        else
        {
            VrefDAC_Data = VrefDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: VrefDAC_Sleep
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
*  VrefDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void VrefDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(VrefDAC_ACT_PWR_EN == (VrefDAC_PWRMGR & VrefDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        VrefDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        VrefDAC_backup.enableState = 0u;
    }
    
    VrefDAC_Stop();
    VrefDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: VrefDAC_Wakeup
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
*  VrefDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void VrefDAC_Wakeup(void) 
{
    VrefDAC_RestoreConfig();
    
    if(VrefDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        VrefDAC_Enable();

        /* Restore the data register */
        VrefDAC_SetValue(VrefDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
