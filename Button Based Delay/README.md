# Button Based Delay
### Ryan Hare

## Background
In this part of Lab 3, the code needed to detect when a button is pressed down, keep track of the amount of time it was held for, and then set the LED blinking interval to be the duration the LED was held for. Similarly to previous parts, the LED and button were intialized as usual. 

The code accomplishes this by incrementing a time variable with the timer. It then stores the current time variable whenever the button interrupt triggers and an if statement detects that the button is pressed. Then, by XOR-ing the P1IES register with the button bit, the interrupt edge is switched from when the button is pressed to when the button is released. This way, when the button is released, it triggers another interrupt. This interrupt uses an if statement to detect whether the button interrupt was a press or release. On a release, it stores a second time variable. 

Finally, the time variables are compared and stored as the divisor in a clock divider. This allows the LED blink duration to be changed based on how long the button is held.
## Devices
Similarly to the TIMER A Blink, there is code for the MSP430G2553. There is also code for the MSP430FR2311. Finally, there is a multiboard variant of the code which functions on the four other MSP430 boards: The MSP430G2553, the MSP430FR5994, the MSP430FR6989, and the MSP430F5529.
## Usage
The code can be loaded onto compatible boards with Code Composer Studio. Once loaded onto the board, the LED will blink at a regular interval. The interval can be changed by holding down the button.
### Other Uses
Storing durations like this is very useful if one wanted to create a timer or a stopwatch, or perhaps measure the difference between a start time and an end time.
### Possible Improvements
Once again, this code lacks debouncing. As such, the button will occasionally bounce, forcing the time difference to be extremely small, making the LED appear to be constantly on. Debouncing would fix this problem.
## Board-Specific Code Differences
The only difference between the boards is the LED and button pins. The multiboard code works for all of the boards except for the FR2311. The FR2311 cannot use Timer A in code so Timer B needs to be used. This is why the FR2311 has seperate code from the multiboard code.