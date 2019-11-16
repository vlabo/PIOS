/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef GPIO_H
#define GPIO_H

#include "../types.h"

#define IO_BASE    0x3F000000
#define MMIO_BASE       0x3F000000

#define GPFSEL0         ((volatile unsigned int*)(MMIO_BASE+0x00200000))
#define GPFSEL1         ((volatile unsigned int*)(MMIO_BASE+0x00200004))
#define GPFSEL2         ((volatile unsigned int*)(MMIO_BASE+0x00200008))
#define GPFSEL3         ((volatile unsigned int*)(MMIO_BASE+0x0020000C))
#define GPFSEL4         ((volatile unsigned int*)(MMIO_BASE+0x00200010))
#define GPFSEL5         ((volatile unsigned int*)(MMIO_BASE+0x00200014))
#define GPSET0          ((volatile unsigned int*)(MMIO_BASE+0x0020001C))
#define GPSET1          ((volatile unsigned int*)(MMIO_BASE+0x00200020))
#define GPCLR0          ((volatile unsigned int*)(MMIO_BASE+0x00200028))
#define GPLEV0          ((volatile unsigned int*)(MMIO_BASE+0x00200034))
#define GPLEV1          ((volatile unsigned int*)(MMIO_BASE+0x00200038))
#define GPEDS0          ((volatile unsigned int*)(MMIO_BASE+0x00200040))
#define GPEDS1          ((volatile unsigned int*)(MMIO_BASE+0x00200044))
#define GPHEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200064))
#define GPHEN1          ((volatile unsigned int*)(MMIO_BASE+0x00200068))
#define GPPUD           ((volatile unsigned int*)(MMIO_BASE+0x00200094))
#define GPPUDCLK0       ((volatile unsigned int*)(MMIO_BASE+0x00200098))
#define GPPUDCLK1       ((volatile unsigned int*)(MMIO_BASE+0x0020009C))



/// the base offset address of the GPIO-registers in memory
#define GPIO_BASE 0x200000

#define GPIO_LOW 0
#define GPIO_HIGH 1

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_ALT0 4
#define GPIO_ALT1 5
#define GPIO_ALT2 6
#define GPIO_ALT3 7
#define GPIO_ALT4 3
#define GPIO_ALT5 2

#define GPIO_PULL_UP 2
#define GPIO_PULL_DOWN 1
#define GPIO_PULL_OFF 0 

/**
 * \brief a mapping of the memory-registers of the GPIO-controller
 **/
struct gpio_t 
{
    uint32_t fn_select[6];               ///< function select registers for the Pins      
    uint32_t pad1;
    uint32_t outputset[2];               ///< registers for setting the levels HIGH
    uint32_t pad2;
    uint32_t outputclear[2];             ///< registers for setting the levels LOW
    uint32_t pad3;
    uint32_t level[2];                   ///< the levels of the pins for reading
    uint32_t pad4;
    uint32_t eventDetect[2];             ///< indicates whether an event has occured (whathever is enabled)
    uint32_t pad5;
    uint32_t risingEdgeDetect[2];        ///< en/disable rising edge for the eventDetect-field
    uint32_t pad6;
    uint32_t fallingEdgeDetect[2];       ///< en/disable falling edge for the eventDetect
    uint32_t pad7;
    uint32_t highDetect[2];              ///< en/disable HIGH as event for eventDetect
    uint32_t pad8;
    uint32_t lowDetect[2];               ///< en/disable LOW as event for eventDetect
    uint32_t pad9;
    uint32_t asyncRisingEdgeDetect[2];   ///< en/disable rising edge as asynchronous event for eventDetect (i.e. not bound to system clock)
    uint32_t pad10;
    uint32_t asyncFallingEdgeDetect[2];  ///< en/disable falling edge as asynchronous event for eventDetect (i.e. not bound to system clock)
    uint32_t pad11;
    uint32_t pullControlEnable;          ///< set the pull-mode (i.e. UP, DOWN or OFF)
    uint32_t pullControlClock[2];        ///< set pins for pulling (see the manual for the exact algorithm)
} typedef gpio_t;

/// struct mapping the GPIO-controller-registers
extern volatile gpio_t* const gpio;

/**
 * \brief pull up or down a set of pins
 * \param p an array which represents the GPIO-pins and their on-values for pulling
 * \param pull the direction for the voltage-pull
 * \note this is a lower-level implementation of the pios_gpio_pudControl-function, use that if unsure
 **/
void gpio_pullMulti( uint32_t p[2], uint32_t pull );

/**
 * \brief pull up or down a specific pin 
 * \param pin GPIO-Pin
 * \param pull the direction for the voltage-pull
 **/
void gpio_pullControl( uint32_t pin, uint32_t pull );

/**
 * \brief reads the value of the GPIO-pin (set as input)
 * \param pin the GPIO pin you want the state of (in [0, 53])
 * \return the state of the GPIO-Pin (i.e. HIGH or LOW-signal level), 
 * always returns LOW if the input is invalid
 **/
uint32_t gpio_read( uint32_t pin );

/**
 * \brief writes a value to the GPIO-Pin (i.e. writes 1 to set or 1 to clear)
 * \param pin GPIO-Pin
 * \param val output-value (1 for on, 0 for off)
 **/
void gpio_write( uint32_t pin, uint32_t val );

/**
 * \brief sets the PIN into the mode we want
 * \param pin GPIO-Pin
 * \param val GPIO-Mode
 * \return NONE
 **/
void gpio_pinmode( uint32_t pin, uint32_t val );

/**
 * \brief read the mode of the pin and return it
 * \param pin the pin to be read
 * \return the current mode of the pin
 **/
int gpio_getPinmode( uint32_t pin );

#endif