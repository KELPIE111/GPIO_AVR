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

/**
 * @brief A class for basic activities related to AVR ports.
 *
 * This class provides methods for extracting the necessary information from the given values
 * in the constructor and managing port registers for DDR, PORT, and PIN operations.
 */

namespace jm
{
    class GPIOPort : public GPIO
    {
    private:
        /**
         * @brief Selects the appropriate DDR register for the specified port.
         *
         * @param portName The name of the port (e.g., 'B', 'C', 'D').
         * @return Pointer to the DDR register or nullptr if the port name is invalid.
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

        /**
         * @brief Selects the appropriate PORT register for the specified port.
         *
         * @param portName The name of the port (e.g., 'B', 'C', 'D').
         * @return Pointer to the PORT register or nullptr if the port name is invalid.
         */
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

        /**
         * @brief Selects the appropriate PIN register for the specified port.
         *
         * @param portName The name of the port (e.g., 'B', 'C', 'D').
         * @return Pointer to the PIN register or nullptr if the port name is invalid.
         */
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
        /**
         * Pointer to the DDR register of the port.
         */
        volatile uint8_t *m_DDR;

        /**
         * Pointer to the PORT register of the port.
         */
        volatile uint8_t *m_PORT;

        /**
         * Pointer to the PIN register of the port.
         */
        volatile uint8_t *m_PIN;

        /**
         * The pin number within the port.
         */
        uint8_t m_pinNr;

        /**
         * @brief Creates a bitmask for the specified pin.
         *
         * @return A bitmask with the bit corresponding to the pin number set to 1.
         */
        uint8_t getMask() const
        {
            return (1 << m_pinNr);
        }

    public:
        /**
         * @brief Constructs a GPIOPort object with the specified port and pin number.
         *
         * This constructor initializes the pointers to the appropriate DDR, PORT, and PIN registers.
         * If an invalid port name is provided, the program enters an infinite loop.
         *
         * @param portName The name of the port (e.g., 'B', 'C', 'D').
         * @param pinNr The pin number within the port (0-7).
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
    };
}