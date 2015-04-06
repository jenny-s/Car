/*******************************************************************************
* File Name: RightButtonInterrupt.c  
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
#include <RightButtonInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START RightButtonInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: RightButtonInterrupt_Start
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
void RightButtonInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    RightButtonInterrupt_Disable();

    /* Set the ISR to point to the RightButtonInterrupt Interrupt. */
    RightButtonInterrupt_SetVector(RightButtonInterrupt_Interrupt);

    /* Set the priority. */
    RightButtonInterrupt_SetPriority(RightButtonInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RightButtonInterrupt_Enable();
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_StartEx
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
void RightButtonInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    RightButtonInterrupt_Disable();

    /* Set the ISR to point to the RightButtonInterrupt Interrupt. */
    RightButtonInterrupt_SetVector(address);

    /* Set the priority. */
    RightButtonInterrupt_SetPriority(RightButtonInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    RightButtonInterrupt_Enable();
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_Stop
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
void RightButtonInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    RightButtonInterrupt_Disable();
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for RightButtonInterrupt.
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
CY_ISR(RightButtonInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START RightButtonInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (RightButtonInterrupt__ES2_PATCH ))      
            RightButtonInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling RightButtonInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use RightButtonInterrupt_StartEx instead.
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
void RightButtonInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(RightButtonInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_GetVector
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
cyisraddress RightButtonInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(RightButtonInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling RightButtonInterrupt_Start
*   or RightButtonInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after RightButtonInterrupt_Start or 
*	RightButtonInterrupt_StartEx has been called. To set the initial
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
void RightButtonInterrupt_SetPriority(uint8 priority) 
{
    *RightButtonInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_GetPriority
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
uint8 RightButtonInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *RightButtonInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_Enable
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
void RightButtonInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *RightButtonInterrupt_INTC_SET_EN = RightButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_GetState
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
uint8 RightButtonInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*RightButtonInterrupt_INTC_SET_EN & RightButtonInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_Disable
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
void RightButtonInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *RightButtonInterrupt_INTC_CLR_EN = RightButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_SetPending
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
void RightButtonInterrupt_SetPending(void) 
{
    *RightButtonInterrupt_INTC_SET_PD = RightButtonInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: RightButtonInterrupt_ClearPending
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
void RightButtonInterrupt_ClearPending(void) 
{
    *RightButtonInterrupt_INTC_CLR_PD = RightButtonInterrupt__INTC_MASK;
}
