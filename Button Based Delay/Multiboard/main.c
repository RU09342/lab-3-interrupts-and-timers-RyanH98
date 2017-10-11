#include <msp430.h>
#include <config.h> //Include the config file for multiboard functionality.

unsigned int count, time, button, lastButton, timeStart, timeEnd, overflows = 0;   //Define the integers, which are used later.
unsigned int div = 4;
unsigned int debouncing = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= LED0;                  // configure LED as output

    P1OUT &= ~LED0;                 //Set the initial LED condition to off.

    BDIR &= ~BUTTON;               //Set BUTTON as an input
    BREN |= BUTTON;                //Enable the pull resistor on BUTTON
    BOUT |= BUTTON;                //Tell the pull resistor to pull up
    BIE |= BUTTON;                 //Enable interrupt on BUTTON
    BIES |= BUTTON;                //Set the BUTTON interrupt to trigger on a high->low edge.
    BIFG &= ~BUTTON;               //Clear the interrupt flag register on BUTTON

    TA0CCTL0 = CCIE;                //Enable interrupts for the first capture/compare register.
    TA0CTL = TASSEL_2 + MC_2;       //Set the Timer_A0 control to:
                                    //1. TASSEL_2 which selects SMCLK, the internal 1MHz clock.
                                    //2. MC_2 which selects the continuous counting mode.

    __enable_interrupt();           //Enable interrupts.

    __bis_SR_register(GIE);         //General interrupt enable.

}

//Interrupt vector service routine for Timer A0.
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void) {
    time = (time + 1) % div;            //Increment 'time' every clock tick and then clock divide it by 'div'
    count++;
    if (time == 0)
        P1OUT ^= LED0;                  //Toggle the LED whenever time % div == 0.
    if (TAIV == 0x0E)
        overflows++;                    //If the capture/compare register says that the interrupt was caused by an overflow, increment 'overflows'.
}

#pragma vector=BUTTONVECTOR             //Set the port 1 interrupt routine
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

    BIFG &= ~BUTTON;                   //P1.3 IFG cleared
    BIES ^= BUTTON;                    //Toggle the interrupt edge so that this interrupt triggers on the button press and release.
}
