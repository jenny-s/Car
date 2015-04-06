/*******************************************************************************
* File Name: LineCounter.c  
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

#include "LineCounter.h"

uint8 LineCounter_initVar = 0u;


/*******************************************************************************
* Function Name: LineCounter_Init
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
void LineCounter_Init(void) 
{
        #if (!LineCounter_UsingFixedFunction && !LineCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!LineCounter_UsingFixedFunction && !LineCounter_ControlRegRemoved) */
        
        #if(!LineCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 LineCounter_interruptState;
        #endif /* (!LineCounter_UsingFixedFunction) */
        
        #if (LineCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            LineCounter_CONTROL &= LineCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                LineCounter_CONTROL2 &= ~LineCounter_CTRL_MODE_MASK;
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                LineCounter_CONTROL3 &= ~LineCounter_CTRL_MODE_MASK;                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (LineCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                LineCounter_CONTROL |= LineCounter_ONESHOT;
            #endif /* (LineCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            LineCounter_CONTROL2 |= LineCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            LineCounter_RT1 &= ~LineCounter_RT1_MASK;
            LineCounter_RT1 |= LineCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            LineCounter_RT1 &= ~(LineCounter_SYNCDSI_MASK);
            LineCounter_RT1 |= LineCounter_SYNCDSI_EN;

        #else
            #if(!LineCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = LineCounter_CONTROL & ~LineCounter_CTRL_CMPMODE_MASK;
            LineCounter_CONTROL = ctrl | LineCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = LineCounter_CONTROL & ~LineCounter_CTRL_CAPMODE_MASK;
            LineCounter_CONTROL = ctrl | LineCounter_DEFAULT_CAPTURE_MODE;
            #endif /* (!LineCounter_ControlRegRemoved) */
        #endif /* (LineCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!LineCounter_UsingFixedFunction)
            LineCounter_ClearFIFO();
        #endif /* (!LineCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        LineCounter_WritePeriod(LineCounter_INIT_PERIOD_VALUE);
        #if (!(LineCounter_UsingFixedFunction && (CY_PSOC5A)))
            LineCounter_WriteCounter(LineCounter_INIT_COUNTER_VALUE);
        #endif /* (!(LineCounter_UsingFixedFunction && (CY_PSOC5A))) */
        LineCounter_SetInterruptMode(LineCounter_INIT_INTERRUPTS_MASK);
        
        #if (!LineCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            LineCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            LineCounter_WriteCompare(LineCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LineCounter_interruptState = CyEnterCriticalSection();
            
            LineCounter_STATUS_AUX_CTRL |= LineCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(LineCounter_interruptState);
            
        #endif /* (!LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_Enable
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
void LineCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LineCounter_UsingFixedFunction)
        LineCounter_GLOBAL_ENABLE |= LineCounter_BLOCK_EN_MASK;
        LineCounter_GLOBAL_STBY_ENABLE |= LineCounter_BLOCK_STBY_EN_MASK;
    #endif /* (LineCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!LineCounter_ControlRegRemoved || LineCounter_UsingFixedFunction)
        LineCounter_CONTROL |= LineCounter_CTRL_ENABLE;                
    #endif /* (!LineCounter_ControlRegRemoved || LineCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: LineCounter_Start
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
*  LineCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void LineCounter_Start(void) 
{
    if(LineCounter_initVar == 0u)
    {
        LineCounter_Init();
        
        LineCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    LineCounter_Enable();        
}


/*******************************************************************************
* Function Name: LineCounter_Stop
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
void LineCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!LineCounter_ControlRegRemoved || LineCounter_UsingFixedFunction)
        LineCounter_CONTROL &= ~LineCounter_CTRL_ENABLE;        
    #endif /* (!LineCounter_ControlRegRemoved || LineCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (LineCounter_UsingFixedFunction)
        LineCounter_GLOBAL_ENABLE &= ~LineCounter_BLOCK_EN_MASK;
        LineCounter_GLOBAL_STBY_ENABLE &= ~LineCounter_BLOCK_STBY_EN_MASK;
    #endif /* (LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_SetInterruptMode
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
void LineCounter_SetInterruptMode(uint8 interruptsMask) 
{
    LineCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: LineCounter_ReadStatusRegister
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
uint8   LineCounter_ReadStatusRegister(void) 
{
    return LineCounter_STATUS;
}


#if(!LineCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: LineCounter_ReadControlRegister
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
uint8   LineCounter_ReadControlRegister(void) 
{
    return LineCounter_CONTROL;
}


/*******************************************************************************
* Function Name: LineCounter_WriteControlRegister
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
void    LineCounter_WriteControlRegister(uint8 control) 
{
    LineCounter_CONTROL = control;
}

#endif  /* (!LineCounter_ControlRegRemoved) */


#if (!(LineCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: LineCounter_WriteCounter
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
void LineCounter_WriteCounter(uint32 counter) \
                                   
{
    #if(LineCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (!(LineCounter_GLOBAL_ENABLE & LineCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        LineCounter_GLOBAL_ENABLE |= LineCounter_BLOCK_EN_MASK;
        CY_SET_REG16(LineCounter_COUNTER_LSB_PTR, (uint16)counter);
        LineCounter_GLOBAL_ENABLE &= ~LineCounter_BLOCK_EN_MASK;
    #else
        CY_SET_REG32(LineCounter_COUNTER_LSB_PTR, counter);
    #endif /* (LineCounter_UsingFixedFunction) */
}
#endif /* (!(LineCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: LineCounter_ReadCounter
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
uint32 LineCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(LineCounter_COUNTER_LSB_PTR);
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG32(LineCounter_STATICCOUNT_LSB_PTR));
}


