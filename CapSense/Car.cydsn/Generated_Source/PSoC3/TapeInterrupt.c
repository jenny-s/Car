/*******************************************************************************
* File Name: TapeInterrupt.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <TapeInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START TapeInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: TapeInterrupt_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void TapeInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    TapeInterrupt_Disable();

    /* Set the ISR to point to the TapeInterrupt Interrupt. */
    TapeInterrupt_SetVector(TapeInterrupt_Interrupt);

    /* Set the priority. */
    TapeInterrupt_SetPriority(TapeInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TapeInterrupt_Enable();
}

/*******************************************************************************
* Function Name: TapeInterrupt_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void TapeInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    TapeInterrupt_Disable();

    /* Set the ISR to point to the TapeInterrupt Interrupt. */
    TapeInterrupt_SetVector(address);

    /* Set the priority. */
    TapeInterrupt_SetPriority(TapeInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TapeInterrupt_Enable();
}

/*******************************************************************************
* Function Name: TapeInterrupt_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void TapeInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    TapeInterrupt_Disable();
}

/*******************************************************************************
* Function Name: TapeInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for TapeInterrupt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(TapeInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START TapeInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (TapeInterrupt__ES2_PATCH ))      
            TapeInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: TapeInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling TapeInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use TapeInterrupt_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(TapeInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: TapeInterrupt_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress TapeInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(TapeInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: TapeInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling TapeInterrupt_Start
*   or TapeInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after TapeInterrupt_Start or 
*	TapeInterrupt_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_SetPriority(uint8 priority) 
{
    *TapeInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: TapeInterrupt_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 TapeInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *TapeInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: TapeInterrupt_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *TapeInterrupt_INTC_SET_EN = TapeInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: TapeInterrupt_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 TapeInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*TapeInterrupt_INTC_SET_EN & TapeInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: TapeInterrupt_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *TapeInterrupt_INTC_CLR_EN = TapeInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: TapeInterrupt_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_SetPending(void) 
{
    *TapeInterrupt_INTC_SET_PD = TapeInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: TapeInterrupt_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void TapeInterrupt_ClearPending(void) 
{
    *TapeInterrupt_INTC_CLR_PD = TapeInterrupt__INTC_MASK;
}
