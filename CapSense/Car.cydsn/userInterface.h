/* ========================================
 *
 * File Name: userInterface.h
 * 
 * ======================================== */
#ifndef USERINTERFACE_INCLUDED
#define USERINTERFACE_INCLUDED

#define ON           (1)
#define OFF          (0)
#define NO_FINGER    (0xFF)

/* update LCD */
void lcd__updates();

/*-----------------------------------------*/
/* start button interrupt handlers */
void button_Start();

/* left button interrupt handler */
CY_ISR_PROTO(interLeft);

/* right button interrupt handler */
CY_ISR_PROTO(interRight);

/*-----------------------------------------*/
/* Start CapSense and LCD for CapSense */
void sense_Start();

/* Update CapSense in main loop and allow 
for user input from BUTTONS and SLIDER */
void sense_updates();

/*-----------------------------------------*/
#endif
//[] END OF FILE
