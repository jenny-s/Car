/******************************************************************************
 * File Name: navigation.c
 * Version 1.1
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
#include "navigation.h"

/* GLOBAL VARIABLES */
double navintegralSum = 0;     // discrete sum of integral
double navprevTime = 0;
double navthisTime = 0;
double navprevError = 0;
double navthisError = 0;
double errorCount = 0;

/*-----------------------------------------*/
// navigation control initializations
void nav_Start() {
    FrameInterrupt_Start();               
    FrameInterrupt_SetVector(interFrame);
    TapeInterrupt_Start();                  // start timer for tape position
    TapeInterrupt_SetVector(interTape);
    TapeTimer_Start();  
    CVComp_Start();                         // start CVComp
    LineCounter_Start();
    ServoPWM_Start();                       // start ServoPWM
    ServoPWM_WriteCompare(140);             // initial cycle PWM pulse-width
}

/*-----------------------------------------*/
// navigation control initializations
void nav_Stop() {
    ServoPWM_Stop();
}
    
/*-----------------------------------------*/
// black tape interrupt handler
CY_ISR(interTape) {
    uint8 cmp;                             // CMP value for PWM
    double begin = (double) navTimer();
    double time1 = (double) navTimer(); // time that the camera saw the tape
    double time2 = (double) navTimer();
    double end = (double) navTimer();
    double time =  begin - ((time1 + time2) / 2);

    if ((begin - end) > .000049 && (begin - end) < .000052)
        cmp = navPIDControl(time);

    // WRITE new pulse width based on PID after each pulse
    ServoPWM_WriteCompare(cmp);
}

/*-----------------------------------------*/
// line interrupt handler
CY_ISR(interFrame) {
    TapeTimer_ClearFIFO();
}

/*---------------------------------------------------------------------------*/
// returns current timer reading in seconds
double navTimer() {
    float clkSpeed = 1000000.0; // in Hz
    float time = (float)TapeTimer_ReadCapture() / clkSpeed;
    SensorTimer_ReadStatusRegister();
    
    return (double)time;
}
/*---------------------------------------------------------------------------*/
// calculate error for goal speed
double navError(double time) {
    double TIMEGOAL = 0.0000243; // calibrated goal time for displacement = 25.4.1us
    double error = TIMEGOAL - time;
    
    if (errorCount == 5) {
        navprevError = navthisError;
        navthisError = error;
        navprevTime = time;
        navthisTime = time;
    }
    
    return TIMEGOAL - time;
}

/*---------------------------------------------------------------------------*/
// integration control
void navIControl(double dT, double error) {
    navintegralSum += error * dT;
}

/*---------------------------------------------------------------------------*/
// derivative control
double navDControl(double time) {
    double dD = (navthisError - navprevError) / (time - navprevTime) ;
    return dD;
}

/*---------------------------------------------------------------------------*/
// PID control method returning CMP value for PWM
uint8 navPIDControl(double time) { 
    double cmp;                     // CMP value for servoPWM_WriteCompare param
    double periodPWM = 1000;        // period of motorPWM component
    double openLoop = 150;          // open loop control constant 
    double navKp = 15;              // constant for P control 
    double navKi = 0;               // constant for I control
    double navKd = 7;               // constant for D control
    double error = navError(time);  // PID error
    
    /* PID control calculation */
    cmp = openLoop - 100000*(navKp * error) + navKi * navintegralSum; // only contains PI for now

    // set bounds for cmp
    if (cmp < 110) cmp = 110;
    else if (cmp > 190) cmp = 190;
    
    // return CMP value for sensorPWM_WriteCompare input param
    return (uint8)cmp;
}

/*-----------------------------------------*/
/* [] END OF FILE */
