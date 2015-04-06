/*******************************************************************************
* File Name: ServoPWM.c  
* Version 2.20
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks. 
*  The compare value output may be configured to be active when the present 
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "ServoPWM.h"

uint8 ServoPWM_initVar = 0u;


/*******************************************************************************
* Function Name: ServoPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the 
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ServoPWM_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ServoPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(ServoPWM_initVar == 0u)
    {
        ServoPWM_Init();
        ServoPWM_initVar = 1u;
    }
    ServoPWM_Enable();

}


/*******************************************************************************
* Function Name: ServoPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ServoPWM_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_Init(void) 
{
    #if (ServoPWM_UsingFixedFunction || ServoPWM_UseControl)
        uint8 ctrl;
    #endif /* (ServoPWM_UsingFixedFunction || ServoPWM_UseControl) */
    
    #if(!ServoPWM_UsingFixedFunction) 
        #if(ServoPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 ServoPWM_interruptState;
        #endif /* (ServoPWM_UseStatus) */
    #endif /* (!ServoPWM_UsingFixedFunction) */
    
    #if (ServoPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        ServoPWM_CONTROL |= ServoPWM_CFG0_MODE;
        #if (ServoPWM_DeadBand2_4)
            ServoPWM_CONTROL |= ServoPWM_CFG0_DB;
        #endif /* (ServoPWM_DeadBand2_4) */
                
        /* Set the default Compare Mode */
        #if(CY_PSOC5A)
                ctrl = ServoPWM_CONTROL2 & ~ServoPWM_CTRL_CMPMODE1_MASK;
                ServoPWM_CONTROL2 = ctrl | ServoPWM_DEFAULT_COMPARE1_MODE;
        #endif /* (CY_PSOC5A) */
        #if(CY_PSOC3 || CY_PSOC5LP)
                ctrl = ServoPWM_CONTROL3 & ~ServoPWM_CTRL_CMPMODE1_MASK;
                ServoPWM_CONTROL3 = ctrl | ServoPWM_DEFAULT_COMPARE1_MODE;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        ServoPWM_RT1 &= ~ServoPWM_RT1_MASK;
        ServoPWM_RT1 |= ServoPWM_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        ServoPWM_RT1 &= ~(ServoPWM_SYNCDSI_MASK);
        ServoPWM_RT1 |= ServoPWM_SYNCDSI_EN;
       
    #elif (ServoPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = ServoPWM_CONTROL & ~ServoPWM_CTRL_CMPMODE2_MASK & ~ServoPWM_CTRL_CMPMODE1_MASK;
        ServoPWM_CONTROL = ctrl | ServoPWM_DEFAULT_COMPARE2_MODE | 
                                   ServoPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (ServoPWM_UsingFixedFunction) */
        
    #if (!ServoPWM_UsingFixedFunction)
        #if (ServoPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            ServoPWM_AUX_CONTROLDP0 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (ServoPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            ServoPWM_AUX_CONTROLDP0 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
            ServoPWM_AUX_CONTROLDP1 |= (ServoPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (ServoPWM_Resolution == 8) */

        ServoPWM_WriteCounter(ServoPWM_INIT_PERIOD_VALUE);
    #endif /* (!ServoPWM_UsingFixedFunction) */
        
    ServoPWM_WritePeriod(ServoPWM_INIT_PERIOD_VALUE);

        #if (ServoPWM_UseOneCompareMode)
            ServoPWM_WriteCompare(ServoPWM_INIT_COMPARE_VALUE1);
        #else
            ServoPWM_WriteCompare1(ServoPWM_INIT_COMPARE_VALUE1);
            ServoPWM_WriteCompare2(ServoPWM_INIT_COMPARE_VALUE2);
        #endif /* (ServoPWM_UseOneCompareMode) */
        
        #if (ServoPWM_KillModeMinTime)
            ServoPWM_WriteKillTime(ServoPWM_MinimumKillTime);
        #endif /* (ServoPWM_KillModeMinTime) */
        
        #if (ServoPWM_DeadBandUsed)
            ServoPWM_WriteDeadTime(ServoPWM_INIT_DEAD_TIME);
        #endif /* (ServoPWM_DeadBandUsed) */

    #if (ServoPWM_UseStatus || ServoPWM_UsingFixedFunction)
        ServoPWM_SetInterruptMode(ServoPWM_INIT_INTERRUPTS_MODE);
    #endif /* (ServoPWM_UseStatus || ServoPWM_UsingFixedFunction) */
        
    #if (ServoPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        ServoPWM_GLOBAL_ENABLE |= ServoPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        ServoPWM_CONTROL2 |= ServoPWM_CTRL2_IRQ_SEL;
    #else
        #if(ServoPWM_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ServoPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            ServoPWM_STATUS_AUX_CTRL |= ServoPWM_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(ServoPWM_interruptState);
            
            /* Clear the FIFO to enable the ServoPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            ServoPWM_ClearFIFO();
        #endif /* (ServoPWM_UseStatus) */
    #endif /* (ServoPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoPWM_Enable
********************************************************************************
*
* Summary: 
*  Enables the PWM block operation
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Side Effects: 
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void ServoPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ServoPWM_UsingFixedFunction)
        ServoPWM_GLOBAL_ENABLE |= ServoPWM_BLOCK_EN_MASK;
        ServoPWM_GLOBAL_STBY_ENABLE |= ServoPWM_BLOCK_STBY_EN_MASK;
    #endif /* (ServoPWM_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (ServoPWM_UseControl || ServoPWM_UsingFixedFunction)
        ServoPWM_CONTROL |= ServoPWM_CTRL_ENABLE;
    #endif /* (ServoPWM_UseControl || ServoPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void ServoPWM_Stop(void) 
{
    #if (ServoPWM_UseControl || ServoPWM_UsingFixedFunction)
        ServoPWM_CONTROL &= ~ServoPWM_CTRL_ENABLE;
    #endif /* (ServoPWM_UseControl || ServoPWM_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ServoPWM_UsingFixedFunction)
        ServoPWM_GLOBAL_ENABLE &= ~ServoPWM_BLOCK_EN_MASK;
        ServoPWM_GLOBAL_STBY_ENABLE &= ~ServoPWM_BLOCK_STBY_EN_MASK;
    #endif /* (ServoPWM_UsingFixedFunction) */
}


