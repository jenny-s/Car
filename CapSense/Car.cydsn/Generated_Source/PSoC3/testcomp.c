/*******************************************************************************
* File Name: testcomp.c  
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
#include "testcomp.h"


/*******************************************************************************
* Function Name: testcomp_Write
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
void testcomp_Write(uint8 value) 
{
    uint8 staticBits = testcomp_DR & ~testcomp_MASK;
    testcomp_DR = staticBits | ((value << testcomp_SHIFT) & testcomp_MASK);
}


/*******************************************************************************
* Function Name: testcomp_SetDriveMode
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
void testcomp_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(testcomp_0, mode);
}


/*******************************************************************************
* Function Name: testcomp_Read
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
*  Macro testcomp_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 testcomp_Read(void) 
{
    return (testcomp_PS & testcomp_MASK) >> testcomp_SHIFT;
}


/*******************************************************************************
* Function Name: testcomp_ReadDataReg
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
uint8 testcomp_ReadDataReg(void) 
{
    return (testcomp_DR & testcomp_MASK) >> testcomp_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(testcomp_INTSTAT) 

    /*******************************************************************************
    * Function Name: testcomp_ClearInterrupt
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
    uint8 testcomp_ClearInterrupt(void) 
    {
        return (testcomp_INTSTAT & testcomp_MASK) >> testcomp_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
