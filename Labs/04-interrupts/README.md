# Lab 4: Interrupts, timers

### Learning objectives

The purpose of the laboratory exercise is to understand the function of the interrupt, interrupt service routine, and the functionality of timer units. Another goal is to practice finding information in the MCU manual; specifically setting timer control registers.


## Preparation tasks (done before the lab at home)

Consider an n-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an overflow. The overflow time depends on the frequency of the clock signal, the number of bits, and on the prescaler value:

&nbsp;
![Timer overflow](Images/timer_overflow.png)
&nbsp;

Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128.

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16u | 128u | -- | 1024u| -- |4096u| 16384u|
| Timer/Counter1 | 16 |  4096u| 32768u | -- | 262.144m| -- | 1.0485776 |4.194304 |
| Timer/Counter2 | 8  |  16u | 128u |512u | 1024u| 2048u |4096u| 16384u|

Shields are boards that can be attached to an Arduino board, significantly expand its capabilities, and makes prototyping much faster. See schematic of [Multi-function shield](../../Docs/arduino_shield.pdf) and find out the connection of four LEDs (D1, D2, D3, D4) and three push buttons (S1-A1, S2-A2, S3-A3).

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;



| **Module** | **Operation** | **I/O register(s)** | **Bit(s)** |
| :-: | :-- | :-: | :-- |
| Timer/Counter0 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR0B<br><br>TCNT0<br>TIMSK0  | CS02, CS01, CS00<br> (000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT0[7:0]<br>TOIE0 (1: enable, 0: disable)<br> |
| Timer/Counter1 | Prescaler<br><br>16-bit data value<br><br>Overflow interrupt enable | TCCR1B<br><br>TCNT1H, TCNT1L<br>TIMSK1 | CS12, CS11, CS10<br>(000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)<br>TCNT1[15:0]<br>TOIE1 (1: enable, 0: disable) |
| Timer/Counter2 | Prescaler<br><br>8-bit data value<br>Overflow interrupt enable | TCCR2B<br><br><br>TCNT2<br> TIMSK2 | CS22, CS21, CS20<br>(000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128, 110: 256, 111: 1024)<br>TCNT2[7:0]<br>TOIE2 (1: enable, 0: disable)<br> 


| **Program address** | **Source** | **Vector name** | **Description** |
| :-: | :-- | :-- | :-- |
| 0x0000 | RESET | -- | Reset of the system |
| 0x0002 | INT0  | `INT0_vect` | External interrupt request number 0 |
| 0x0004 | INT1 | `INT1_vect` |  External interrupt request number 1 |
| 0x0006 | PCINT0 | `PCINT0_vect` |Pin change interrupt request 0  |
| 0x0008 | PCINT1 | `PCINT1_vect` |Pin change interrupt request 1  |
|  0x000A| PCINT2 | `PCINT2_vect` |Pin change interrupt request 2  |
|  0x000C| WDT | `WDT_vect`  | Watchdog time-out interrupt |
|  0x0012| TIMER2_OVF | `TIMER2_OVF_vect`  | Overflow of Timer/Counter2 value |
| 0x0018 | TIMER1_COMPB | `TIMER1_COMPB_vect` | Compare match between Timer/Counter1 value and channel B compare value |
| 0x001A | TIMER1_OVF | `TIMER1_OVF_vect` | Overflow of Timer/Counter1 value |
| 0x0020 | TIMER0_OVF | `TIMER0_OVF_vect` | Overflow of Timer/Counter0 value |
| 0x0024 | USART_RX | `USART0_RX_vect` | USART Rx complete |
| 0x002A | ADC |  `ADC_vect `   | ADC conversion complete |
| 0x0030 | TWI |  `TWI_vect  ` | 2-wire serial interface |

&nbsp;


| **Module** | **Description** | **MCU pin** | **Arduino pin** |
| :-: | :-: | :-: | :-: |
| Timer/Counter0 | OC0A |   PD6  |  6  |
|                | OC0B |   PD5  |  5   |
| Timer/Counter1 | OC1A |   PB1  | 9   |
|                | OC1B | PB2 | 10 |
| Timer/Counter2 | OC2A | PB3 | 11  |
|                | OC2B |   PD3  |   3 |
