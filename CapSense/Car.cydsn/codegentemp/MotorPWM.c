/*******************************************************************************
* File Name: MotorPWM.c  
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
#include "MotorPWM.h"

uint8 MotorPWM_initVar = 0u;


/*******************************************************************************
* Function Name: MotorPWM_Start
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
*  MotorPWM_initVar: Is modified when this function is called for the 
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void MotorPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(MotorPWM_initVar == 0u)
    {
        MotorPWM_Init();
        MotorPWM_initVar = 1u;
    }
    MotorPWM_Enable();

}


/*******************************************************************************
* Function Name: MotorPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  MotorPWM_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void MotorPWM_Init(void) 
{
    #if (MotorPWM_UsingFixedFunction || MotorPWM_UseControl)
        uint8 ctrl;
    #endif /* (MotorPWM_UsingFixedFunction || MotorPWM_UseControl) */
    
    #if(!MotorPWM_UsingFixedFunction) 
        #if(MotorPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 MotorPWM_interruptState;
        #endif /* (MotorPWM_UseStatus) */
    #endif /* (!MotorPWM_UsingFixedFunction) */
    
    #if (MotorPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        MotorPWM_CONTROL |= MotorPWM_CFG0_MODE;
        #if (MotorPWM_DeadBand2_4)
            MotorPWM_CONTROL |= MotorPWM_CFG0_DB;
        #endif /* (MotorPWM_DeadBand2_4) */
                
        /* Set the default Compare Mode */
        #if(CY_PSOC5A)
                ctrl = MotorPWM_CONTROL2 & ~MotorPWM_CTRL_CMPMODE1_MASK;
                MotorPWM_CONTROL2 = ctrl | MotorPWM_DEFAULT_COMPARE1_MODE;
        #endif /* (CY_PSOC5A) */
        #if(CY_PSOC3 || CY_PSOC5LP)
                ctrl = MotorPWM_CONTROL3 & ~MotorPWM_CTRL_CMPMODE1_MASK;
                MotorPWM_CONTROL3 = ctrl | MotorPWM_DEFAULT_COMPARE1_MODE;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        MotorPWM_RT1 &= ~MotorPWM_RT1_MASK;
        MotorPWM_RT1 |= MotorPWM_SYNC;     
                
        /*Enable DSI Sync all all inputs of the PWM*/
        MotorPWM_RT1 &= ~(MotorPWM_SYNCDSI_MASK);
        MotorPWM_RT1 |= MotorPWM_SYNCDSI_EN;
       
    #elif (MotorPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = MotorPWM_CONTROL & ~MotorPWM_CTRL_CMPMODE2_MASK & ~MotorPWM_CTRL_CMPMODE1_MASK;
        MotorPWM_CONTROL = ctrl | MotorPWM_DEFAULT_COMPARE2_MODE | 
                                   MotorPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (MotorPWM_UsingFixedFunction) */
        
    #if (!MotorPWM_UsingFixedFunction)
        #if (MotorPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            MotorPWM_AUX_CONTROLDP0 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (MotorPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            MotorPWM_AUX_CONTROLDP0 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
            MotorPWM_AUX_CONTROLDP1 |= (MotorPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (MotorPWM_Resolution == 8) */

        MotorPWM_WriteCounter(MotorPWM_INIT_PERIOD_VALUE);
    #endif /* (!MotorPWM_UsingFixedFunction) */
        
    MotorPWM_WritePeriod(MotorPWM_INIT_PERIOD_VALUE);

        #if (MotorPWM_UseOneCompareMode)
            MotorPWM_WriteCompare(MotorPWM_INIT_COMPARE_VALUE1);
        #else
            MotorPWM_WriteCompare1(MotorPWM_INIT_COMPARE_VALUE1);
            MotorPWM_WriteCompare2(MotorPWM_INIT_COMPARE_VALUE2);
        #endif /* (MotorPWM_UseOneCompareMode) */
        
        #if (MotorPWM_KillModeMinTime)
            MotorPWM_WriteKillTime(MotorPWM_MinimumKillTime);
        #endif /* (MotorPWM_KillModeMinTime) */
        
        #if (MotorPWM_DeadBandUsed)
            MotorPWM_WriteDeadTime(MotorPWM_INIT_DEAD_TIME);
        #endif /* (MotorPWM_DeadBandUsed) */

    #if (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction)
        MotorPWM_SetInterruptMode(MotorPWM_INIT_INTERRUPTS_MODE);
    #endif /* (MotorPWM_UseStatus || MotorPWM_UsingFixedFunction) */
        
    #if (MotorPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        MotorPWM_GLOBAL_ENABLE |= MotorPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        MotorPWM_CONTROL2 |= MotorPWM_CTRL2_IRQ_SEL;
    #else
        #if(MotorPWM_UseStatus)
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            MotorPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            MotorPWM_STATUS_AUX_CTRL |= MotorPWM_STATUS_ACTL_INT_EN_MASK;
            
             /* Exit Critical Region*/
            CyExitCriticalSection(MotorPWM_interruptState);
            
            /* Clear the FIFO to enable the MotorPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            MotorPWM_ClearFIFO();
        #endif /* (MotorPWM_UseStatus) */
    #endif /* (MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_Enable
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
void MotorPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (MotorPWM_UsingFixedFunction)
        MotorPWM_GLOBAL_ENABLE |= MotorPWM_BLOCK_EN_MASK;
        MotorPWM_GLOBAL_STBY_ENABLE |= MotorPWM_BLOCK_STBY_EN_MASK;
    #endif /* (MotorPWM_UsingFixedFunction) */
    
    /* Enable the PWM from the control register  */
    #if (MotorPWM_UseControl || MotorPWM_UsingFixedFunction)
        MotorPWM_CONTROL |= MotorPWM_CTRL_ENABLE;
    #endif /* (MotorPWM_UseControl || MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_Stop
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
void MotorPWM_Stop(void) 
{
    #if (MotorPWM_UseControl || MotorPWM_UsingFixedFunction)
        MotorPWM_CONTROL &= ~MotorPWM_CTRL_ENABLE;
    #endif /* (MotorPWM_UseControl || MotorPWM_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (MotorPWM_UsingFixedFunction)
        MotorPWM_GLOBAL_ENABLE &= ~MotorPWM_BLOCK_EN_MASK;
        MotorPWM_GLOBAL_STBY_ENABLE &= ~MotorPWM_BLOCK_STBY_EN_MASK;
    #endif /* (MotorPWM_UsingFixedFunction) */
}


#if (MotorPWM_UseOneCompareMode)
#if (MotorPWM_CompareMode1SW)


/*******************************************************************************
* Function Name: MotorPWM_SetCompareMode
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
void MotorPWM_SetCompareMode(uint8 comparemode) 
{
    #if(MotorPWM_UsingFixedFunction)
        #if(CY_PSOC5A)
            uint8 comparemodemasked = (comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT);
            MotorPWM_CONTROL2 &= ~MotorPWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            MotorPWM_CONTROL2 |= comparemodemasked;  
        #endif /* (CY_PSOC5A) */
                
        #if(CY_PSOC3 || CY_PSOC5LP)
            uint8 comparemodemasked = (comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT);
            MotorPWM_CONTROL3 &= ~MotorPWM_CTRL_CMPMODE1_MASK; /*Clear Existing Data */
            MotorPWM_CONTROL3 |= comparemodemasked;     
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
                
    #elif (MotorPWM_UseControl)
        uint8 comparemode1masked = (comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT) & 
                                    MotorPWM_CTRL_CMPMODE1_MASK;
        uint8 comparemode2masked = (comparemode << MotorPWM_CTRL_CMPMODE2_SHIFT) & 
                                   MotorPWM_CTRL_CMPMODE2_MASK;
        /*Clear existing mode */
        MotorPWM_CONTROL &= ~(MotorPWM_CTRL_CMPMODE1_MASK | MotorPWM_CTRL_CMPMODE2_MASK); 
        MotorPWM_CONTROL |= (comparemode1masked | comparemode2masked);
        
    #else
        uint8 temp = comparemode;
    #endif /* (MotorPWM_UsingFixedFunction) */
}
#endif /* MotorPWM_CompareMode1SW */

