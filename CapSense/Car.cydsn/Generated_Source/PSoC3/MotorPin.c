/*******************************************************************************
* File Name: MotorPin.c  
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
#include "MotorPin.h"


/*******************************************************************************
* Function Name: MotorPin_Write
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
void MotorPin_Write(uint8 value) 
{
    uint8 staticBits = MotorPin_DR & ~MotorPin_MASK;
    MotorPin_DR = staticBits | ((value << MotorPin_SHIFT) & MotorPin_MASK);
}


/*******************************************************************************
* Function Name: MotorPin_SetDriveMode
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
void MotorPin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MotorPin_0, mode);
}


/*******************************************************************************
* Function Name: MotorPin_Read
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
*  Macro MotorPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MotorPin_Read(void) 
{
    return (MotorPin_PS & MotorPin_MASK) >> MotorPin_SHIFT;
}


/*******************************************************************************
* Function Name: MotorPin_ReadDataReg
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
uint8 MotorPin_ReadDataReg(void) 
{
    return (MotorPin_DR & MotorPin_MASK) >> MotorPin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MotorPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: MotorPin_ClearInterrupt
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
    uint8 MotorPin_ClearInterrupt(void) 
    {
        return (MotorPin_INTSTAT & MotorPin_MASK) >> MotorPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
