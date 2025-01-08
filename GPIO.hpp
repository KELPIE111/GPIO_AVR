/*
 * 2024
 * Project: GPIO_AVR
 * Creator: Jakub Marszalek
 * File: GPIO.hpp
 *
 * @file GPIO.hpp
 * @brief Header file defining the GPIO class.
 *
 * This file contains the definition of the GPIO class, which includes virtual methods
 * that must be implemented by derived classes. The class is intended to provide an
 * interface for controlling General Purpose Input/Output (GPIO) pins.
 */

#pragma once

namespace jm
{
    /**
     * @class GPIO
     * @brief Abstract base class for GPIO operations.
     *
     * This class provides an interface for controlling GPIO pins. It includes
     * virtual methods for setting the direction, writing to, and reading from a GPIO pin.
     * Derived classes must implement these methods to interact with specific hardware.
     */
    class GPIO
    {
    public:
        /**
         * @brief Set the direction of the GPIO pin.
         *
         * This method sets the direction of the GPIO pin, either input or output.
         *
         * @param inOut A boolean value where true sets the direction to input,
         *              and false sets it to output.
         */
        virtual void setDirection(bool inOut) = 0;

        /**
         * @brief Write a value to the GPIO pin.
         *
         * This method writes a state to the GPIO pin. The state can either be
         * high (true) or low (false).
         *
         * @param state The value to write to the pin (true for high, false for low).
         */
        virtual void write(bool state) = 0;

        /**
         * @brief Read the value from the GPIO pin.
         *
         * This method reads the current state of the GPIO pin.
         *
         * @return bool The current state of the GPIO pin (true for high, false for low).
         */
        virtual bool read() const = 0;

        /**
         * @brief Destructor for the GPIO class.
         *
         * The destructor is virtual to allow proper cleanup of derived classes.
         */
        virtual ~GPIO() = default;
    };
}
