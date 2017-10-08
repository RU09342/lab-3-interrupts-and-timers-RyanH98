#include <msp430.h> 

//We'll do the reaction game on the FR6989.

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//Initialize all the buttons, LED assignments, and timers.

	//Wait for both buttons to be pressed simultaneously.

	//Begin counting.

	//At a random time (within a margin) turn on an LED.

	//Measure which button is pressed first.

	//Record when the first button is pressed.

	//Record when the second button is pressed.

	//Display the time between the button presses on the 7-segment display. Blink an LED to show the winner.

	return 0;
}