#if (ServoPWM_UseOneCompareMode)
#if (ServoPWM_CompareMode1SW)


/*******************************************************************************
* Function Name: ServoPWM_SetCompareMode
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm output when in Dither mode,
*  Center Align Mode or One Output Mode.
*
* Parameters:
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return:
*  void
*
*******************************************************************************/
void ServoPWM_SetCompareMode(uint8 comparemode) 
{
    #if(ServoPWM_UsingFixedFunction)
        #if(CY_PSOC5A)
            uint8 comparemodemasked = (comparemode << ServoPWM_CTRL_CMPMODE1_SHIFT);
            ServoPWM_CONTROL2 &= ~ServoPWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            ServoPWM_CONTROL2 |= comparemodemasked;  
        #endif /* (CY_PSOC5A) */
                
        #if(CY_PSOC3 || CY_PSOC5LP)
            uint8 comparemodemasked = (comparemode << ServoPWM_CTRL_CMPMODE1_SHIFT);
            ServoPWM_CONTROL3 &= ~ServoPWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            ServoPWM_CONTROL3 |= comparemodemasked;     
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
                
    #elif (ServoPWM_UseControl)
        uint8 comparemode1masked = (comparemode << ServoPWM_CTRL_CMPMODE1_SHIFT) & 
                                    ServoPWM_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << ServoPWM_CTRL_CMPMODE2_SHIFT) & 
                                   ServoPWM_CTRL_CMPMODE2_MASK;
        /*Clear existing mode */
        ServoPWM_CONTROL &= ~(ServoPWM_CTRL_CMPMODE1_MASK | ServoPWM_CTRL_CMPMODE2_MASK); 
        ServoPWM_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif /* (ServoPWM_UsingFixedFunction) */
}
#endif /* ServoPWM_CompareMode1SW */

