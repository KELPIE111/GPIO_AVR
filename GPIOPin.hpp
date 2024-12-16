#pragma once
#include "GPIOPort.hpp"
#include "util/delay.h"

namespace jm
{
    class GPIOPin : public GPIOPort
    {
    public:
        GPIOPin(char portName, uint8_t pinNr)
            : GPIOPort(portName, pinNr) {}

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

        void toggle()
        {
            *m_PORT ^= getMask();
        }

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