#include <msp430.h>

//These pin assignments are for the G2553.

#define BUTTON BIT3                 //Define "BUTTON" as bit 3
#define LED0 BIT0                   //Define "LED0" as bit 0

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       //Stop watchdog timer

    P1SEL &= (~LED0 & ~BUTTON);     //Select the I/O mode for P1.0 and P1.3

    P1DIR |= LED0;                  //Set P1.0 (LED) as an output
    P1OUT &= ~LED0;                 //Set the initial LED condition to off

    P1DIR &= ~BUTTON;               //Set P1.3 (Button) as an input
    P1REN |= BUTTON;                //Enable the pull resistor on P1.3
    P1OUT |= BUTTON;                //Tell the pull resistor to pull up
    P1IE |= BUTTON;                 //Enable interrupt on P1.3
    P1IES |= BUTTON;                //Set the P1.3 interrupt to trigger on a high->low edge.
    P1IFG &= ~BUTTON;               //Clear the interrupt flag register on P1.3

    __bis_SR_register(LPM4_bits + GIE);

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= LED0;                  //Toggle P1.0 (LED)
    P1IFG &= ~BUTTON;                //P1.3 IFG cleared
}


