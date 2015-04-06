/*******************************************************************************
* File Name: CompSynchCounter_PM.c  
* Version 2.20
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "CompSynchCounter.h"

static CompSynchCounter_backupStruct CompSynchCounter_backup;


/*******************************************************************************
* Function Name: CompSynchCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  CompSynchCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void CompSynchCounter_SaveConfig(void) 
{
    #if (!CompSynchCounter_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            CompSynchCounter_backup.CounterUdb = CompSynchCounter_ReadCounter();
            CompSynchCounter_backup.CounterPeriod = CompSynchCounter_ReadPeriod();
            CompSynchCounter_backup.CompareValue = CompSynchCounter_ReadCompare();
            CompSynchCounter_backup.InterruptMaskValue = CompSynchCounter_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            CompSynchCounter_backup.CounterUdb = CompSynchCounter_ReadCounter();
            CompSynchCounter_backup.InterruptMaskValue = CompSynchCounter_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!CompSynchCounter_ControlRegRemoved)
            CompSynchCounter_backup.CounterControlRegister = CompSynchCounter_ReadControlRegister();
        #endif /* (!CompSynchCounter_ControlRegRemoved) */
    #endif /* (!CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_RestoreConfig
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
* Global variables:
*  CompSynchCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void CompSynchCounter_RestoreConfig(void) 
{      
    #if (!CompSynchCounter_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 CompSynchCounter_interruptState;
        
            CompSynchCounter_WriteCounter(CompSynchCounter_backup.CounterUdb);
            CompSynchCounter_WritePeriod(CompSynchCounter_backup.CounterPeriod);
            CompSynchCounter_WriteCompare(CompSynchCounter_backup.CompareValue);
            /* Enter Critical Region*/
            CompSynchCounter_interruptState = CyEnterCriticalSection();
        
            CompSynchCounter_STATUS_AUX_CTRL |= CompSynchCounter_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(CompSynchCounter_interruptState);
            CompSynchCounter_STATUS_MASK = CompSynchCounter_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            CompSynchCounter_WriteCounter(CompSynchCounter_backup.CounterUdb);
            CompSynchCounter_STATUS_MASK = CompSynchCounter_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!CompSynchCounter_ControlRegRemoved)
            CompSynchCounter_WriteControlRegister(CompSynchCounter_backup.CounterControlRegister);
        #endif /* (!CompSynchCounter_ControlRegRemoved) */
    #endif /* (!CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  CompSynchCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void CompSynchCounter_Sleep(void) 
{
    #if(!CompSynchCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(CompSynchCounter_CTRL_ENABLE == (CompSynchCounter_CONTROL & CompSynchCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            CompSynchCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            CompSynchCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!CompSynchCounter_ControlRegRemoved) */
    CompSynchCounter_Stop();
    CompSynchCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: CompSynchCounter_Wakeup
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
*  CompSynchCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void CompSynchCounter_Wakeup(void) 
{
    CompSynchCounter_RestoreConfig();
    #if(!CompSynchCounter_ControlRegRemoved)
        if(CompSynchCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            CompSynchCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!CompSynchCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