#else /* UseOneCompareMode */


#if (MotorPWM_CompareMode1SW)


/*******************************************************************************
* Function Name: MotorPWM_SetCompareMode1
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
void MotorPWM_SetCompareMode1(uint8 comparemode) 
{
    uint8 comparemodemasked = (comparemode << MotorPWM_CTRL_CMPMODE1_SHIFT) & 
                               MotorPWM_CTRL_CMPMODE1_MASK;
    #if(MotorPWM_UsingFixedFunction)
        #if(CY_PSOC5A)
            MotorPWM_CONTROL2 &= MotorPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
            MotorPWM_CONTROL2 |= comparemodemasked; 
        #endif /* (CY_PSOC5A) */
                
        #if(CY_PSOC3 || CY_PSOC5LP)
            MotorPWM_CONTROL3 &= MotorPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
            MotorPWM_CONTROL3 |= comparemodemasked; 
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
                
    #elif (MotorPWM_UseControl)
        MotorPWM_CONTROL &= MotorPWM_CTRL_CMPMODE1_MASK; /*Clear existing mode */
        MotorPWM_CONTROL |= comparemodemasked;
    #endif    /* (MotorPWM_UsingFixedFunction) */
}
#endif /* MotorPWM_CompareMode1SW */


#if (MotorPWM_CompareMode2SW)


