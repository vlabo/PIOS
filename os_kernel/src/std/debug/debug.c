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

#include "debug.h"
#include <stdio.h>
#include <io/config.h>

#ifndef NDEBUG

void debug_hexdump(const void *start, uint64_t bytes_number, const char *source) {
	uint8_t *offset = (uint8_t *) start;

	if(source == NULL) {
		source = "debug";
	}

	printf ("Dumping 0x%X bytes starting at 0x%X", bytes_number, (uint64_t) offset);
	
	while (bytes_number > 0) {
		printf(
				"%X: %hX %hX %hX %hX %hX %hX %hX %hX-%hX %hX %hX %hX %hX %hX %hX %hX",
				(uint32_t) offset & 0xFFFF,
				(uint16_t) offset[0],  (uint16_t) offset[1],  (uint16_t) offset[2],  (uint16_t) offset[3],
				(uint16_t) offset[4],  (uint16_t) offset[5],  (uint16_t) offset[6],  (uint16_t) offset[7],
				(uint16_t) offset[8],  (uint16_t) offset[9],  (uint16_t) offset[10], (uint16_t) offset[11],
				(uint16_t) offset[12], (uint16_t) offset[13], (uint16_t) offset[14], (uint16_t) offset[15]);

		offset += 16;

		if (bytes_number >= 16) {
			bytes_number -= 16;
		} else {
			bytes_number = 0;
		}
	}
}

void debug_stacktrace(const uint64_t *stack_ptr, const char *source) {
	if (source == 0) {
		source = "debug";
	}
	
	for (unsigned i = 0; i < 64; i++, stack_ptr++) {
		extern unsigned char _end_text;

		if ( *stack_ptr >= MEM_KERNEL_START
		    && *stack_ptr < (uint64_t) &_end_text) {
			printf("stack[%u] is 0x%X\n", i, (unsigned) *stack_ptr);
		}
	}
}

#endif
