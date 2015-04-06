/*******************************************************************************
* File Name: SensorTimer_PM.c
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

#include "SensorTimer.h"
static SensorTimer_backupStruct SensorTimer_backup;


/*******************************************************************************
* Function Name: SensorTimer_SaveConfig
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
*  SensorTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SensorTimer_SaveConfig(void) 
{
    #if (!SensorTimer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            SensorTimer_backup.TimerUdb = SensorTimer_ReadCounter();
            SensorTimer_backup.TimerPeriod = SensorTimer_ReadPeriod();
            SensorTimer_backup.InterruptMaskValue = SensorTimer_STATUS_MASK;
            #if (SensorTimer_UsingHWCaptureCounter)
                SensorTimer_backup.TimerCaptureCounter = SensorTimer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            SensorTimer_backup.TimerUdb = SensorTimer_ReadCounter();
            SensorTimer_backup.InterruptMaskValue = SensorTimer_STATUS_MASK;
            #if (SensorTimer_UsingHWCaptureCounter)
                SensorTimer_backup.TimerCaptureCounter = SensorTimer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!SensorTimer_ControlRegRemoved)
            SensorTimer_backup.TimerControlRegister = SensorTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SensorTimer_RestoreConfig
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
*  SensorTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SensorTimer_RestoreConfig(void) 
{   
    #if (!SensorTimer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 SensorTimer_interruptState;

            SensorTimer_WriteCounter(SensorTimer_backup.TimerUdb);
            SensorTimer_WritePeriod(SensorTimer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            SensorTimer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            SensorTimer_STATUS_AUX_CTRL |= SensorTimer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(SensorTimer_interruptState);
            SensorTimer_STATUS_MASK =SensorTimer_backup.InterruptMaskValue;
            #if (SensorTimer_UsingHWCaptureCounter)
                SensorTimer_SetCaptureCount(SensorTimer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            SensorTimer_WriteCounter(SensorTimer_backup.TimerUdb);
            SensorTimer_STATUS_MASK =SensorTimer_backup.InterruptMaskValue;
            #if (SensorTimer_UsingHWCaptureCounter)
                SensorTimer_SetCaptureCount(SensorTimer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!SensorTimer_ControlRegRemoved)
            SensorTimer_WriteControlRegister(SensorTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SensorTimer_Sleep
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
*  SensorTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SensorTimer_Sleep(void) 
{
    #if(!SensorTimer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(SensorTimer_CTRL_ENABLE == (SensorTimer_CONTROL & SensorTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SensorTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SensorTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SensorTimer_Stop();
    SensorTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SensorTimer_Wakeup
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
*  SensorTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SensorTimer_Wakeup(void) 
{
    SensorTimer_RestoreConfig();
    #if(!SensorTimer_ControlRegRemoved)
        if(SensorTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SensorTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
