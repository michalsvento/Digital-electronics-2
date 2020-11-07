## Preparation tasks (done before the lab at home)

Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?


   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | Read (High) or write (Low) - our AVR has just write function |
   | E | PB1 | Signal ENABLE  |
   | D[3:0] | not used | Data registers for 8bit communication |
   | D[7:4] | PD[7:4] | Data registers, 4 bit communication,first high four bits and then low four bits with an E clock pulse |

What is the ASCII table? What are the values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

It's a American standard code for information interchange. Its code table for letters numbers and special characters

|**Description**|**ASCII**|**Character**|
| :-: | :-: | :-:
|  uppercase (Capital) letters US Alphabet   | 65 - 90  | `A` to `Z`|
| lowercase letters US Alphabet | 97 - 122 | `a`to `z`|
| numbers | 48 - 57 | `0`to `9` | 




   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br>&nbsp;<br>&nbsp;<br>&nbsp; | `lcd_init(LCD_DISP_OFF);`<br>&nbsp;<br>&nbsp;<br>&nbsp; |
   | `lcd_clrscr` | none | | `lcd_clrscr();` |
   | `lcd_gotoxy` | `uint8_t`x , y| Set cursor to specified position| `lcd_gotoxy(0,4);` |
   | `lcd_putc` | | | |
   | `lcd_puts` | | | |
   | `lcd_command` | | | |
   | `lcd_data` | `LCD_DATA0_PORT`| | |
