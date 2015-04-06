/*******************************************************************************
* File Name: LineCounter_PM.c  
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

#include "LineCounter.h"

static LineCounter_backupStruct LineCounter_backup;


/*******************************************************************************
* Function Name: LineCounter_SaveConfig
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
*  LineCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void LineCounter_SaveConfig(void) 
{
    #if (!LineCounter_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            LineCounter_backup.CounterUdb = LineCounter_ReadCounter();
            LineCounter_backup.CounterPeriod = LineCounter_ReadPeriod();
            LineCounter_backup.CompareValue = LineCounter_ReadCompare();
            LineCounter_backup.InterruptMaskValue = LineCounter_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            LineCounter_backup.CounterUdb = LineCounter_ReadCounter();
            LineCounter_backup.InterruptMaskValue = LineCounter_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!LineCounter_ControlRegRemoved)
            LineCounter_backup.CounterControlRegister = LineCounter_ReadControlRegister();
        #endif /* (!LineCounter_ControlRegRemoved) */
    #endif /* (!LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_RestoreConfig
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
*  LineCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LineCounter_RestoreConfig(void) 
{      
    #if (!LineCounter_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 LineCounter_interruptState;
        
            LineCounter_WriteCounter(LineCounter_backup.CounterUdb);
            LineCounter_WritePeriod(LineCounter_backup.CounterPeriod);
            LineCounter_WriteCompare(LineCounter_backup.CompareValue);
            /* Enter Critical Region*/
            LineCounter_interruptState = CyEnterCriticalSection();
        
            LineCounter_STATUS_AUX_CTRL |= LineCounter_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(LineCounter_interruptState);
            LineCounter_STATUS_MASK = LineCounter_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            LineCounter_WriteCounter(LineCounter_backup.CounterUdb);
            LineCounter_STATUS_MASK = LineCounter_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!LineCounter_ControlRegRemoved)
            LineCounter_WriteControlRegister(LineCounter_backup.CounterControlRegister);
        #endif /* (!LineCounter_ControlRegRemoved) */
    #endif /* (!LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_Sleep
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
*  LineCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LineCounter_Sleep(void) 
{
    #if(!LineCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(LineCounter_CTRL_ENABLE == (LineCounter_CONTROL & LineCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            LineCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            LineCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!LineCounter_ControlRegRemoved) */
    LineCounter_Stop();
    LineCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: LineCounter_Wakeup
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
*  LineCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LineCounter_Wakeup(void) 
{
    LineCounter_RestoreConfig();
    #if(!LineCounter_ControlRegRemoved)
        if(LineCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            LineCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!LineCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
