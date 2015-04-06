/* ========================================
 *
 * File Name: userInterface.h
 * 
 * ======================================== */
#ifndef SPEEDCONTROL_INCLUDED
#define SPEEDCONTROL_INCLUDED

// extern GOAL SPEED
extern double GOAL;  // GOAL SPEED = 3ft/s
extern double speed; // current speed value in ft/s
extern double Kp;
extern double Ki;
extern double Kd;
extern int dist;

/*-----------------------------------------*/
// speed control initializations
void speed_Start();

/*-----------------------------------------*/
// speed control stop
void speed_Stop();

/*-----------------------------------------*/
// sensor interrupt handler
CY_ISR_PROTO(interSensor);

/*-----------------------------------------*/
// returns current timer reading in seconds
double Timer();

/*-----------------------------------------*/
// calculate current speed in ft/s
double Speed(double time);

/*-----------------------------------------*/
// calculate error for goal speed of 3ft/s
double Error(double speed);

/*-----------------------------------------*/
// integration control
void IControl(double dT, double error);

/*-----------------------------------------*/
// derivative control (DOES NOTHING)
double DControl(double speed);

/*-----------------------------------------*/
// PID control returning CMP value for PWM
uint8 PIDControl(double speed);

/*-----------------------------------------*/
#endif
//[] END OF FILE
