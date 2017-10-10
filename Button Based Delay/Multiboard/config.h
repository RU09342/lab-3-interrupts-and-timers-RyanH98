/*
 * config.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Ryan
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#if defined(__MSP430G2553__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT3
    int LED1pin = 1;
    int BUTTONpin = 1; //Instead of this int shit, i need to #define pinDIR P1DIR, etc...

#elif defined(__MSP430F5529__)
    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1
    int LED1pin = 4;
    int BUTTONpin = 2;

#elif defined(__MSP430FR6989__)
    #define LED0 BIT0
    #define LED1 BIT7
    #define BUTTON BIT1
    int LED1pin = 9;
    int BUTTONpin = 1;

#elif defined(__MSP430FR5994__)
    #define LED0 BIT0
    #define LED1 BIT2
    #define BUTTON BIT6
    int LED1pin = 1;
    int BUTTONpin = 5.

#elif defined(__MSP430FR2311__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT1
    int LED1pin = 4;
    int BUTTONbit = 1;

#else
  #error "Unsupported board detected!"
#endif

#endif /* CONFIG_H_ */
