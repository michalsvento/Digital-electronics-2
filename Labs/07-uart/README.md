# Lab 7: ADC and UART serial communication

### Learning objectives

The purpose of the laboratory exercise is to understand analog-to-digital number conversion and the use of an internal 8-channel 10-bit AD converter. Another goal is to understand serial asynchronous communication, data frame structure and communication options using an internal USART unit.

![LCD-keypad shield](Images/arduino_uno_adc.jpeg)


## Preparation tasks (done before the lab at home)

Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of five push buttons: Select, Left, Up, Down, and Right.

![zapojenie](Images/zapojeniebuttons.png)

According to the connection, calculate the voltage value on pin PC0[A0] if one button is pressed at a time. In this case, the voltage on the pin is given by the [voltage divider](https://www.allaboutcircuits.com/tools/voltage-divider-calculator/), where resistors R3, R4, R5 and R6 are applied successively.

![Equation: Voltage divider](Images/eq_divider1.png)

![Equation: Voltage divider](Images/eq_divider2.png)

&nbsp;

![Equation: Voltage divider](Images/eq_divider3.png)

&nbsp;

![Equation: Voltage divider](Images/eq_divider4.png)

&nbsp;

![Equation: Voltage divider](Images/eq_divider5.png)

&nbsp;

What is the voltage value if none of the push buttons is pressed?

![Equation: Voltage divider](Images/eq_divider6.png)

&nbsp;

Calculate the ADC values for these voltages according to the following equation if reference is Vref=5V and number of bits for analog to digital conversion is n=10.

![Equation: ADC conversion](Images/eq_adc.png)

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0   |  0|
   | Up     | 0.495&nbsp;V | 101 | 101 |
   | Down   | 1.203&nbsp;V | 246 | 245 |
   | Left   | 1.969&nbsp;V | 403  | 402 |
   | Select | 3.181&nbsp;V | 651 |  650 |
   | none   | 5&nbsp;V |   1023  | 1022 |
   
   
The operation with the AD converter is performed through ADMUX, ADCSRA, ADCL+ADCH, ADCSRB, and DIDR0 registers. See [ATmega328P datasheet](https://www.microchip.com/wwwproducts/en/ATmega328p) (**Analog-to-Digital Converter > Register Description**) and complete the following table.

   | **Operation** | **Register(s)** | **Bit(s)** | **Description** |
   | :-: | :-- | :-- | :-- |
   | Voltage reference | ADMUX | REFS1:0 | 01: AVcc voltage reference, 5V |
   | Input channel | ADMUX | MUX3:0 | 0000: ADC0, 0001: ADC1, ... |
   | ADC enable | ADCSRA | Bit 7 – ADEN: | 0: turned off |
   | Start conversion | ADCSRA | Bit 6 – ADSC | 1: in Single - starts each conversion, in Freerunning - starts the first conv.; returns to 0 when conv. completed |
   | ADC interrupt enable | ADCSRA | Bit 3 – ADIE | 1: activated, if 1-bit in SREG is set |
   | ADC clock prescaler | ADCSRA | ADPS2:0 | 000: Division factor 2, 001: 2, 010: 4, ...|
   | ADC result |  |  |  |


In the lab, we are using [UART library](http://www.peterfleury.epizy.com/avr-software.html) developed by Peter Fleury. Use online manual of UART library and add the input parameters and description of the functions to the following table.

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd | `uart_init(UART_BAUD_SELECT(9600, F_CPU));` |
   | `uart_getc` | none | Get received byte from ringbuffer. | `uart_getc()` |
   | `uart_putc` | `data` byte to be transmitted | Put byte to ringbuffer for transmitting via UART. | `uart_putc(data)` |
   | `uart_puts` | `s`	string to be transmitted  | Put string to ringbuffer for transmitting via UART. | `uart_putc(s)` |
