/*
 * File:   MOTOR.c
 * Author: aswin
 *
 * Created on 14 June, 2024, 2:36 PM
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

// Function prototypes
void DCmotor(int speed);
void initPIC();

unsigned char button;

void DCmotor(int speed) {
    if (speed == 1) {
        /*
         * PWM registers configuration for 300 Hz, 50% duty cycle.
         * Fosc = 4 MHz, Fpwm = 300.48 Hz, Duty Cycle = 50%, Resolution is 10 bits, Prescaler is 16.
         */
        PR2 = 0b11001111; // Set PR2 value for 300 Hz
        T2CON = 0b00000111; // Timer2 on, Prescaler: 1:16
        CCPR1L = 0b01100111; // Set the duty cycle to 50%
        CCP1CON = 0b00111100; // PWM mode, CCP1M3:0 = 0b00111100
    } 
    else if (speed == 2) {
        /*
         * PWM registers configuration for 700 Hz, 70% duty cycle.
         * Fosc = 4 MHz, Fpwm = 702.25 Hz, Duty Cycle = 70%, Resolution is 10 bits, Prescaler is 16.
         */
        PR2 = 0b01011000; // Set PR2 value for 700 Hz
        T2CON = 0b00000111; // Timer2 on, Prescaler: 1:16
        CCPR1L = 0b00111110; // Set the duty cycle to 70%
        CCP1CON = 0b00011100; // PWM mode, CCP1M3:0 = 0b00011100
    } 
    else if (speed == 3) {
        /*
         * PWM registers configuration for 1000 Hz, 50% duty cycle.
         * Fosc = 4 MHz, Fpwm = 1000 Hz, Duty Cycle = 50%, Resolution is 10 bits, Prescaler is 4.
         */
        PR2 = 0b11111001; // Set PR2 value for 1000 Hz
        T2CON = 0b00000101; // Timer2 on, Prescaler: 1:4
        CCPR1L = 0b11111100; // Set the duty cycle to 50%
        CCP1CON = 0b00111100; // PWM mode, CCP1M3:0 = 0b00111100
    } 
    else {
        /*
         * PWM registers configuration for 0 Hz (motor off).
         * Fosc = 4 MHz, Fpwm = 0 Hz, Duty Cycle = 0%, Resolution is 10 bits, Prescaler is 16.
         */
        CCPR1L = 0b00000000;
        CCP1CON = 0b00000000; // Turn off PWM
    }
}

void initPIC() {
    __CONFIG(0x3FF9); // Configuration bits: Code Protection Off, WDT Disabled, XT Oscillator
    TRISC = 0x00; // Set PORTC as output
    PORTC = 0; // Clear PORTC
    TRISD = 0xFF; // Set PORTD as input for buttons
    PORTD = 0; // Clear PORTD
}

void main() {
    initPIC();

    while (1) {
        button = PORTD; // Read the state of PORTD
        
        if (button == 0x20) {
            DCmotor(1);
        } 
        else if (button == 0x40) {
            DCmotor(2);
        } 
        else if (button == 0x80) {
            DCmotor(3);
        } 
        else {
            DCmotor(0);
        }
    }
}
