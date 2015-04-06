/******************************************************************************
 * File Name: userInterface.c
 * Version 2.1
 * 
 * Authors: Jenny & Allie
 * 
 * Description:
 * Speed Control using PI control
 * 
 * Dependencies: stdio.h, device.h, speedcontrol.h
 * 
 * Code Tested with: 
 * PSoC Creator: PSoC Creator 2.1
 * Device tested with: CY8C3866AXI-040 
 * Compiler: DP8051 Keil 8.16
*******************************************************************************/

#include <device.h>
#include <stdio.h>
#include "userInterface.h"
#include "speedControl.h"
#include "navigation.h"

// global variables for CapSense
static uint8 statusButton0 = OFF;
static uint8 statusButton1 = OFF;
static uint16 sliderPosition = NO_FINGER;
static uint16 lastPosition = NO_FINGER;

// global variable to control LCD update rate
int tick = 0;

/******************************************************************************
*                               LCD SCREEN
* 
* Hardware connection on the Kit
* LCD - P2[0] through P6[6]
******************************************************************************/ 

/* update LCD screen */
void lcd__updates() {
    char buffer1[20];   // LCD buffer for LINE 1
    char buffer2[20];   // LCD buffer for LINE 2
    
    // update tick count for update rate
    tick++;

    
    // at rate of 5 ticks...
    if (tick == 20) {
        LCD_Position(0,7);
        // clear previous
        LCD_PrintString("    ");
        // LINE 1: print the current speed to LCD
        LCD_Position(0,0);
        sprintf(buffer1, "SPEED: %.1f ft/s  ", speed);
        LCD_PrintString(buffer1);
        
        tick = 0;  // reset tick
    }
    
    // LINE 2: print the goal speed to LCD
    LCD_Position(1,0);
    sprintf(buffer2, "GOAL: %.1f ft/s", GOAL);
    LCD_PrintString(buffer2);

}

/******************************************************************************
*                   LEFT AND RIGHT SWITCHES FOR DIGITAL ON/OFF
* 
* Hardware connection on the Kit
* LeftButton - P6[1]
* RightButton - P15[5]
******************************************************************************/ 

/* start button interrupt handlers */
void button_Start() {
    LeftButtonInterrupt_Start();                // start left button interrupt handler
    LeftButtonInterrupt_SetVector(interLeft);   // set up left button interrupt
    RightButtonInterrupt_Start();               // start right button interrupt handler
    RightButtonInterrupt_SetVector(interRight); // set up right button interrupt
}

/*---------------------------------------------------------------------------*/
/* Interrupt handler for left button */
CY_ISR(interLeft) {
    /* START CAR */
    speed_Start();
   // start navigation
    nav_Start();
}

/*---------------------------------------------------------------------------*/
/* Interrupt handler for right button */
CY_ISR(interRight) {
    /* STOP CAR */
    speed_Stop();
    nav_Stop();
}

/******************************************************************************
*                             CAPSENSE OPERATION
* 
* Hardware connection on the Kit
* Slider - P5[0] - P5[4]
* Button1 - P5[5]
* Button2 - P5[6]
* LCD 2[0-6]
******************************************************************************/ 

/* Start CapSense and LCD for CapSense */
void sense_Start() {        
    /* Start capsense and initialize baselines and enable scan */
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
}

/*---------------------------------------------------------------------------*/
/* Update CapSense in main loop and allow for user input from BUTTONS and SLIDER */
void sense_updates() {
    // variables for the buttons and slider to change
    int button1 = 0;
    int button2 = 0;
    int slider = 0;
    
    /* If scanning is completed update the baseline count and check if sensor is active */  
    if(!CapSense_IsBusy())
    {
        /* Update baseline for all the sensors */
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
    
        /* Test if button widget is active */
        statusButton0 = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
        statusButton1 = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
        sliderPosition =(uint8)CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);

        /********************* LEFT CAPSENSE BUTTON CONTROL ******************/
        if( statusButton0 == ON )
        {
            /* CURRENTLY DOES NOTHING */
        }
        else
        {
            /* CURRENTLY DOES NOTHING */
        }

        /********************* RIGHT CAPSENSE BUTTON CONTROL *****************/
        if( statusButton1 == ON )
        {
            /* CURRENTLY DOES NOTHING */
        }
        else
        {
            /* CURRENTLY DOES NOTHING */
        }


        /*************************** SLIDER CONTROL **************************/
        /* Finger not detected on slider */
	    if(sliderPosition == NO_FINGER)
        {  
        
        }
        
        /* Finger detected on the slider */
        else
        {
            /* If finger position on the slider is changed then update GOAL speed */
            if(sliderPosition != lastPosition)
            {
                // goal speed range of 3 ft/s to 6.3 ft/s
                GOAL = ((double)sliderPosition / 30) + 3;
                
                // update slider positon
                lastPosition = sliderPosition; 
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/* [] END OF FILE */
