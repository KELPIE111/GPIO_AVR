/*
 * 2024
 * Project: GPIO_AVR
 * Creator: Jakub Marszalek
 * File: GPIO.hpp
 *
 */

#pragma once

/*
 * It is a class containing virtual methods used in inheriting classes and a destructor.
 */

namespace jm
{
    class GPIO
    {
    public:
        virtual void setDirection(bool inOut) = 0;
        virtual void write(bool state) = 0;
        virtual bool read() const = 0;
        virtual ~GPIO() = default;
    };
}
