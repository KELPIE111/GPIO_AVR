/*
 * 2024
 * Project: GPIO_AVR
 * Creator: Jakub Marszalek
 * File: GPIOPort.hpp
 *
 */

#pragma once
#include <avr/io.h>
#include "GPIO.hpp"

/*
 * This is a class for basic activities related to ports.
 * Methods for extracting the necessary information from the given values ​​in the constructor.
 */

namespace jm
{
    class GPIOPort : public GPIO
    {
    private:
        /*
         * Methods to select appropriate registers.
         * DDRX, PORTX, PINX
         * where X = B || C || D
         */
        static volatile uint8_t *getDDR(char portName)
        {
            switch (portName)
            {
            case 'B':
                return &DDRB;
            case 'C':
                return &DDRC;
            case 'D':
                return &DDRD;
            default:
                return nullptr;
            }
        }

        static volatile uint8_t *getPORT(char portName)
        {
            switch (portName)
            {
            case 'B':
                return &PORTB;
            case 'C':
                return &PORTC;
            case 'D':
                return &PORTD;
            default:
                return nullptr;
            }
        }

        static volatile uint8_t *getPIN(char portName)
        {
            switch (portName)
            {
            case 'B':
                return &PINB;
            case 'C':
                return &PINC;
            case 'D':
                return &PIND;
            default:
                return nullptr;
            }
        }

    protected:
        /*
         * Fields with appropriate registers.
         */
        volatile uint8_t *m_DDR;
        volatile uint8_t *m_PORT;
        volatile uint8_t *m_PIN;
        uint8_t m_pinNr;

        /*
         * A method for creating the appropriate mask. Used in further methods.
         */
        uint8_t getMask() const
        {
            return (1 << m_pinNr);
        }

    public:
        /*
         * Parametric constructor using appropriate methods.
         * If a wrong value is given, the program will stop in an infinite loop.
         */
        GPIOPort(char portName, uint8_t pinNr)
            : m_DDR(getDDR(portName)), m_PORT(getPORT(portName)), m_PIN(getPIN(portName)), m_pinNr(pinNr)
        {
            if (!m_DDR || !m_PIN || !m_PORT)
            {
                while (1)
                {
                }
            }
        }

        /*
         * basic methods for setting direction, writing or reading
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

        bool read() const override
        {
            return (*m_PIN & getMask()) != 0;
        }
    };
}
