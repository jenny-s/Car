/*******************************************************************************
* File Name: CompSynchCounter.c  
* Version 2.20
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 CompSynchCounter_initVar = 0u;


/*******************************************************************************
* Function Name: CompSynchCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void CompSynchCounter_Init(void) 
{
        #if (!CompSynchCounter_UsingFixedFunction && !CompSynchCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!CompSynchCounter_UsingFixedFunction && !CompSynchCounter_ControlRegRemoved) */
        
        #if(!CompSynchCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 CompSynchCounter_interruptState;
        #endif /* (!CompSynchCounter_UsingFixedFunction) */
        
        #if (CompSynchCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            CompSynchCounter_CONTROL &= CompSynchCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                CompSynchCounter_CONTROL2 &= ~CompSynchCounter_CTRL_MODE_MASK;
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                CompSynchCounter_CONTROL3 &= ~CompSynchCounter_CTRL_MODE_MASK;                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (CompSynchCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                CompSynchCounter_CONTROL |= CompSynchCounter_ONESHOT;
            #endif /* (CompSynchCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            CompSynchCounter_CONTROL2 |= CompSynchCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            CompSynchCounter_RT1 &= ~CompSynchCounter_RT1_MASK;
            CompSynchCounter_RT1 |= CompSynchCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            CompSynchCounter_RT1 &= ~(CompSynchCounter_SYNCDSI_MASK);
            CompSynchCounter_RT1 |= CompSynchCounter_SYNCDSI_EN;

        #else
            #if(!CompSynchCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = CompSynchCounter_CONTROL & ~CompSynchCounter_CTRL_CMPMODE_MASK;
            CompSynchCounter_CONTROL = ctrl | CompSynchCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = CompSynchCounter_CONTROL & ~CompSynchCounter_CTRL_CAPMODE_MASK;
            CompSynchCounter_CONTROL = ctrl | CompSynchCounter_DEFAULT_CAPTURE_MODE;
            #endif /* (!CompSynchCounter_ControlRegRemoved) */
        #endif /* (CompSynchCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!CompSynchCounter_UsingFixedFunction)
            CompSynchCounter_ClearFIFO();
        #endif /* (!CompSynchCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        CompSynchCounter_WritePeriod(CompSynchCounter_INIT_PERIOD_VALUE);
        #if (!(CompSynchCounter_UsingFixedFunction && (CY_PSOC5A)))
            CompSynchCounter_WriteCounter(CompSynchCounter_INIT_COUNTER_VALUE);
        #endif /* (!(CompSynchCounter_UsingFixedFunction && (CY_PSOC5A))) */
        CompSynchCounter_SetInterruptMode(CompSynchCounter_INIT_INTERRUPTS_MASK);
        
        #if (!CompSynchCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            CompSynchCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            CompSynchCounter_WriteCompare(CompSynchCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            CompSynchCounter_interruptState = CyEnterCriticalSection();
            
            CompSynchCounter_STATUS_AUX_CTRL |= CompSynchCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(CompSynchCounter_interruptState);
            
        #endif /* (!CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void CompSynchCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (CompSynchCounter_UsingFixedFunction)
        CompSynchCounter_GLOBAL_ENABLE |= CompSynchCounter_BLOCK_EN_MASK;
        CompSynchCounter_GLOBAL_STBY_ENABLE |= CompSynchCounter_BLOCK_STBY_EN_MASK;
    #endif /* (CompSynchCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!CompSynchCounter_ControlRegRemoved || CompSynchCounter_UsingFixedFunction)
        CompSynchCounter_CONTROL |= CompSynchCounter_CTRL_ENABLE;                
    #endif /* (!CompSynchCounter_ControlRegRemoved || CompSynchCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: CompSynchCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  CompSynchCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void CompSynchCounter_Start(void) 
{
    if(CompSynchCounter_initVar == 0u)
    {
        CompSynchCounter_Init();
        
        CompSynchCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    CompSynchCounter_Enable();        
}


/*******************************************************************************
* Function Name: CompSynchCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void CompSynchCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!CompSynchCounter_ControlRegRemoved || CompSynchCounter_UsingFixedFunction)
        CompSynchCounter_CONTROL &= ~CompSynchCounter_CTRL_ENABLE;        
    #endif /* (!CompSynchCounter_ControlRegRemoved || CompSynchCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (CompSynchCounter_UsingFixedFunction)
        CompSynchCounter_GLOBAL_ENABLE &= ~CompSynchCounter_BLOCK_EN_MASK;
        CompSynchCounter_GLOBAL_STBY_ENABLE &= ~CompSynchCounter_BLOCK_STBY_EN_MASK;
    #endif /* (CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void CompSynchCounter_SetInterruptMode(uint8 interruptsMask) 
{
    CompSynchCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: CompSynchCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   CompSynchCounter_ReadStatusRegister(void) 
{
    return CompSynchCounter_STATUS;
}


#if(!CompSynchCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: CompSynchCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   CompSynchCounter_ReadControlRegister(void) 
{
    return CompSynchCounter_CONTROL;
}


/*******************************************************************************
* Function Name: CompSynchCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    CompSynchCounter_WriteControlRegister(uint8 control) 
{
    CompSynchCounter_CONTROL = control;
}

#endif  /* (!CompSynchCounter_ControlRegRemoved) */


#if (!(CompSynchCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: CompSynchCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void CompSynchCounter_WriteCounter(uint32 counter) \
                                   
{
    #if(CompSynchCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (!(CompSynchCounter_GLOBAL_ENABLE & CompSynchCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        CompSynchCounter_GLOBAL_ENABLE |= CompSynchCounter_BLOCK_EN_MASK;
        CY_SET_REG16(CompSynchCounter_COUNTER_LSB_PTR, (uint16)counter);
        CompSynchCounter_GLOBAL_ENABLE &= ~CompSynchCounter_BLOCK_EN_MASK;
    #else
        CY_SET_REG32(CompSynchCounter_COUNTER_LSB_PTR, counter);
    #endif /* (CompSynchCounter_UsingFixedFunction) */
}
#endif /* (!(CompSynchCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: CompSynchCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 CompSynchCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(CompSynchCounter_COUNTER_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG32(CompSynchCounter_STATICCOUNT_LSB_PTR));
}


/*******************************************************************************
* Function Name: CompSynchCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 CompSynchCounter_ReadCapture(void) 
{
   return ( CY_GET_REG32(CompSynchCounter_STATICCOUNT_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: CompSynchCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void CompSynchCounter_WritePeriod(uint32 period) 
{
    #if(CompSynchCounter_UsingFixedFunction)
        CY_SET_REG16(CompSynchCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(CompSynchCounter_PERIOD_LSB_PTR,period);
    #endif /* (CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 CompSynchCounter_ReadPeriod(void) 
{
   return ( CY_GET_REG32(CompSynchCounter_PERIOD_LSB_PTR));
}


#if (!CompSynchCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: CompSynchCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void CompSynchCounter_WriteCompare(uint32 compare) \
                                   
{
    #if(CompSynchCounter_UsingFixedFunction)
        CY_SET_REG16(CompSynchCounter_COMPARE_LSB_PTR,(uint16)compare);
    #else
        CY_SET_REG32(CompSynchCounter_COMPARE_LSB_PTR,compare);
    #endif /* (CompSynchCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: CompSynchCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 CompSynchCounter_ReadCompare(void) 
{
   return ( CY_GET_REG32(CompSynchCounter_COMPARE_LSB_PTR));
}


#if (CompSynchCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CompSynchCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CompSynchCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    CompSynchCounter_CONTROL &= ~CompSynchCounter_CTRL_CMPMODE_MASK;
    
    /* Write the new setting */
    CompSynchCounter_CONTROL |= (compareMode << CompSynchCounter_CTRL_CMPMODE0_SHIFT);
}
#endif  /* (CompSynchCounter_COMPARE_MODE_SOFTWARE) */


#if (CompSynchCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: CompSynchCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void CompSynchCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    CompSynchCounter_CONTROL &= ~CompSynchCounter_CTRL_CAPMODE_MASK;
    
    /* Write the new setting */
    CompSynchCounter_CONTROL |= (captureMode << CompSynchCounter_CTRL_CAPMODE0_SHIFT);
}
#endif  /* (CompSynchCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: CompSynchCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void CompSynchCounter_ClearFIFO(void) 
{

    while(CompSynchCounter_ReadStatusRegister() & CompSynchCounter_STATUS_FIFONEMP)
    {
        CompSynchCounter_ReadCapture();
    }

}
#endif  /* (!CompSynchCounter_UsingFixedFunction) */


/* [] END OF FILE */

