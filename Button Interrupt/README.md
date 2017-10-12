# Button Interrupt
### Ryan Hare

## Background
For this part of Lab 3, button interrupts were used to toggle an LED. The code initializes the LED and button as it does in the button blink part with one difference. The button bit is also or-ed with the P1IE and P1IES registers. These are the interrupt enable register and the interrupt edge select register. The first one enables an interrupt when the button is pressed. The second one sets the interrupt so it only triggers when the button is pressed down. Then, the following code is used:

__bis_SR_register(LPM4_bits + GIE);
 
This puts the microprocessor into low power mode. This means that almost all of the functions of the processor are turned off. In LPM4, which is low power mode 4, the processor and all the clocks are disabled. Then, the following code is placed:

pragma vector=PORT1_VECTOR __interrupt void Port_1(void)

This code defines what the processor does when the button interrupt triggers. When the interrupt triggers, the processor will turn on for a brief moment, perform any actions defined by the interrupt vector, and go back into low power mode.
## Devices
Code is included for the MSP430G2553, the MSP430FR5994, the MSP430FR6989, the MSP430FR2311, and the MSP430F5529.
## Usage
Once the code is loaded onto the assigned board with Code Composer Studio, the LED will toggle whenever the button is pressed down.
### Other Uses
The use of interrupt vectors and low power mode allows the processor to save a large amount of power. This is very useful in data processing, where the processor will be able to idle whenever it isn't gathering data. This is also useful for consumer products, where the device would use very little power until a button was pressed, for example.
### Possible Improvements
This code has a major flaw: The lack of debouncing. Whenever the button is depressed, it bounces, occasionally triggering one or multiple inputs. This means that the LED might be turned off by the initial press and turned back on by the bouncing. Or maybe it will blink a few times instead. This code would be greatly improved by the addition of debouncing, either through hardware or software.
## Board-Specific Code Differences
One of the two differences between the board code is the button pin assignments.

* For the G2553, the button is on pin 1.3 
* For the F5529, the button is on pin 2.1 
* For the FR6989, the button is on pin 1.1 
* For the FR5994, the button is on pin 5.6 
* For the FR2311, the button is on pin 1.1

The other difference is that the following line of code is needed for the F5529 and FR5994:

PM5CTL0 &= ~LOCKLPM5;

This code disables high impedance mode, which sets all pins to high impedance inputs. This allows the board to actually read the input of the button and toggle the LED.
