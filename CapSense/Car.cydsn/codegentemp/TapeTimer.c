/*******************************************************************************
* File Name: TapeTimer.c
* Version 2.30
*
* Description:
*  The Timer component consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TapeTimer.h"

uint8 TapeTimer_initVar = 0u;


/*******************************************************************************
* Function Name: TapeTimer_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_Init(void) 
{
    #if(!TapeTimer_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 TapeTimer_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (TapeTimer_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        TapeTimer_CONTROL &= TapeTimer_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            TapeTimer_CONTROL2 &= ~TapeTimer_CTRL_MODE_MASK;
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            TapeTimer_CONTROL3 &= ~TapeTimer_CTRL_MODE_MASK;
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (TapeTimer_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            TapeTimer_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (TapeTimer_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                TapeTimer_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                TapeTimer_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (TapeTimer_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                TapeTimer_CONTROL2 |= TapeTimer_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                TapeTimer_CONTROL3 &= ~TapeTimer_CTRL_RCOD_MASK;
                TapeTimer_CONTROL3 |= TapeTimer_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                TapeTimer_CONTROL3 &= ~TapeTimer_CTRL_ENBL_MASK;
                TapeTimer_CONTROL3 |= TapeTimer_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                TapeTimer_CONTROL3 |= TapeTimer_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        TapeTimer_RT1 &= ~TapeTimer_RT1_MASK;
        TapeTimer_RT1 |= TapeTimer_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        TapeTimer_RT1 &= ~(TapeTimer_SYNCDSI_MASK);
        TapeTimer_RT1 |= TapeTimer_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        TapeTimer_CONTROL2 |= TapeTimer_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    TapeTimer_WritePeriod(TapeTimer_INIT_PERIOD);
    TapeTimer_WriteCounter(TapeTimer_INIT_PERIOD);

    #if (TapeTimer_UsingHWCaptureCounter)/* Capture counter is enabled */
        TapeTimer_CAPTURE_COUNT_CTRL |= TapeTimer_CNTR_ENABLE;
        TapeTimer_SetCaptureCount(TapeTimer_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!TapeTimer_UsingFixedFunction)
        #if (TapeTimer_SoftwareCaptureMode)
            TapeTimer_SetCaptureMode(TapeTimer_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (TapeTimer_SoftwareTriggerMode)
            if (!(TapeTimer_CONTROL & TapeTimer__B_TIMER__TM_SOFTWARE))
            {
                TapeTimer_SetTriggerMode(TapeTimer_INIT_TRIGGER_MODE);
            }
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        TapeTimer_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        TapeTimer_STATUS_AUX_CTRL |= TapeTimer_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(TapeTimer_interruptState);

        #if (TapeTimer_EnableTriggerMode)
            TapeTimer_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/

        #if (TapeTimer_InterruptOnCaptureCount)
             #if (!TapeTimer_ControlRegRemoved)
                TapeTimer_SetInterruptCount(TapeTimer_INIT_INT_CAPTURE_COUNT);
            #endif /* Set interrupt count in control register if control register is not removed */
        #endif /*Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        TapeTimer_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    TapeTimer_SetInterruptMode(TapeTimer_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: TapeTimer_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (TapeTimer_UsingFixedFunction)
        TapeTimer_GLOBAL_ENABLE |= TapeTimer_BLOCK_EN_MASK;
        TapeTimer_GLOBAL_STBY_ENABLE |= TapeTimer_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!TapeTimer_ControlRegRemoved || TapeTimer_UsingFixedFunction)
        TapeTimer_CONTROL |= TapeTimer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: TapeTimer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TapeTimer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void TapeTimer_Start(void) 
{
    if(TapeTimer_initVar == 0u)
    {
        TapeTimer_Init();

        TapeTimer_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    TapeTimer_Enable();
}


/*******************************************************************************
* Function Name: TapeTimer_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
*
*******************************************************************************/
void TapeTimer_Stop(void) 
{
    /* Disable Timer */
    #if(!TapeTimer_ControlRegRemoved || TapeTimer_UsingFixedFunction)
        TapeTimer_CONTROL &= ~TapeTimer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (TapeTimer_UsingFixedFunction)
        TapeTimer_GLOBAL_ENABLE &= ~TapeTimer_BLOCK_EN_MASK;
        TapeTimer_GLOBAL_STBY_ENABLE &= ~TapeTimer_BLOCK_STBY_EN_MASK;
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: TapeTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_SetInterruptMode(uint8 interruptMode) 
{
    TapeTimer_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: TapeTimer_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void TapeTimer_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    CY_GET_REG8(TapeTimer_COUNTER_LSB_PTR);
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: TapeTimer_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
*******************************************************************************/
uint8   TapeTimer_ReadStatusRegister(void) 
{
    return TapeTimer_STATUS;
}


#if (!TapeTimer_ControlRegRemoved) /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TapeTimer_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
*******************************************************************************/
uint8 TapeTimer_ReadControlRegister(void) 
{
    return TapeTimer_CONTROL;
}


/*******************************************************************************
* Function Name: TapeTimer_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
*******************************************************************************/
void TapeTimer_WriteControlRegister(uint8 control) 
{
    TapeTimer_CONTROL = control;
}
#endif /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TapeTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
*******************************************************************************/
uint32 TapeTimer_ReadPeriod(void) 
{
   return ( CY_GET_REG32(TapeTimer_PERIOD_LSB_PTR) );
}


/*******************************************************************************
* Function Name: TapeTimer_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_WritePeriod(uint32 period) 
{
    #if(TapeTimer_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(TapeTimer_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG32(TapeTimer_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: TapeTimer_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
*******************************************************************************/
uint32 TapeTimer_ReadCapture(void) 
{
   return ( CY_GET_REG32(TapeTimer_CAPTURE_LSB_PTR) );
}


/*******************************************************************************
* Function Name: TapeTimer_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_WriteCounter(uint32 counter) \
                                   
{
   #if(TapeTimer_UsingFixedFunction)
        counter = counter;
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        /* uint16 counter_temp = (uint16)counter;
         * CY_SET_REG16(TapeTimer_COUNTER_LSB_PTR, counter_temp);
         */
    #else
        CY_SET_REG32(TapeTimer_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: TapeTimer_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
*******************************************************************************/
uint32 TapeTimer_ReadCounter(void) 
{

    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    CY_GET_REG8(TapeTimer_COUNTER_LSB_PTR);

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    return (CY_GET_REG32(TapeTimer_CAPTURE_LSB_PTR));
}


#if(!TapeTimer_UsingFixedFunction) /* UDB Specific Functions */

/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (TapeTimer_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: TapeTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define TapeTimer__B_TIMER__CM_NONE 0
#define TapeTimer__B_TIMER__CM_RISINGEDGE 1
#define TapeTimer__B_TIMER__CM_FALLINGEDGE 2
#define TapeTimer__B_TIMER__CM_EITHEREDGE 3
#define TapeTimer__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  TapeTimer__B_TIMER__CM_NONE        - Set Capture mode to None
*  TapeTimer__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  TapeTimer__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  TapeTimer__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = (captureMode << TapeTimer_CTRL_CAP_MODE_SHIFT);
    captureMode &= (TapeTimer_CTRL_CAP_MODE_MASK);

    /* Clear the Current Setting */
    TapeTimer_CONTROL &= ~TapeTimer_CTRL_CAP_MODE_MASK;

    /* Write The New Setting */
    TapeTimer_CONTROL |= captureMode;
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (TapeTimer_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: TapeTimer_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define TapeTimer__B_TIMER__TM_NONE 0x00u
    #define TapeTimer__B_TIMER__TM_RISINGEDGE 0x04u
    #define TapeTimer__B_TIMER__TM_FALLINGEDGE 0x08u
    #define TapeTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define TapeTimer__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= TapeTimer_CTRL_TRIG_MODE_MASK;

    /* Clear the Current Setting */
    TapeTimer_CONTROL &= ~TapeTimer_CTRL_TRIG_MODE_MASK;

    /* Write The New Setting */
    TapeTimer_CONTROL |= (triggerMode | TapeTimer__B_TIMER__TM_SOFTWARE);

}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (TapeTimer_EnableTriggerMode)


/*******************************************************************************
* Function Name: TapeTimer_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_EnableTrigger(void) 
{
    #if (!TapeTimer_ControlRegRemoved)   /* Remove assignment if control register is removed */
        TapeTimer_CONTROL |= TapeTimer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: TapeTimer_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_DisableTrigger(void) 
{
    #if (!TapeTimer_ControlRegRemoved)   /* Remove assignment if control register is removed */
        TapeTimer_CONTROL &= ~TapeTimer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */


#if(TapeTimer_InterruptOnCaptureCount)
#if (!TapeTimer_ControlRegRemoved)   /* Remove API if control register is removed */


/*******************************************************************************
* Function Name: TapeTimer_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= TapeTimer_CTRL_INTCNT_MASK;

    /* Clear the Current Setting */
    TapeTimer_CONTROL &= ~TapeTimer_CTRL_INTCNT_MASK;
    /* Write The New Setting */
    TapeTimer_CONTROL |= interruptCount;
}
#endif /* Remove API if control register is removed */
#endif /* TapeTimer_InterruptOnCaptureCount */


#if (TapeTimer_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: TapeTimer_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
*******************************************************************************/
void TapeTimer_SetCaptureCount(uint8 captureCount) 
{
    TapeTimer_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: TapeTimer_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 TapeTimer_ReadCaptureCount(void) 
{
    return TapeTimer_CAP_COUNT ;
}
#endif /* TapeTimer_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: TapeTimer_ClearFIFO
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
void TapeTimer_ClearFIFO(void) 
{
    while(TapeTimer_ReadStatusRegister() & TapeTimer_STATUS_FIFONEMP)
    {
        TapeTimer_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */
