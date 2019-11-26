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
#include <stdlib.h>
#include <assert.h>

#include "io/delays.h"
#include "io/hw_properties.h"
#include "io/usb.h"
#include "io/mbox.h"
#include "memory/liballoc.h"
#include "memory/mmu.h"
#include "cli/cli.h"

void main()
{
    mmu_init();
    cli_init();
    //set_cpu_max_speed();

    printf("Serial number is %lX\n",    get_serial_number());
    printf("MAC address is %lX\n",      get_mac_address());
    printf("ARM memory is %u\n",        get_arm_memory());
    printf("VideoCore memory is %u\n",  get_vc_memory());
    
    //assert(1 == 0);


    /*for(int i = 0; i < 8; i++) {
        printf("%X\n", mbox[i]);
    }*/

    /* Initialize USB system we will want keyboard and mouse */
	UsbInitialise();
    UsbCheckForChange();

	/* Display the USB tree */
	printf("\n");
	UsbShowTree(UsbGetRootHub(), 1, '+');
	printf("\n");

    /* Detect the first keyboard on USB bus */
	/*uint8_t firstKbd = 0;
	for (int i = 1; i <= MaximumDevices; i++) {
		if (IsKeyboard(i)) {
			firstKbd = i;
			break;
		}
	}
	if (firstKbd) printf("Keyboard detected\r\n");*/
    
    /*bool* array = calloc(100, sizeof(bool));
    printf("Allocated bool array: %X\n", array);
    if(array != NULL) {
        memset(array + 50, true, 50);

        for(int i = 0; i < 100; i++) {
            printf("%d : %s, ", i, array[i] ? "true" : "false");
        }

        printf("\n");
        free(array);
    }*/

    int i = 0;
    while(1) {
        //uart_printf("Counting %d\n", get_mem_size((atag_t*) 0x100));
        i++;
        wait_usec_st(100000);
    }
}
