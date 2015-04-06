/*******************************************************************************
* File Name: NavTimer_PM.c
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

#include "NavTimer.h"
static NavTimer_backupStruct NavTimer_backup;


/*******************************************************************************
* Function Name: NavTimer_SaveConfig
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
*  NavTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void NavTimer_SaveConfig(void) 
{
    #if (!NavTimer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A*/
        #if (CY_PSOC5A)
            NavTimer_backup.TimerUdb = NavTimer_ReadCounter();
            NavTimer_backup.TimerPeriod = NavTimer_ReadPeriod();
            NavTimer_backup.InterruptMaskValue = NavTimer_STATUS_MASK;
            #if (NavTimer_UsingHWCaptureCounter)
                NavTimer_backup.TimerCaptureCounter = NavTimer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Backup the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            NavTimer_backup.TimerUdb = NavTimer_ReadCounter();
            NavTimer_backup.InterruptMaskValue = NavTimer_STATUS_MASK;
            #if (NavTimer_UsingHWCaptureCounter)
                NavTimer_backup.TimerCaptureCounter = NavTimer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!NavTimer_ControlRegRemoved)
            NavTimer_backup.TimerControlRegister = NavTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: NavTimer_RestoreConfig
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
*  NavTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void NavTimer_RestoreConfig(void) 
{   
    #if (!NavTimer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 NavTimer_interruptState;

            NavTimer_WriteCounter(NavTimer_backup.TimerUdb);
            NavTimer_WritePeriod(NavTimer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            NavTimer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            NavTimer_STATUS_AUX_CTRL |= NavTimer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(NavTimer_interruptState);
            NavTimer_STATUS_MASK =NavTimer_backup.InterruptMaskValue;
            #if (NavTimer_UsingHWCaptureCounter)
                NavTimer_SetCaptureCount(NavTimer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for PSoC5A */
        #endif /* Restore the UDB non-rentention registers for PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            NavTimer_WriteCounter(NavTimer_backup.TimerUdb);
            NavTimer_STATUS_MASK =NavTimer_backup.InterruptMaskValue;
            #if (NavTimer_UsingHWCaptureCounter)
                NavTimer_SetCaptureCount(NavTimer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for PSoC3 or PSoC5LP */

        #if(!NavTimer_ControlRegRemoved)
            NavTimer_WriteControlRegister(NavTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: NavTimer_Sleep
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
*  NavTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void NavTimer_Sleep(void) 
{
    #if(!NavTimer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(NavTimer_CTRL_ENABLE == (NavTimer_CONTROL & NavTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            NavTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            NavTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    NavTimer_Stop();
    NavTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: NavTimer_Wakeup
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
*  NavTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void NavTimer_Wakeup(void) 
{
    NavTimer_RestoreConfig();
    #if(!NavTimer_ControlRegRemoved)
        if(NavTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                NavTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
