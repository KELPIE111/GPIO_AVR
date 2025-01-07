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
    };
}