#else /* UseOneCompareMode */


#if (ServoPWM_CompareMode1SW)


/*******************************************************************************
* Function Name: ServoPWM_SetCompareMode1
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm1 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << ServoPWM_CTRL_CMPMODE1_SHIFT) & 
                               ServoPWM_CTRL_CMPMODE1_MASK;
    #if(ServoPWM_UsingFixedFunction)
        #if(CY_PSOC5A)
            ServoPWM_CONTROL2 &= ServoPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
            ServoPWM_CONTROL2 |= comparemodemasked; 
        #endif /* (CY_PSOC5A) */
                
        #if(CY_PSOC3 || CY_PSOC5LP)
            ServoPWM_CONTROL3 &= ServoPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
            ServoPWM_CONTROL3 |= comparemodemasked; 
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
                
    #elif (ServoPWM_UseControl)
        ServoPWM_CONTROL &= ServoPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        ServoPWM_CONTROL |= comparemodemasked;
    #endif    /* (ServoPWM_UsingFixedFunction) */
}
#endif /* ServoPWM_CompareMode1SW */


#if (ServoPWM_CompareMode2SW)


/*******************************************************************************
* Function Name: ServoPWM_SetCompareMode2
********************************************************************************
* 
* Summary:
*  This function writes the Compare Mode for the pwm or pwm2 output
*
* Parameters:  
*  comparemode:  The new compare mode for the PWM output. Use the compare types
*                defined in the H file as input arguments.
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_SetCompareMode2(uint8 comparemode) 
{
    #if(ServoPWM_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block */ 
    #elif (ServoPWM_UseControl)
        uint8 comparemodemasked = (comparemode << ServoPWM_CTRL_CMPMODE2_SHIFT) & 
                                             ServoPWM_CTRL_CMPMODE2_MASK;
        ServoPWM_CONTROL &= ServoPWM_CTRL_CMPMODE2_MASK; /*Clear existing mode */
        ServoPWM_CONTROL |= comparemodemasked;
    #endif /* (ServoPWM_UsingFixedFunction) */
}
#endif /*ServoPWM_CompareMode2SW */
#endif /* UseOneCompareMode */


#if (!ServoPWM_UsingFixedFunction)


/*******************************************************************************
* Function Name: ServoPWM_WriteCounter
********************************************************************************
* 
* Summary:
*  This function is used to change the counter value.
*
* Parameters:  
*  counter:  This value may be between 1 and (2^Resolution)-1.   
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_WriteCounter(uint16 counter) \
                                   
{
    CY_SET_REG16(ServoPWM_COUNTER_LSB_PTR, counter);
}

/*******************************************************************************
* Function Name: ServoPWM_ReadCounter
********************************************************************************
* 
* Summary:
*  This function returns the current value of the counter.  It doesn't matter
*  if the counter is enabled or running.
*
* Parameters:  
*  void  
*
* Return: 
*  The current value of the counter.
*
*******************************************************************************/
uint16 ServoPWM_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(ServoPWM_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG16(ServoPWM_CAPTURE_LSB_PTR));
}


#if (ServoPWM_UseStatus)


