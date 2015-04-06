/*******************************************************************************
* File Name: ServoPWM_PM.c
* Version 2.20
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "ServoPWM.h"

static ServoPWM_backupStruct ServoPWM_backup;


/*******************************************************************************
* Function Name: ServoPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ServoPWM_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ServoPWM_SaveConfig(void) 
{
    
    #if(!ServoPWM_UsingFixedFunction)
        #if (CY_PSOC5A)
            ServoPWM_backup.PWMUdb = ServoPWM_ReadCounter();
            ServoPWM_backup.PWMPeriod = ServoPWM_ReadPeriod();
            #if (ServoPWM_UseStatus)
                ServoPWM_backup.InterruptMaskValue = ServoPWM_STATUS_MASK;
            #endif /* (ServoPWM_UseStatus) */
            
            #if(ServoPWM_UseOneCompareMode)
                ServoPWM_backup.PWMCompareValue = ServoPWM_ReadCompare();
            #else
                ServoPWM_backup.PWMCompareValue1 = ServoPWM_ReadCompare1();
                ServoPWM_backup.PWMCompareValue2 = ServoPWM_ReadCompare2();
            #endif /* (ServoPWM_UseOneCompareMode) */
            
           #if(ServoPWM_DeadBandUsed)
                ServoPWM_backup.PWMdeadBandValue = ServoPWM_ReadDeadTime();
            #endif /* (ServoPWM_DeadBandUsed) */
          
            #if ( ServoPWM_KillModeMinTime)
                ServoPWM_backup.PWMKillCounterPeriod = ServoPWM_ReadKillTime();
            #endif /* ( ServoPWM_KillModeMinTime) */
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            #if(!ServoPWM_PWMModeIsCenterAligned)
                ServoPWM_backup.PWMPeriod = ServoPWM_ReadPeriod();
            #endif /* (!ServoPWM_PWMModeIsCenterAligned) */
            ServoPWM_backup.PWMUdb = ServoPWM_ReadCounter();
            #if (ServoPWM_UseStatus)
                ServoPWM_backup.InterruptMaskValue = ServoPWM_STATUS_MASK;
            #endif /* (ServoPWM_UseStatus) */
            
            #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                ServoPWM_backup.PWMdeadBandValue = ServoPWM_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(ServoPWM_KillModeMinTime)
                 ServoPWM_backup.PWMKillCounterPeriod = ServoPWM_ReadKillTime();
            #endif /* (ServoPWM_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(ServoPWM_UseControl)
            ServoPWM_backup.PWMControlRegister = ServoPWM_ReadControlRegister();
        #endif /* (ServoPWM_UseControl) */
    #endif  /* (!ServoPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoPWM_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ServoPWM_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ServoPWM_RestoreConfig(void) 
{
        #if(!ServoPWM_UsingFixedFunction)
            #if (CY_PSOC5A)
                /* Interrupt State Backup for Critical Region*/
                uint8 ServoPWM_interruptState;
                /* Enter Critical Region*/
                ServoPWM_interruptState = CyEnterCriticalSection();
                #if (ServoPWM_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    ServoPWM_STATUS_AUX_CTRL |= ServoPWM_STATUS_ACTL_INT_EN_MASK;
                    
                    ServoPWM_STATUS_MASK = ServoPWM_backup.InterruptMaskValue;
                #endif /* (ServoPWM_UseStatus) */
                
                #if (ServoPWM_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    ServoPWM_AUX_CONTROLDP0 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
                #else /* (ServoPWM_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    ServoPWM_AUX_CONTROLDP0 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
                    ServoPWM_AUX_CONTROLDP1 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
                #endif /* (ServoPWM_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(ServoPWM_interruptState);
                
                ServoPWM_WriteCounter(ServoPWM_backup.PWMUdb);
                ServoPWM_WritePeriod(ServoPWM_backup.PWMPeriod);
                
                #if(ServoPWM_UseOneCompareMode)
                    ServoPWM_WriteCompare(ServoPWM_backup.PWMCompareValue);
                #else
                    ServoPWM_WriteCompare1(ServoPWM_backup.PWMCompareValue1);
                    ServoPWM_WriteCompare2(ServoPWM_backup.PWMCompareValue2);
                #endif /* (ServoPWM_UseOneCompareMode) */
                
               #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                   ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                    ServoPWM_WriteDeadTime(ServoPWM_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( ServoPWM_KillModeMinTime)
                    ServoPWM_WriteKillTime(ServoPWM_backup.PWMKillCounterPeriod);
                #endif /* ( ServoPWM_KillModeMinTime) */
            #endif /* (CY_PSOC5A) */
            
            #if (CY_PSOC3 || CY_PSOC5LP)
                #if(!ServoPWM_PWMModeIsCenterAligned)
                    ServoPWM_WritePeriod(ServoPWM_backup.PWMPeriod);
                #endif /* (!ServoPWM_PWMModeIsCenterAligned) */
                ServoPWM_WriteCounter(ServoPWM_backup.PWMUdb);
                #if (ServoPWM_UseStatus)
                    ServoPWM_STATUS_MASK = ServoPWM_backup.InterruptMaskValue;
                #endif /* (ServoPWM_UseStatus) */
                
                #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                    ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                    ServoPWM_WriteDeadTime(ServoPWM_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(ServoPWM_KillModeMinTime)
                    ServoPWM_WriteKillTime(ServoPWM_backup.PWMKillCounterPeriod);
                #endif /* (ServoPWM_KillModeMinTime) */
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            
            #if(ServoPWM_UseControl)
                ServoPWM_WriteControlRegister(ServoPWM_backup.PWMControlRegister); 
            #endif /* (ServoPWM_UseControl) */
        #endif  /* (!ServoPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ServoPWM_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ServoPWM_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ServoPWM_Sleep(void) 
{
    #if(ServoPWM_UseControl)
        if(ServoPWM_CTRL_ENABLE == (ServoPWM_CONTROL & ServoPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            ServoPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ServoPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (ServoPWM_UseControl) */
    /* Stop component */
    ServoPWM_Stop();
    
    /* Save registers configuration */
    ServoPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: ServoPWM_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ServoPWM_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ServoPWM_Wakeup(void) 
{
     /* Restore registers values */
    ServoPWM_RestoreConfig();
    
    if(ServoPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ServoPWM_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
