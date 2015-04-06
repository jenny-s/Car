/*******************************************************************************
* File Name: Pin_Camera.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Pin_Camera.h"


/*******************************************************************************
* Function Name: Pin_Camera_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Pin_Camera_Write(uint8 value) 
{
    uint8 staticBits = Pin_Camera_DR & ~Pin_Camera_MASK;
    Pin_Camera_DR = staticBits | ((value << Pin_Camera_SHIFT) & Pin_Camera_MASK);
}


/*******************************************************************************
* Function Name: Pin_Camera_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Pin_Camera_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin_Camera_0, mode);
}


/*******************************************************************************
* Function Name: Pin_Camera_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Pin_Camera_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin_Camera_Read(void) 
{
    return (Pin_Camera_PS & Pin_Camera_MASK) >> Pin_Camera_SHIFT;
}


/*******************************************************************************
* Function Name: Pin_Camera_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Pin_Camera_ReadDataReg(void) 
{
    return (Pin_Camera_DR & Pin_Camera_MASK) >> Pin_Camera_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin_Camera_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin_Camera_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Pin_Camera_ClearInterrupt(void) 
    {
        return (Pin_Camera_INTSTAT & Pin_Camera_MASK) >> Pin_Camera_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
