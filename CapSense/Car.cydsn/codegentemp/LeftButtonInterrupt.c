/*******************************************************************************
* File Name: LeftButtonInterrupt.c  
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
#include <LeftButtonInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START LeftButtonInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: LeftButtonInterrupt_Start
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
void LeftButtonInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    LeftButtonInterrupt_Disable();

    /* Set the ISR to point to the LeftButtonInterrupt Interrupt. */
    LeftButtonInterrupt_SetVector(LeftButtonInterrupt_Interrupt);

    /* Set the priority. */
    LeftButtonInterrupt_SetPriority(LeftButtonInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LeftButtonInterrupt_Enable();
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_StartEx
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
void LeftButtonInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    LeftButtonInterrupt_Disable();

    /* Set the ISR to point to the LeftButtonInterrupt Interrupt. */
    LeftButtonInterrupt_SetVector(address);

    /* Set the priority. */
    LeftButtonInterrupt_SetPriority(LeftButtonInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LeftButtonInterrupt_Enable();
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_Stop
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
void LeftButtonInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    LeftButtonInterrupt_Disable();
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for LeftButtonInterrupt.
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
CY_ISR(LeftButtonInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START LeftButtonInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (LeftButtonInterrupt__ES2_PATCH ))      
            LeftButtonInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling LeftButtonInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use LeftButtonInterrupt_StartEx instead.
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
void LeftButtonInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(LeftButtonInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_GetVector
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
cyisraddress LeftButtonInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(LeftButtonInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling LeftButtonInterrupt_Start
*   or LeftButtonInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after LeftButtonInterrupt_Start or 
*	LeftButtonInterrupt_StartEx has been called. To set the initial
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
void LeftButtonInterrupt_SetPriority(uint8 priority) 
{
    *LeftButtonInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_GetPriority
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
uint8 LeftButtonInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *LeftButtonInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_Enable
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
void LeftButtonInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *LeftButtonInterrupt_INTC_SET_EN = LeftButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_GetState
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
uint8 LeftButtonInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*LeftButtonInterrupt_INTC_SET_EN & LeftButtonInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_Disable
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
void LeftButtonInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *LeftButtonInterrupt_INTC_CLR_EN = LeftButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_SetPending
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
void LeftButtonInterrupt_SetPending(void) 
{
    *LeftButtonInterrupt_INTC_SET_PD = LeftButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LeftButtonInterrupt_ClearPending
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
void LeftButtonInterrupt_ClearPending(void) 
{
    *LeftButtonInterrupt_INTC_CLR_PD = LeftButtonInterrupt__INTC_MASK;
}
