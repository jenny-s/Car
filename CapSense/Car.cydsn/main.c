/******************************************************************************
* File Name: Main.c
* Version 2.1 (with capsense and buttons)
*
* Authors: Jenny & Allie
*
* Description:
* Left switch (P6_1) turns car "on" and right switch (P15_5) turns car "off".
* CapSense slider changes speed at any time, with a range of 3ft/s to 6ft/s.
* Speed is regulated with PI feedback control
*
* Dependencies: device.h, userInterface.h, speedControl.h
* 
* Code Tested with: 
* PSoC Creator: PSoC Creator 2.1
* Device tested with: CY8C3866AXI-040 
* Compiler: DP8051 Keil 8.16
*******************************************************************************/

#include <device.h>
#include "userInterface.h"
#include "speedControl.h"
#include "navigation.h"

/*---------------------------------------------------------------------------*/
void main()
{
    CYGlobalIntEnable; 
    // start LCD
    LCD_Start();
    // start CapSense
    sense_Start();
    // start buttons
    button_Start();


    for(;;)
    {
        lcd__updates();
        
        sense_updates();
    }    
}

/*---------------------------------------------------------------------------*/
/* [] END OF FILE */

