/*******************************************************************************
* File Name: SensorPin.c  
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
#include "SensorPin.h"


/*******************************************************************************
* Function Name: SensorPin_Write
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
void SensorPin_Write(uint8 value) 
{
    uint8 staticBits = SensorPin_DR & ~SensorPin_MASK;
    SensorPin_DR = staticBits | ((value << SensorPin_SHIFT) & SensorPin_MASK);
}


/*******************************************************************************
* Function Name: SensorPin_SetDriveMode
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
void SensorPin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SensorPin_0, mode);
}


/*******************************************************************************
* Function Name: SensorPin_Read
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
*  Macro SensorPin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SensorPin_Read(void) 
{
    return (SensorPin_PS & SensorPin_MASK) >> SensorPin_SHIFT;
}


/*******************************************************************************
* Function Name: SensorPin_ReadDataReg
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
uint8 SensorPin_ReadDataReg(void) 
{
    return (SensorPin_DR & SensorPin_MASK) >> SensorPin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SensorPin_INTSTAT) 

    /*******************************************************************************
    * Function Name: SensorPin_ClearInterrupt
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
    uint8 SensorPin_ClearInterrupt(void) 
    {
        return (SensorPin_INTSTAT & SensorPin_MASK) >> SensorPin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
