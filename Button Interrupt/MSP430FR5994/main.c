#include <msp430.h>

//These pin assignments are for the FR5994

#define BUTTON BIT6                 //Define "BUTTON" as bit 6
#define LED0 BIT0                   //Define "LED0" as bit 0

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       //Stop watchdog timer

    P1DIR |= LED0;                  //Set P1.0 (LED) as an output
    P1OUT &= ~LED0;                 //Set the initial LED condition to off

    P5DIR &= ~BUTTON;               //Set P5.6 (Button) as an input
    P5REN |= BUTTON;                //Enable the pull resistor on P5.6
    P5OUT |= BUTTON;                //Tell the pull resistor to pull up
    P5IE |= BUTTON;                 //Enable interrupt on P5.6
    P5IES |= BUTTON;                //Set the P5.6 interrupt to trigger on a high->low edge.
    P5IFG &= ~BUTTON;               //Clear the interrupt flag register on P5.6

    PM5CTL0 &= ~LOCKLPM5;            //Disable high impedance mode.

    __bis_SR_register(LPM4_bits + GIE); //Enter into low power mode to idle until the interrupt occurs and enable global interrupts

}

#pragma vector=PORT5_VECTOR          //Set the port 5 interrupt routine
__interrupt void Port_5(void) {
    P1OUT ^= LED0;                   //Toggle P1.0 (LED)
    P5IFG &= ~BUTTON;                //P5.6 IFG cleared
}



