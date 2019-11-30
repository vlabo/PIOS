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


#include "assert.h"
#include "printf.h"
#include "stdlib.h"
#include "debug/debug.h"

#ifndef NDEBUG

void assertion_failed(const char *expresion, const char *file, const char *function, unsigned line) {
	uint64_t stack_pointer;
	__asm__ volatile ("mov %0,sp" : "=r" (stack_pointer));

    printf("Assertion failed: %s: %s(%u) : %s\n", expresion, file, line, function);

	//debug_stacktrace ((uint64_t*) stack_pointer, NULL);
}

void not_implemented_error(const char *file, const char *function, unsigned line) {
	printf("Not implemented: %s(%u) : %s\n", file, line, function);
}

void display_warning(const char *message, const char *file, const char *function, unsigned line) {
	printf("Warning: %s - %s(%u) : %s\n", message, file, line, function);
}

#endif