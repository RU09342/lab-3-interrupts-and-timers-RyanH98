#include <config.h>

unsigned int time = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= LED0;                  // configure LED0

    P1OUT &= ~LED0;                 //Set the initial LED condition to off.

    CCTL0 = CCIE;                   //Enable interrupts for the first capture/compare register.
    TACTL = TASSEL_2 + MC_2 + ID_3; //Set the Clock_A control to:
                                    //1. TASSEL_2 which selects SMCLK, the internal 1MHz clock.
                                    //2. MC_2 which selects the continuous counting mode.
                                    //3. ID_3 which sets an internal 8x clock divider.

    __enable_interrupt();           //Enable interrupts.

    __bis_SR_register(LPM0 + GIE);  //Enter low power mode with interrupts.
}

//Interrupt vector service routine for Timer A0.
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {
    P1OUT ^= LED0;                  //Toggle the LED whenever the timer interrupts (about every 0.5 seconds).
}
