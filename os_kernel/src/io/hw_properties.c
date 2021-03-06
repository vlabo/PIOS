/*
 * Copyright (C) 2019 Vladimir Stoilov (vlabo@github)
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

#include "hw_properties.h"
#include "mbox.h"

uint64_t    get_current_execution_level() {
    uint64_t el;
    __asm__ volatile ("mrs %0, CurrentEL" : "=r" (el));
    return el;
}

uint64_t    get_serial_number() {
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MAILBOX_TAG_GET_BOARD_SERIAL;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if(!mbox_call(MBOX_CH_PROP)) {
        return 0;
    }

    return ((uint64_t) mbox[6]) << 32 | ((uint64_t)mbox[5]);
}

uint64_t    get_mac_address() {
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message

    mbox[2] = MAILBOX_TAG_GET_BOARD_MAC_ADDRESS;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if(!mbox_call(MBOX_CH_PROP)) {
        return 0;
    }

    return ((uint64_t)mbox[6] << 32) | ((uint64_t)mbox[5]);
}

uint32_t    get_arm_memory() {

    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = MAILBOX_TAG_GET_ARM_MEMORY;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    if(!mbox_call(MBOX_CH_PROP)) {
        return 0;
    }

    return mbox[6];
}

uint32_t    get_vc_memory() {
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    mbox[2] = MAILBOX_TAG_GET_VC_MEMORY;
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;
    if(!mbox_call(MBOX_CH_PROP)) {
        return 0;
    }

    return mbox[6];
}

bool    set_cpu_max_speed() {
    mbox[0] = 8*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MAILBOX_TAG_GET_MAX_CLOCK_RATE;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = CLK_ARM_ID;
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;

    if(!mbox_call(MBOX_CH_PROP)) {
        return false;
    }
    uint32_t max_clock_rate = mbox[6];

    mbox[0] = 8*4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MAILBOX_TAG_SET_CLOCK_RATE;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = CLK_ARM_ID;
    mbox[6] = max_clock_rate;
    mbox[7] = MBOX_TAG_LAST;

    if(!mbox_call(MBOX_CH_PROP)) {
        return false;
    }
    return true;
}