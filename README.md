Introduction
This project is a library for General Purpose Input/Output (GPIO) handling for AVR microcontrollers. 
Its main goal is to simplify working with microcontroller ports by providing an object-oriented interface that allows operations such as:

Setting the pin direction (input/output).
Reading the logical state of the pin.
Writing the logical state to the pin.
Enabling the pull-up resistor.
Debouncing the switch.
Generating PWM signals on selected pins.
Blinking an LED at a specified frequency.
The library is designed with an object-oriented approach, making it easy to extend its functionality and reuse the code in different projects.

Project Structure
The project consists of three main classes:

GPIO Class
This is the base class defining the interface for GPIO handling. It contains virtual methods:

void setDirection(bool inOut) – Sets the pin direction (input/output).
void write(bool state) – Writes the logical state to the pin.
bool read() const – Reads the logical state of the pin.
This class is abstract and serves as a foundation for implementing specific GPIO functions.
GPIOPort Class
This is a derived class related to port functionality.
Features:

Selecting the appropriate registers (DDR, PORT, PIN) based on the port name (B, C, D).
Constructor:
GPIOPort(char portName, uint8_t pinNr) – Initializes the GPIO object for the selected port and pin number. If invalid data is provided, the program halts in an infinite loop.
GPIOPin Class
This class inherits from GPIOPort and extends its functionality with additional methods. It implements the functionalities defined in the GPIO class related to individual pins.
Features:

setDirection(bool inOut) – Sets the pin direction by modifying the DDR register.
write(bool state) – Writes the logical state to the pin via the PORT register.
read() const – Reads the logical state of the pin from the PIN register.
void pullUp(bool on) – Enables or disables the pull-up resistor.
void toggle() – Toggles the logical state of the pin.
void blink(uint16_t delay, uint8_t times) – Makes the LED blink with the specified delay (in milliseconds) and number of repetitions.
bool debounced() – Debounces the switch by reading the pin state with a 50 ms delay.
void configurePWM(uint8_t timer, uint8_t fill, char channel, uint8_t prescaler) – Configures PWM on the selected pin using the specified timer, duty cycle, channel (A/B), and prescaler.
PWM Handling:

Timers 0, 1, and 2 are supported in Fast PWM modes with configurable A and B channels.
Registers OCR, TCCR, and prescalers are used for precise PWM signal control.
Key Elements of the Project

AVR Registers: The GPIOPort class uses the DDRX, PORTX, and PINX registers, where X represents the port name (B, C, D).
Debouncing: The GPIOPin class implements a simple debouncing mechanism by reading the pin state twice with a delay.
PWM: The GPIOPin class allows easy configuration of PWM signals on selected pins, which can be used for controlling LED brightness or DC motor speed.
Applications
This project can be used in various microcontroller applications, such as:

Controlling LEDs.
Reading button states with switch debouncing.
Generating PWM signals.
Handling digital inputs/outputs in complex embedded systems.
Summary
The GPIO project for AVR is a flexible and easy-to-use tool for developers working with AVR microcontrollers. The object-oriented approach allows intuitive management of GPIO pins, and advanced features such as PWM and debouncing significantly expand the capabilities of the application. The library can be easily adapted to meet the specific needs of a project.
