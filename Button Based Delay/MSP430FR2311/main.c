#include <msp430.h>

unsigned int count, time, button, lastButton, timeStart, timeEnd, overflows = 0;   //Define the integers, which are used later.
unsigned int div = 4;
unsigned int debouncing = 0;
#define LED0 BIT0
#define BUTTON BIT1                 //Define "BUTTON" as bit 3

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= LED0;                  // configure P1.0 and 1.6 as output

    P1OUT &= ~LED0;                 //Set the initial LED condition to off.

    P1DIR &= ~BUTTON;               //Set P1.3 (Button) as an input
    P1REN |= BUTTON;                //Enable the pull resistor on P1.3
    P1OUT |= BUTTON;                //Tell the pull resistor to pull up
    P1IE |= BUTTON;                 //Enable interrupt on P1.3
    P1IES |= BUTTON;                //Set the P1.3 interrupt to trigger on a high->low edge.
    P1IFG &= ~BUTTON;               //Clear the interrupt flag register on P1.3

    TB0CCTL0 = CCIE;                //Enable interrupts for the first capture/compare register.
    TB0CTL = TBSSEL_2 + MC_2;       //Set the Timer_A0 control to:
                                    //1. TASSEL_2 which selects SMCLK, the internal 1MHz clock.
                                    //2. MC_2 which selects the continuous counting mode.

    __enable_interrupt();           //Enable interrupts.

    __bis_SR_register(GIE);         //General interrupt enable.

}

//Interrupt vector service routine for Timer A0.
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B0 (void) {
    time = (time + 1) % div;            //Increment 'time' every clock tick and then clock divide it by 'div'
    count++;
    if (time == 0)
        P1OUT ^= LED0;                  //Toggle the LED whenever time % div == 0.
    if (TBIV == 0x0E)
        overflows++;                    //If the capture/compare register says that the interrupt was caused by an overflow, increment 'overflows'.
}

#pragma vector=PORT1_VECTOR             //Set the port 1 interrupt routine
__interrupt void Port_1(void) {
    button ^= 1;                        //Toggle the button variable.
    if ((button == 1) && (lastButton == 0)){    //If the button has been pressed, this if statement will trigger.
        timeStart = count;                      //Store the current count in 'timeStart'.
        overflows = 0;                          //Reset 'overflows'.
    }
    else if ((button == 0) && (lastButton == 1)){               //If the button has been depressed, this if statement will trigger.
        timeEnd = count;                                        //Store the current count in 'timeEnd'.
        div = ((timeEnd + (overflows * 65536)) - timeStart);    //Update div to be equal to the difference in 'timeEnd' and 'timeStart'...
                                                            //...taking into account the amount of overflows that occurred between the two.
    }

    lastButton = button;                //Update 'lastButton' with 'button'.

    P1IFG &= ~BUTTON;                   //P1.3 IFG cleared
    P1IES ^= BUTTON;                    //Toggle the interrupt edge so that this interrupt triggers on the button press and release.
}
