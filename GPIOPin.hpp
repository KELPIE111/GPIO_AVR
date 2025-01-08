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

/**
 * @brief A class that allows additional capabilities to be added to a controlled pin.
 *
 * This class extends GPIOPort and provides functionality such as toggling, blinking,
 * debouncing, and configuring PWM on a specific pin.
 */
namespace jm
{
    class GPIOPin : public GPIOPort
    {
    public:
        /**
         * @brief Constructs a GPIOPin object with the specified port and pin number.
         *
         * @param portName The name of the port (e.g., 'B', 'C', 'D').
         * @param pinNr The pin number within the port (0-7).
         */
        GPIOPin(char portName, uint8_t pinNr)
            : GPIOPort(portName, pinNr) {}

        /**
         * @brief Sets the direction of the pin.
         *
         * @param inOut Set to true for output, false for input.
         */
        void setDirection(bool inOut) override
        {
            if (inOut)
            {
                *m_DDR |= getMask();
            }
            else
            {
                *m_DDR &= ~getMask();
            }
        }

        /**
         * @brief Writes a state to the pin.
         *
         * @param state Set to true to drive the pin high, false to drive it low.
         */
        void write(bool state) override
        {
            if (state)
            {
                *m_PORT |= getMask();
            }
            else
            {
                *m_PORT &= ~getMask();
            }
        }

        /**
         * @brief Reads the current state of the pin.
         *
         * @return True if the pin is high, false otherwise.
         */
        bool read() const override
        {
            return (*m_PIN & getMask()) != 0;
        }

        /**
         * @brief Enables or disables the pull-up resistor on the pin.
         *
         * @param on Set to true to enable the pull-up resistor, false to disable it.
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

        /**
         * @brief Toggles the state of the pin.
         */
        void toggle()
        {
            *m_PORT ^= getMask();
        }

        /**
         * @brief Blinks the pin at the specified delay and number of times.
         *
         * @param delay The delay in milliseconds between state changes.
         * @param times The number of times to toggle the pin.
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

        /**
         * @brief Eliminates the debouncing effect when using a button or key.
         *
         * @return True if the pin state is stable and consistent, false otherwise.
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

        /**
         * @brief Configures PWM functionality on the selected pin.
         *
         * @param timer The timer to use (0, 1, or 2).
         * @param fill The duty cycle (0-255 for 8-bit timers, or 0-65535 for 16-bit timers).
         * @param channel The PWM channel ('A' or 'B').
         * @param prescaler The prescaler value (0-7).
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