/*******************************************************************************
* Function Name: ServoPWM_ClearFIFO
********************************************************************************
* 
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_ClearFIFO(void) 
{
    while(ServoPWM_ReadStatusRegister() & ServoPWM_STATUS_FIFONEMPTY)
        ServoPWM_ReadCapture();
}
#endif /* ServoPWM_UseStatus */
#endif /* !ServoPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: ServoPWM_WritePeriod
********************************************************************************
* 
* Summary:
*  This function is used to change the period of the counter.  The new period 
*  will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0 
*           will result in the counter remaining at zero.
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_WritePeriod(uint16 period) 
{
    #if(ServoPWM_UsingFixedFunction)
        CY_SET_REG16(ServoPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(ServoPWM_PERIOD_LSB_PTR, period);
    #endif /* (ServoPWM_UsingFixedFunction) */
}


#if (ServoPWM_UseOneCompareMode)


/*******************************************************************************
* Function Name: ServoPWM_WriteCompare
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value when the PWM is in Dither
*  mode. The compare output will reflect the new value on the next UDB clock. 
*  The compare output will be driven high when the present counter value is 
*  compared to the compare value based on the compare mode defined in 
*  Dither Mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
* Side Effects:
*  This function is only available if the PWM mode parameter is set to
*  Dither Mode, Center Aligned Mode or One Output Mode
*
*******************************************************************************/
void ServoPWM_WriteCompare(uint16 compare) \
                                   
{
   CY_SET_REG16(ServoPWM_COMPARE1_LSB_PTR, compare);
   #if (ServoPWM_PWMMode == ServoPWM__B_PWM__DITHER)
        CY_SET_REG16(ServoPWM_COMPARE2_LSB_PTR, compare+1);
   #endif /* (ServoPWM_PWMMode == ServoPWM__B_PWM__DITHER) */
}


#else


/*******************************************************************************
* Function Name: ServoPWM_WriteCompare1
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare1 value.  The compare output will 
*  reflect the new value on the next UDB clock.  The compare output will be 
*  driven high when the present counter value is less than or less than or 
*  equal to the compare register, depending on the mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_WriteCompare1(uint16 compare) \
                                    
{
    #if(ServoPWM_UsingFixedFunction)
        CY_SET_REG16(ServoPWM_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(ServoPWM_COMPARE1_LSB_PTR, compare);
    #endif /* (ServoPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ServoPWM_WriteCompare2
********************************************************************************
* 
* Summary:
*  This funtion is used to change the compare value, for compare1 output.  
*  The compare output will reflect the new value on the next UDB clock.  
*  The compare output will be driven high when the present counter value is 
*  less than or less than or equal to the compare register, depending on the 
*  mode.
*
* Parameters:  
*  compare:  New compare value.  
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_WriteCompare2(uint16 compare) \
                                    
{
    #if(ServoPWM_UsingFixedFunction)
        CY_SET_REG16(ServoPWM_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG16(ServoPWM_COMPARE2_LSB_PTR, compare);
    #endif /* (ServoPWM_UsingFixedFunction) */
}
#endif /* UseOneCompareMode */


#if (ServoPWM_DeadBandUsed)


/*******************************************************************************
* Function Name: ServoPWM_WriteDeadTime
********************************************************************************
* 
* Summary:
*  This function writes the dead-band counts to the corresponding register
*
* Parameters:  
*  deadtime:  Number of counts for dead time 
*
* Return: 
*  void
*
*******************************************************************************/
void ServoPWM_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!ServoPWM_DeadBand2_4)
        CY_SET_REG8(ServoPWM_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        ServoPWM_DEADBAND_COUNT &= ~ServoPWM_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        ServoPWM_DEADBAND_COUNT |= (deadtime << ServoPWM_DEADBAND_COUNT_SHIFT) & 
                                            ServoPWM_DEADBAND_COUNT_MASK; 
    #endif /* (!ServoPWM_DeadBand2_4) */
}


/*******************************************************************************
* Function Name: ServoPWM_ReadDeadTime
********************************************************************************
* 
* Summary:
*  This function reads the dead-band counts from the corresponding register
*
* Parameters:  
*  void
*
* Return: 
*  Dead Band Counts
*
*******************************************************************************/
uint8 ServoPWM_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!ServoPWM_DeadBand2_4)
        return (CY_GET_REG8(ServoPWM_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((ServoPWM_DEADBAND_COUNT & ServoPWM_DEADBAND_COUNT_MASK) >> 
                 ServoPWM_DEADBAND_COUNT_SHIFT);
    #endif /* (!ServoPWM_DeadBand2_4) */
}
#endif /* DeadBandUsed */


/* [] END OF FILE */
