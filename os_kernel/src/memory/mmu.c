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

#include "mmu.h"

#include <stdlib.h>
#include <printf.h>

#include "io/hw_properties.h"


extern uint8_t _end;

#define PAGE_SIZE 4096  // 4 KB

uint64_t    base_address;
bool        *pages;
size_t      pages_count;

void    mmu_init() {
    base_address = ((uint64_t)&_end) + PAGE_SIZE;
    uint64_t avaliable_bytes = get_arm_memory() - base_address;
    
    pages = (bool*) &_end;
    pages_count = avaliable_bytes / PAGE_SIZE;

    for(size_t i = 0; i < pages_count; i++) {
        pages[i] = false;
    }
}

int liballoc_lock() {
    return 0;
}

int liballoc_unlock() {
    return 0;
}

void* liballoc_alloc(size_t count) {
    size_t free_pages_count = 0;
    size_t first_page_index = -1;
    for(size_t i = 0; i < pages_count; i++) {
        if(!pages[i]) {
            free_pages_count++;

            if(free_pages_count == 1) {
                first_page_index = i;
            }
        } else {
            free_pages_count = 0;
            first_page_index = -1;
        }

        if(free_pages_count == count) {
            for(int j = count; j < i; j++) {
                pages[j] = true;
            }
            return (void*)(base_address + first_page_index * PAGE_SIZE);
        }
    }

    return NULL;
}

int liballoc_free(void* pointer, size_t count) {
    size_t index = (size_t) (pointer - base_address) / PAGE_SIZE;
    if(index + count > pages_count) 
        return 1;

    if(index < 0)
        return 1;
    
    for(size_t i = index; i < count; i++) {
        pages[i] = false;
    }
    return 0;
}