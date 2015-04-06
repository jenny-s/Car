/*******************************************************************************
* File Name: sensor_Pin.c  
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
#include "sensor_Pin.h"


/*******************************************************************************
* Function Name: sensor_Pin_Write
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
void sensor_Pin_Write(uint8 value) 
{
    uint8 staticBits = sensor_Pin_DR & ~sensor_Pin_MASK;
    sensor_Pin_DR = staticBits | ((value << sensor_Pin_SHIFT) & sensor_Pin_MASK);
}


/*******************************************************************************
* Function Name: sensor_Pin_SetDriveMode
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
void sensor_Pin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(sensor_Pin_0, mode);
}


/*******************************************************************************
* Function Name: sensor_Pin_Read
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
*  Macro sensor_Pin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 sensor_Pin_Read(void) 
{
    return (sensor_Pin_PS & sensor_Pin_MASK) >> sensor_Pin_SHIFT;
}


/*******************************************************************************
* Function Name: sensor_Pin_ReadDataReg
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
uint8 sensor_Pin_ReadDataReg(void) 
{
    return (sensor_Pin_DR & sensor_Pin_MASK) >> sensor_Pin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(sensor_Pin_INTSTAT) 

    /*******************************************************************************
    * Function Name: sensor_Pin_ClearInterrupt
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
    uint8 sensor_Pin_ClearInterrupt(void) 
    {
        return (sensor_Pin_INTSTAT & sensor_Pin_MASK) >> sensor_Pin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
