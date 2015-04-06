/*******************************************************************************
* File Name: testcounter.c  
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
#include "testcounter.h"


/*******************************************************************************
* Function Name: testcounter_Write
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
void testcounter_Write(uint8 value) 
{
    uint8 staticBits = testcounter_DR & ~testcounter_MASK;
    testcounter_DR = staticBits | ((value << testcounter_SHIFT) & testcounter_MASK);
}


/*******************************************************************************
* Function Name: testcounter_SetDriveMode
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
void testcounter_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(testcounter_0, mode);
}


/*******************************************************************************
* Function Name: testcounter_Read
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
*  Macro testcounter_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 testcounter_Read(void) 
{
    return (testcounter_PS & testcounter_MASK) >> testcounter_SHIFT;
}


/*******************************************************************************
* Function Name: testcounter_ReadDataReg
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
uint8 testcounter_ReadDataReg(void) 
{
    return (testcounter_DR & testcounter_MASK) >> testcounter_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(testcounter_INTSTAT) 

    /*******************************************************************************
    * Function Name: testcounter_ClearInterrupt
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
    uint8 testcounter_ClearInterrupt(void) 
    {
        return (testcounter_INTSTAT & testcounter_MASK) >> testcounter_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