/*******************************************************************************
* Function Name: LineCounter_ReadCapture
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
uint32 LineCounter_ReadCapture(void) 
{
   return ( CY_GET_REG32(LineCounter_STATICCOUNT_LSB_PTR) );  
}


/*******************************************************************************
* Function Name: LineCounter_WritePeriod
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
void LineCounter_WritePeriod(uint32 period) 
{
    #if(LineCounter_UsingFixedFunction)
        CY_SET_REG16(LineCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(LineCounter_PERIOD_LSB_PTR,period);
    #endif /* (LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_ReadPeriod
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
uint32 LineCounter_ReadPeriod(void) 
{
   return ( CY_GET_REG32(LineCounter_PERIOD_LSB_PTR));
}


#if (!LineCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: LineCounter_WriteCompare
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
void LineCounter_WriteCompare(uint32 compare) \
                                   
{
    #if(LineCounter_UsingFixedFunction)
        CY_SET_REG16(LineCounter_COMPARE_LSB_PTR,(uint16)compare);
    #else
        CY_SET_REG32(LineCounter_COMPARE_LSB_PTR,compare);
    #endif /* (LineCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LineCounter_ReadCompare
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
uint32 LineCounter_ReadCompare(void) 
{
   return ( CY_GET_REG32(LineCounter_COMPARE_LSB_PTR));
}


#if (LineCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: LineCounter_SetCompareMode
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
void LineCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    LineCounter_CONTROL &= ~LineCounter_CTRL_CMPMODE_MASK;
    
    /* Write the new setting */
    LineCounter_CONTROL |= (compareMode << LineCounter_CTRL_CMPMODE0_SHIFT);
}
#endif  /* (LineCounter_COMPARE_MODE_SOFTWARE) */


#if (LineCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: LineCounter_SetCaptureMode
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
void LineCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    LineCounter_CONTROL &= ~LineCounter_CTRL_CAPMODE_MASK;
    
    /* Write the new setting */
    LineCounter_CONTROL |= (captureMode << LineCounter_CTRL_CAPMODE0_SHIFT);
}
#endif  /* (LineCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: LineCounter_ClearFIFO
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
void LineCounter_ClearFIFO(void) 
{

    while(LineCounter_ReadStatusRegister() & LineCounter_STATUS_FIFONEMP)
    {
        LineCounter_ReadCapture();
    }

}
#endif  /* (!LineCounter_UsingFixedFunction) */


/* [] END OF FILE */

