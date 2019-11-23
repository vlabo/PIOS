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
#include "types.h"
#include "io/delays.h"
#include "std/printf.h"
#include "io/hw_properties.h"
#include "memory/liballoc.h"
#include "memory/mmu.h"
#include "cli/cli.h"

void main()
{
 
    /*uart_init();
    if( ! gpu_init() ) {
        uart_printf("Failed to initialize frame buffer.\n");
    }
    
    gpu_clear_screen();*/
    mmu_init();
    cli_init();

    printf("Serial number is %lX\n",     get_serial_number());
    uint64_t mac = get_mac_address();
    printf("MAC address is %lX\n", mac);
    printf("ARM memory is %u\n",        get_arm_memory());
    printf("VideoCore memory is %u\n",  get_vc_memory());

    
    bool* array = calloc(100, sizeof(bool));
    printf("Allocated bool array: %X\n", array);
    if(array != NULL) {
        memset(array + 50, true, 50);

        for(int i = 0; i < 100; i++) {
            printf("%d : %s, ", i, array[i] ? "true" : "false");
        }

        printf("\n");
        free(array);
    }

    int i = 0;
    while(1) {
        //uart_printf("Counting %d\n", get_mem_size((atag_t*) 0x100));
        i++;
        wait_msec_st(100000);
    }
}