/*******************************************************************************
* Function Name: MotorPWM_SetCompareMode2
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
void MotorPWM_SetCompareMode2(uint8 comparemode) 
{
    #if(MotorPWM_UsingFixedFunction)
        /* Do Nothing because there is no second Compare Mode Register in FF block */ 
    #elif (MotorPWM_UseControl)
        uint8 comparemodemasked = (comparemode << MotorPWM_CTRL_CMPMODE2_SHIFT) & 
                                             MotorPWM_CTRL_CMPMODE2_MASK;
        MotorPWM_CONTROL &= MotorPWM_CTRL_CMPMODE2_MASK; /*Clear existing mode */
        MotorPWM_CONTROL |= comparemodemasked;
    #endif /* (MotorPWM_UsingFixedFunction) */
}
#endif /*MotorPWM_CompareMode2SW */
#endif /* UseOneCompareMode */


#if (!MotorPWM_UsingFixedFunction)


/*******************************************************************************
* Function Name: MotorPWM_WriteCounter
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
void MotorPWM_WriteCounter(uint16 counter) \
                                   
{
    CY_SET_REG16(MotorPWM_COUNTER_LSB_PTR, counter);
}

/*******************************************************************************
* Function Name: MotorPWM_ReadCounter
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
uint16 MotorPWM_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(MotorPWM_COUNTERCAP_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG16(MotorPWM_CAPTURE_LSB_PTR));
}


#if (MotorPWM_UseStatus)


/*******************************************************************************
* Function Name: MotorPWM_ClearFIFO
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
void MotorPWM_ClearFIFO(void) 
{
    while(MotorPWM_ReadStatusRegister() & MotorPWM_STATUS_FIFONEMPTY)
        MotorPWM_ReadCapture();
}
#endif /* MotorPWM_UseStatus */
#endif /* !MotorPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: MotorPWM_WritePeriod
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
void MotorPWM_WritePeriod(uint16 period) 
{
    #if(MotorPWM_UsingFixedFunction)
        CY_SET_REG16(MotorPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(MotorPWM_PERIOD_LSB_PTR, period);
    #endif /* (MotorPWM_UsingFixedFunction) */
}


#if (MotorPWM_UseOneCompareMode)


/*******************************************************************************
* Function Name: MotorPWM_WriteCompare
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
void MotorPWM_WriteCompare(uint16 compare) \
                                   
{
   CY_SET_REG16(MotorPWM_COMPARE1_LSB_PTR, compare);
   #if (MotorPWM_PWMMode == MotorPWM__B_PWM__DITHER)
        CY_SET_REG16(MotorPWM_COMPARE2_LSB_PTR, compare+1);
   #endif /* (MotorPWM_PWMMode == MotorPWM__B_PWM__DITHER) */
}


#else


/*******************************************************************************
* Function Name: MotorPWM_WriteCompare1
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
void MotorPWM_WriteCompare1(uint16 compare) \
                                    
{
    #if(MotorPWM_UsingFixedFunction)
        CY_SET_REG16(MotorPWM_COMPARE1_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(MotorPWM_COMPARE1_LSB_PTR, compare);
    #endif /* (MotorPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorPWM_WriteCompare2
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
void MotorPWM_WriteCompare2(uint16 compare) \
                                    
{
    #if(MotorPWM_UsingFixedFunction)
        CY_SET_REG16(MotorPWM_COMPARE2_LSB_PTR, compare);
    #else
        CY_SET_REG16(MotorPWM_COMPARE2_LSB_PTR, compare);
    #endif /* (MotorPWM_UsingFixedFunction) */
}
#endif /* UseOneCompareMode */


#if (MotorPWM_DeadBandUsed)


/*******************************************************************************
* Function Name: MotorPWM_WriteDeadTime
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
void MotorPWM_WriteDeadTime(uint8 deadtime) 
{
    /* If using the Dead Band 1-255 mode then just write the register */
    #if(!MotorPWM_DeadBand2_4)
        CY_SET_REG8(MotorPWM_DEADBAND_COUNT_PTR, deadtime);
    #else
        /* Otherwise the data has to be masked and offset */        
        /* Clear existing data */
        MotorPWM_DEADBAND_COUNT &= ~MotorPWM_DEADBAND_COUNT_MASK; 
            /* Set new dead time */
        MotorPWM_DEADBAND_COUNT |= (deadtime << MotorPWM_DEADBAND_COUNT_SHIFT) & 
                                            MotorPWM_DEADBAND_COUNT_MASK; 
    #endif /* (!MotorPWM_DeadBand2_4) */
}


/*******************************************************************************
* Function Name: MotorPWM_ReadDeadTime
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
uint8 MotorPWM_ReadDeadTime(void) 
{
    /* If using the Dead Band 1-255 mode then just read the register */
    #if(!MotorPWM_DeadBand2_4)
        return (CY_GET_REG8(MotorPWM_DEADBAND_COUNT_PTR));
    #else
        /* Otherwise the data has to be masked and offset */
        return ((MotorPWM_DEADBAND_COUNT & MotorPWM_DEADBAND_COUNT_MASK) >> 
                 MotorPWM_DEADBAND_COUNT_SHIFT);
    #endif /* (!MotorPWM_DeadBand2_4) */
}
#endif /* DeadBandUsed */


/* [] END OF FILE */
