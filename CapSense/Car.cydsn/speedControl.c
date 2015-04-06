/******************************************************************************
 * File Name: speedControl.c
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <device.h>
#include "speedControl.h"

/* GLOBAL VARIABLES */
double prevTime = 42949.6;  // time of previous sensor interrupt in seconds
double prevError = 3;       // previous error for integral calculation
double integralSum = 0;     // discrete sum of integral
int tickCount = 0;       // track ticks for restarting integral calculation
// declare and initialize externs
double GOAL = 3.0;          // initial goal speed prior to slider input
double speed = 0;           // track current speed
double Kp = 50;             // constant for P control 
double Ki = 42;             // constant for I control
double Kd = 0;              // constant for D control

int dist = 0;

/*---------------------------------------------------------------------------*/
// start car and speed control initializations
void speed_Start() {
    SensorInterrupt_Start();                // start interrupt handler
    SensorInterrupt_SetVector(interSensor); // set up interrupt
    SensorTimer_Start();                    // start sensorTimer
    MotorPWM_Start();                       // start motorPWM
    MotorPWM_WriteCompare(50);              // initial cycle PWM pulse-width
}

/*---------------------------------------------------------------------------*/
// stop car
void speed_Stop() {
    MotorPWM_Stop();
    SensorInterrupt_Stop();
    SensorTimer_Stop();
}

/*---------------------------------------------------------------------------*/
// sensor interrupt handler
CY_ISR(interSensor) {
    double time = Timer();          // READ from sensorTimer_ReadCapture()
    double dT = prevTime - time;    // calculate elapsed time
    double error;
    uint8 cmp;                      // CMP value for PWM

    speed = Speed(dT);       // speed of car at time of interrupt
    error = Error(speed);    // error in speed of car at time of interrupt
    
    // calculate integral term
    IControl(dT, error);
    cmp = PIDControl(speed);

    // WRITE new pulse width based on PID after each pulse
    MotorPWM_WriteCompare(cmp);
    
    // update previous time
    prevTime = time; 
     
    // reset integral calculation ~every 4 ft (30.5 ticks = 4ft)
    tickCount++;
    if (tickCount == 10) {
        integralSum = 0;
    }
    
    dist++;
    if (dist >= 1600) speed_Stop();
}

/*---------------------------------------------------------------------------*/
// returns current timer reading in seconds
double Timer() {
    float clkSpeed = 100000.0; // in Hz
    float time = (float)SensorTimer_ReadCapture() / clkSpeed;
    SensorTimer_ReadStatusRegister();
    
    return (double)time;
}

// calculate current speed in ft/s
double Speed(double dT) {
    // calculations
    double CIRC = .6544974223;    // circumference of wheel in feet (calculated on paper)
    double DISTANCE = CIRC / 5.0; // distance between each of five magnets
    double speed = DISTANCE / dT; // speed in m/s
    
    return speed;
}

/*---------------------------------------------------------------------------*/
// calculate error for goal speed
double Error(double speed) {
//    double GOAL = 3.0;  // GOAL SPEED = 3ft/s
    
    return GOAL - speed;
}

/*---------------------------------------------------------------------------*/
// integration control
void IControl(double dT, double error) {
    integralSum += error * dT;
}

/*---------------------------------------------------------------------------*/
// derivative control
double DControl(double speed) {
    double dD = 0;
    return dD;
}

/*---------------------------------------------------------------------------*/
// PID control method returning CMP value for PWM
uint8 PIDControl(double speed) {
    double cmp;             // CMP value for sensorPWM_WriteCompare input param
    double periodPWM = 255; // period of motorPWM component
    double openLoop = 40;   // open loop control constant 
    
    double error = Error(speed);
    
    /* PID control calculation */
    cmp = openLoop + Kp * error + Ki * integralSum; // only contains PI for now
    
    // set bounds for cmp
    if (cmp < 0) cmp = 0;
    else if (cmp > periodPWM) cmp = periodPWM;
    
    // return CMP value for sensorPWM_WriteCompare input param
    return (uint8)cmp;
}

/*---------------------------------------------------------------------------*/
/* [] END OF FILE */
