/*
 * 2024
 * Project: GPIO_AVR
 * Creator: Jakub Marszalek
 * File: main.cpp
 *
 */

#include <Arduino.h>
#include <avr/io.h>
#include "GPIOPin.hpp"
#include "util/delay.h"

int main()
{
  jm::GPIOPin ledB('B', PB0);
  jm::GPIOPin ledCp('C', PB3);
  jm::GPIOPin ledCd('C', PB4);
  jm::GPIOPin button('D', PD7);

  // test blink and toggle
  ledB.setDirection(true);
  ledB.write(1);
  _delay_ms(1000);
  ledB.toggle();
  _delay_ms(1000);
  ledB.blink(500, 10);

  // test button
  button.setDirection(false);
  button.pullUp(true);
  while (1)
  {
    // test pullUp
    if (!button.read())
    {
      ledCp.write(true);
    }
    else
    {
      ledCp.write(false);
    }

    // test debounced
    if (!button.debounced())
    {
      ledCd.write(true);
    }
    else
    {
      ledCd.write(false);
    }
  }
  return 0;
}
