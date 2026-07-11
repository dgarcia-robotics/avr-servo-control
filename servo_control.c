/*
 * Assignment 12.1: Servo Control
 * Author: David Garcia
 *
 * Bare-metal AVR C (ATmega328P, Microchip/Atmel Studio).
 * Timer1 Fast PWM (mode 14, ICR1 = TOP) generates a 50 Hz servo signal on OC1A (D9).
 * Two push buttons increment/decrement the pulse width to sweep the servo.
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Servo pulse limits
#define PULSE_MIN   999U
#define PULSE_MAX   4799U
#define PULSE_MID   2899U
#define TOP_VALUE   39999U   // 50 Hz period (20 ms)

// Pin definitions
#define BTN_INC     PD2     // Button 1 (increment)
#define BTN_DEC     PD3     // Button 2 (decrement)

int main(void)
{
    // ---- Timer1 Setup for 50 Hz PWM on OC1A (D9) ----
    ICR1 = TOP_VALUE;
    TCCR1A |= (1 << WGM11);                     // Fast PWM, mode 14 (ICR1 top)
    TCCR1A |= (1 << COM1A1);                    // Clear OC1A on compare match
    TCCR1B |= (1 << WGM12) | (1 << WGM13);      // Continue mode 14 bits
    TCCR1B |= (1 << CS11);                      // Prescaler = 8

    DDRB |= (1 << PB1);                         // D9 (OC1A) as output

    // ---- Button Inputs ----
    DDRD &= ~((1 << BTN_INC) | (1 << BTN_DEC)); // D2, D3 as inputs
    // No internal pull-ups since external pull-downs are used

    // ---- Variables ----
    uint16_t pulse = PULSE_MID;
    OCR1A = pulse;

    // ---- Main Loop ----
    while (1)
    {
        // Read the two buttons
        uint8_t pins = PIND;

        // Increment servo angle
        if (pins & (1 << BTN_INC))
        {
            if (pulse + 20 <= PULSE_MAX)
                pulse += 20;
        }

        // Decrement servo angle
        if (pins & (1 << BTN_DEC))
        {
            if (pulse >= PULSE_MIN + 20)
                pulse -= 20;
        }

        // Update PWM compare value
        OCR1A = pulse;

        // Adjust this delay to control servo speed
        _delay_ms(10);
    }
}
