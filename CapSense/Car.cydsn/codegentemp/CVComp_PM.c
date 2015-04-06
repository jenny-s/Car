/*******************************************************************************
* File Name: CVComp.c
* Version 1.90
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "CVComp.h"

static CVComp_backupStruct CVComp_backup;


/*******************************************************************************
* Function Name: CVComp_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void CVComp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: CVComp_RestoreConfig
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
********************************************************************************/
void CVComp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: CVComp_Sleep
********************************************************************************
*
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
*  CVComp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void CVComp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(CVComp_ACT_PWR_EN == (CVComp_PWRMGR & CVComp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        CVComp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        CVComp_backup.enableState = 0u;
    }    
    
    CVComp_Stop();
    CVComp_SaveConfig();
}


/*******************************************************************************
* Function Name: CVComp_Wakeup
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
*  CVComp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CVComp_Wakeup(void) 
{
    CVComp_RestoreConfig();
    
    if(CVComp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        CVComp_Enable();

    } /* Do nothing if Comp was disabled before */
    
}


/* [] END OF FILE */
