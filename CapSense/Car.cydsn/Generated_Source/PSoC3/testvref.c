/*******************************************************************************
* File Name: testvref.c  
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
#include "testvref.h"


/*******************************************************************************
* Function Name: testvref_Write
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
void testvref_Write(uint8 value) 
{
    uint8 staticBits = testvref_DR & ~testvref_MASK;
    testvref_DR = staticBits | ((value << testvref_SHIFT) & testvref_MASK);
}


/*******************************************************************************
* Function Name: testvref_SetDriveMode
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
void testvref_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(testvref_0, mode);
}


/*******************************************************************************
* Function Name: testvref_Read
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
*  Macro testvref_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 testvref_Read(void) 
{
    return (testvref_PS & testvref_MASK) >> testvref_SHIFT;
}


/*******************************************************************************
* Function Name: testvref_ReadDataReg
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
uint8 testvref_ReadDataReg(void) 
{
    return (testvref_DR & testvref_MASK) >> testvref_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(testvref_INTSTAT) 

    /*******************************************************************************
    * Function Name: testvref_ClearInterrupt
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
    uint8 testvref_ClearInterrupt(void) 
    {
        return (testvref_INTSTAT & testvref_MASK) >> testvref_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
