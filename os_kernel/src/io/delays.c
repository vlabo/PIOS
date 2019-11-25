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

#include "gpio.h"
#include "delays.h"

#define SYSTMR_LO        ((volatile uint32_t*)(IO_BASE+0x00003004))
#define SYSTMR_HI        ((volatile uint32_t*)(IO_BASE+0x00003008))

/**
 * Wait N CPU cycles (ARM CPU only)
 */
void wait_cycles(uint32_t n)
{
    if(n) while(n--) { __asm__ volatile("nop"); }
}

/**
 * Wait N microsec (ARM CPU only)
 */
void wait_usec(uint32_t n)
{
    register uint64_t f, t, r;
    // get the current counter frequency
    __asm__ volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // read the current counter
    __asm__ volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // calculate expire value for counter
    t+=((f/1000)*n)/1000;
    do{__asm__ volatile ("mrs %0, cntpct_el0" : "=r"(r));}while(r<t);
}

/**
 * Get System Timer's counter
 */
uint64_t get_system_timer()
{
    uint32_t h=-1, l;
    // we must read MMIO area as two separate 32 bit reads
    h = *SYSTMR_HI;
    l = *SYSTMR_LO;
    // we have to repeat it if high word changed during read
    if(h != *SYSTMR_HI) {
        h = *SYSTMR_HI;
        l = *SYSTMR_LO;
    }
    // compose long int value
    return ((uint64_t) h << 32) | l;
}

/**
 * Wait N microsec (with BCM System Timer)
 */
void wait_usec_st(unsigned int n)
{
    unsigned long t=get_system_timer();
    // we must check if it's non-zero, because qemu does not emulate
    // system timer, and returning constant zero would mean infinite loop
    if(t) while(get_system_timer() < t+n);
}


uint64_t tick_difference (uint64_t us1, uint64_t us2) {
	if (us1 > us2) {												// If timer one is greater than two then timer rolled
		uint64_t td = UINT64_MAX - us1 + 1;							// Counts left to roll value
		return us2 + td;											// Add that to new count
	} 
	return us2 - us1;												// Return difference between values
}