/* ========================================
 *
 * File Name: navigation.h
 * 
 * ======================================== */
#ifndef NAVIGATION_INCLUDED
#define NAVIGATION_INCLUDED

/*-----------------------------------------*/
// navigation control initializations
void nav_Start();

/*-----------------------------------------*/
// navigation stop
void nav_Stop();

/*-----------------------------------------*/
// black tape interrupt handler
CY_ISR_PROTO(interTape);

/*-----------------------------------------*/
// frame interrupt handler
CY_ISR_PROTO(interFrame);

/*-----------------------------------------*/
// returns current timer reading in seconds
double navTimer();

/*-----------------------------------------*/
// calculate error for following the line
double navError(double speed);

/*-----------------------------------------*/
// integration control
void navIControl(double dT, double error);

/*-----------------------------------------*/
// derivative control
double navDControl(double time);

/*-----------------------------------------*/
// PID control returning CMP value for PWM
uint8 navPIDControl(double time);

/*-----------------------------------------*/
#endif
//[] END OF FILE
