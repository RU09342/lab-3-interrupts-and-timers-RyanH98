/*
 * config.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Ryan
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#if defined(__MSP430G2553__)
    #include <msp430g2553.h>

    #define LED0 BIT0 //Define bits for the LEDs and BUTTON.
    #define LED1 BIT1
    #define BUTTON BIT3

    #define LEDDIR P1DIR //Define DIR and OUT for the correct LED1 pin.
    #define LEDOUT P1OUT

    #define BDIR P1DIR //Define DIR, REN, OUT, IE, IES, and IFG for the correct button pin.
    #define BREN P1REN
    #define BOUT P1OUT
    #define BIE P1IE
    #define BIES P1IES
    #define BIFG P1IFG
    #define BIN P1IN

#elif defined(__MSP430F5529__)
    #include <msp430f5529.h>

    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1

    #define LEDDIR P4DIR
    #define LEDOUT P4OUT

    #define BDIR P2DIR
    #define BREN P2REN
    #define BOUT P2OUT
    #define BIE P2IE
    #define BIES P2IES
    #define BIFG P2IFG
    #define BIN P2IN

#elif defined(__MSP430FR6989__)
    #include <msp430fr6989.h>
    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1

    #define LEDDIR P9DIR
    #define LEDOUT P9OUT

    #define BDIR P1DIR
    #define BREN P1REN
    #define BOUT P1OUT
    #define BIE P1IE
    #define BIES P1IES
    #define BIFG P1IFG
    #define BIN P1IN

#elif defined(__MSP430FR5994__)
    #include <msp430fr5994.h>

    #define LED0 BIT0
    #define LED1 BIT2
    #define BUTTON BIT6

    #define LEDDIR P1DIR
    #define LEDOUT P1OUT

    #define BDIR P5DIR
    #define BREN P5REN
    #define BOUT P5OUT
    #define BIE P5IE
    #define BIES P5IES
    #define BIFG P5IFG
    #define BIN P5IN

#elif defined(__MSP430FR2311__)
    #include <msp430fr2311.h>

    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT1

    #define LEDDIR P4DIR
    #define LEDOUT P4OUT

    #define BDIR P1DIR
    #define BREN P1REN
    #define BOUT P1OUT
    #define BIE P1IE
    #define BIES P1IES
    #define BIFG P1IFG
    #define BIN P1IN

#else
  #error "Unsupported board detected!"
#endif

#endif /* CONFIG_H_ */
