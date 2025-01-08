/*
 * 2024
 * Project: GPIO_AVR
 * Creator: Jakub Marszalek
 * File: GPIOPin.hpp
 *
 */

#pragma once
#include "GPIOPort.hpp"
#include "util/delay.h"

namespace jm
{
    /*
     * A class that allows you to add additional capabilities to the controlled pin.
     */
    class GPIOPin : public GPIOPort
    {
    public:
        /*
         * A constructor that allows you to enter the port name and pin number when creating an object.
         */
        GPIOPin(char portName, uint8_t pinNr)
            : GPIOPort(portName, pinNr) {}

        /*
         * It allows you to add a pull up resistor to the pin.
         */
        void pullUp(bool on)
        {
            if (on)
            {
                *m_PORT |= getMask();
            }
            else
            {
                *m_PORT &= ~getMask();
            }
        }

        /*
         * Allows you to change the state of the pin.
         */
        void toggle()
        {
            *m_PORT ^= getMask();
        }

        /*
         * It allows the LED to blink at an appropriate frequency specified by the use.
         */
        void blink(uint16_t delay, uint8_t times)
        {
            for (uint8_t i = 0; i < times; i++)
            {
                write(true);
                _delay_ms(delay);
                write(false);
                _delay_ms(delay);
            }
        }

        /*
         * It allows you to eliminate the phenomenon of debouncing when using the keys
         */
        bool debounced()
        {
            bool firstRead{read()};
            _delay_ms(50);
            bool secondRead{read()};
            if (firstRead == secondRead)
            {
                return firstRead;
            }
            else
            {
                return false;
            }
        }

        /*
         * It allows you to set the PWM function on the selected pin.
         * The user enters the clock he wants to use, the fill, the channel and the prescaler value from 0 to 7.
         */
        void configurePWM(uint8_t timer, uint8_t fill, char channel, uint8_t prescaler)
        {
            if (timer == 0)
            {
                if (channel == 'A')
                {
                    TCCR0A |= (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
                    OCR0A = fill;
                }
                else if (channel == 'B')
                {
                    TCCR0A |= (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
                    OCR0B = fill;
                }
                TCCR0B = (TCCR0B & 0xF8) | (prescaler & 0x07);
            }
            else if (timer == 1)
            {
                if (channel == 'A')
                {
                    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
                    OCR1A = fill;
                }
                else if (channel == 'B')
                {
                    TCCR1A |= (1 << COM1B1) | (1 << WGM11);
                    OCR1B = fill;
                }
                TCCR1B |= (1 << WGM12) | (1 << WGM13);
                ICR1 = 16000;
                TCCR1B = (TCCR1B & 0xF8) | (prescaler & 0x07);
            }
            else if (timer == 2)
            {
                if (channel == 'A')
                {
                    TCCR2A |= (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
                    OCR2A = fill;
                }
                else if (channel == 'B')
                {
                    TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
                    OCR2B = fill;
                }
                TCCR2B = (TCCR2B & 0xF8) | (prescaler & 0x07);
            }
        }
    };
}
