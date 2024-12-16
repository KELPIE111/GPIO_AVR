#include <Arduino.h>
#include <avr/io.h>
#include "GPIOPin.hpp"
#include "util/delay.h"

int main()
{
  jm::GPIOPin led('B', PB0);
  jm::GPIOPin button('D', PD7);

  // test blink and toggle
  /*led.setDirection(true);
  led.write(1);
  _delay_ms(1000);
  led.toggle();
  _delay_ms(1000);
  led.blink(500, 10);*/

  button.setDirection(false);
  button.pullUp(true);
  while (1)
  {
    // test pullUp
    /*if (!button.read())
    {
      led.write(true);
    }
    else
    {
      led.write(false);
    }
    */

    if (!button.debounced())
    {
      led.write(true);
    }
    else
    {
      led.write(false);
    }
  }
  return 0;
}