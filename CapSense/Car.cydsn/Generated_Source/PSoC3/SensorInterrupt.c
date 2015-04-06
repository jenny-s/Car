/*******************************************************************************
* File Name: SensorInterrupt.c  
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
#include <SensorInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START SensorInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: SensorInterrupt_Start
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
void SensorInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    SensorInterrupt_Disable();

    /* Set the ISR to point to the SensorInterrupt Interrupt. */
    SensorInterrupt_SetVector(SensorInterrupt_Interrupt);

    /* Set the priority. */
    SensorInterrupt_SetPriority(SensorInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    SensorInterrupt_Enable();
}

/*******************************************************************************
* Function Name: SensorInterrupt_StartEx
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
void SensorInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    SensorInterrupt_Disable();

    /* Set the ISR to point to the SensorInterrupt Interrupt. */
    SensorInterrupt_SetVector(address);

    /* Set the priority. */
    SensorInterrupt_SetPriority(SensorInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    SensorInterrupt_Enable();
}

/*******************************************************************************
* Function Name: SensorInterrupt_Stop
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
void SensorInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    SensorInterrupt_Disable();
}

/*******************************************************************************
* Function Name: SensorInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for SensorInterrupt.
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
CY_ISR(SensorInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START SensorInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (SensorInterrupt__ES2_PATCH ))      
            SensorInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: SensorInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling SensorInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use SensorInterrupt_StartEx instead.
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
void SensorInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(SensorInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: SensorInterrupt_GetVector
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
cyisraddress SensorInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(SensorInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: SensorInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling SensorInterrupt_Start
*   or SensorInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after SensorInterrupt_Start or 
*	SensorInterrupt_StartEx has been called. To set the initial
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
void SensorInterrupt_SetPriority(uint8 priority) 
{
    *SensorInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: SensorInterrupt_GetPriority
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
uint8 SensorInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *SensorInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: SensorInterrupt_Enable
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
void SensorInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *SensorInterrupt_INTC_SET_EN = SensorInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: SensorInterrupt_GetState
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
uint8 SensorInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*SensorInterrupt_INTC_SET_EN & SensorInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: SensorInterrupt_Disable
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
void SensorInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *SensorInterrupt_INTC_CLR_EN = SensorInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: SensorInterrupt_SetPending
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
void SensorInterrupt_SetPending(void) 
{
    *SensorInterrupt_INTC_SET_PD = SensorInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: SensorInterrupt_ClearPending
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
void SensorInterrupt_ClearPending(void) 
{
    *SensorInterrupt_INTC_CLR_PD = SensorInterrupt__INTC_MASK;
}
