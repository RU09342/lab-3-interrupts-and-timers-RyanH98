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

#elif defined(__MSP430F5529__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT3

#elif defined(__MSP430FR6989__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT3

#elif defined(__MSP430FR5994__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT3

#elif defined(__MSP430FR2311__)
    #define LED0 BIT0
    #define LED1 BIT1
    #define BUTTON BIT3

#else
  #error "Unsupported board detected!"
#endif

#endif /* CONFIG_H_ */
