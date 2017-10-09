# TIMER A Blink
### Ryan Hare

## Background
Buttons are not the only thing in the MSP430 microprocessors that can trigger interrupts. Timers can also trigger interrupts. For this part, a timer was set up by first setting CCTL0 = CCIE. This enables interrupts for capture/control register zero. Then, the following code is run:

TACTL = TASSEL_2 + MC_2 + ID_3

This takes TACTL (Timer A Control) and sets it to TASSEL_2 (Timer A select 2, SMCLK), MC_2 which is continuous counting mode, and ID_3 which is an 8x internal clock divider. Once the timer is initialized, the timer interrupt vector can be set with:

#pragma vector=TIMER0_A0_VECTOR __interrupt void Timer_A (void)

Any code inside of the interrupt vector will run whenever the timer increments. In this case, the code is to toggle an LED.
## Devices
There is timer interrupt code for the MSP430G2553. There is also a multi-board compatible code which will function on the MSP430G2553, the MSP430FR5994, the MSP430FR6989, the MSP430FR2311, and the MSP430F5529.
## Extra Work
