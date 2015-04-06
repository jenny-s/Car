/*******************************************************************************
* File Name: TapeTimer_PM.c
* Version 2.30
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
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

#include "TapeTimer.h"
static TapeTimer_backupStruct TapeTimer_backup;


/*******************************************************************************
* Function Name: TapeTimer_SaveConfig
********************************************************************************
*
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
*  TapeTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TapeTimer_SaveConfig(void) 
{
    #if (!TapeTimer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            TapeTimer_backup.TimerUdb = TapeTimer_ReadCounter();
            TapeTimer_backup.TimerPeriod = TapeTimer_ReadPeriod();
            TapeTimer_backup.InterruptMaskValue = TapeTimer_STATUS_MASK;
            #if (TapeTimer_UsingHWCaptureCounter)
                TapeTimer_backup.TimerCaptureCounter = TapeTimer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            TapeTimer_backup.TimerUdb = TapeTimer_ReadCounter();
            TapeTimer_backup.InterruptMaskValue = TapeTimer_STATUS_MASK;
            #if (TapeTimer_UsingHWCaptureCounter)
                TapeTimer_backup.TimerCaptureCounter = TapeTimer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!TapeTimer_ControlRegRemoved)
            TapeTimer_backup.TimerControlRegister = TapeTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TapeTimer_RestoreConfig
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
*  TapeTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TapeTimer_RestoreConfig(void) 
{   
    #if (!TapeTimer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 TapeTimer_interruptState;

            TapeTimer_WriteCounter(TapeTimer_backup.TimerUdb);
            TapeTimer_WritePeriod(TapeTimer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            TapeTimer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            TapeTimer_STATUS_AUX_CTRL |= TapeTimer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(TapeTimer_interruptState);
            TapeTimer_STATUS_MASK =TapeTimer_backup.InterruptMaskValue;
            #if (TapeTimer_UsingHWCaptureCounter)
                TapeTimer_SetCaptureCount(TapeTimer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            TapeTimer_WriteCounter(TapeTimer_backup.TimerUdb);
            TapeTimer_STATUS_MASK =TapeTimer_backup.InterruptMaskValue;
            #if (TapeTimer_UsingHWCaptureCounter)
                TapeTimer_SetCaptureCount(TapeTimer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!TapeTimer_ControlRegRemoved)
            TapeTimer_WriteControlRegister(TapeTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TapeTimer_Sleep
********************************************************************************
*
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
*  TapeTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TapeTimer_Sleep(void) 
{
    #if(!TapeTimer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(TapeTimer_CTRL_ENABLE == (TapeTimer_CONTROL & TapeTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TapeTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TapeTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TapeTimer_Stop();
    TapeTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: TapeTimer_Wakeup
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
*  TapeTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TapeTimer_Wakeup(void) 
{
    TapeTimer_RestoreConfig();
    #if(!TapeTimer_ControlRegRemoved)
        if(TapeTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TapeTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
