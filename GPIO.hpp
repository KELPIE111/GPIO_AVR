#pragma once

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