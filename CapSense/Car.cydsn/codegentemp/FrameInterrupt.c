/*******************************************************************************
* File Name: FrameInterrupt.c  
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
#include <FrameInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START FrameInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: FrameInterrupt_Start
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
void FrameInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    FrameInterrupt_Disable();

    /* Set the ISR to point to the FrameInterrupt Interrupt. */
    FrameInterrupt_SetVector(FrameInterrupt_Interrupt);

    /* Set the priority. */
    FrameInterrupt_SetPriority(FrameInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    FrameInterrupt_Enable();
}

/*******************************************************************************
* Function Name: FrameInterrupt_StartEx
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
void FrameInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    FrameInterrupt_Disable();

    /* Set the ISR to point to the FrameInterrupt Interrupt. */
    FrameInterrupt_SetVector(address);

    /* Set the priority. */
    FrameInterrupt_SetPriority(FrameInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    FrameInterrupt_Enable();
}

/*******************************************************************************
* Function Name: FrameInterrupt_Stop
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
void FrameInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    FrameInterrupt_Disable();
}

/*******************************************************************************
* Function Name: FrameInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for FrameInterrupt.
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
CY_ISR(FrameInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START FrameInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (FrameInterrupt__ES2_PATCH ))      
            FrameInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: FrameInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling FrameInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use FrameInterrupt_StartEx instead.
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
void FrameInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(FrameInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: FrameInterrupt_GetVector
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
cyisraddress FrameInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(FrameInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: FrameInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling FrameInterrupt_Start
*   or FrameInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after FrameInterrupt_Start or 
*	FrameInterrupt_StartEx has been called. To set the initial
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
void FrameInterrupt_SetPriority(uint8 priority) 
{
    *FrameInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: FrameInterrupt_GetPriority
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
uint8 FrameInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *FrameInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: FrameInterrupt_Enable
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
void FrameInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *FrameInterrupt_INTC_SET_EN = FrameInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: FrameInterrupt_GetState
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
uint8 FrameInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*FrameInterrupt_INTC_SET_EN & FrameInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: FrameInterrupt_Disable
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
void FrameInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *FrameInterrupt_INTC_CLR_EN = FrameInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: FrameInterrupt_SetPending
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
void FrameInterrupt_SetPending(void) 
{
    *FrameInterrupt_INTC_SET_PD = FrameInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: FrameInterrupt_ClearPending
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
void FrameInterrupt_ClearPending(void) 
{
    *FrameInterrupt_INTC_CLR_PD = FrameInterrupt__INTC_MASK;
}
