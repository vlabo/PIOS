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

#include <stdio.h>
#include "cli.h"
#include "io/gpu.h"
#include "io/uart.h"
#include "memory/liballoc.h"

#define BUFFER_SIZE 100

typedef struct Line {
    char* string;
    int last_char;
    int last_drawn_char;
} Line;


Line*  m_cli_buffer;
size_t  m_current_line_index;

void init_lines(Line* lines) {
    for(int i = 0; i < BUFFER_SIZE; i++) {
        lines[i].string = calloc(gpu_get_line_char_count(), sizeof(char));
        lines[i].last_char = -1;
        lines[i].last_drawn_char = 0;
    }
}

void    cli_init() {
    uart_init();

    if( ! gpu_init() ) {
        uart_printf("Failed to initialize frame buffer.\n");
        return;
    }

    gpu_clear_screen();

    m_current_line_index = 0;

    m_cli_buffer = calloc(BUFFER_SIZE, sizeof(Line));
    init_lines(m_cli_buffer);
    uart_printf("CLI initialized.\n");

    set_default_output_stream(cli_stream);
}

void    cli_destroy() {
    free(m_cli_buffer);
}

static void draw() {
    Line* line = &m_cli_buffer[m_current_line_index];
    for(int i = line->last_drawn_char; i <= line->last_char; i++) {
        gpu_putc(line->string[i], i, m_current_line_index);
    }
    line->last_drawn_char = line->last_char;
}

static void gpu_putchar(char c) {
    if(c == '\n') {
        m_current_line_index++;
        return;
    }
    Line* current_line = &m_cli_buffer[m_current_line_index];
    if(current_line->last_char > 0 && current_line->last_char >= gpu_get_line_char_count()) {
        m_current_line_index++;
        gpu_putchar(c);
        return;
    }

    current_line->last_char++;
    current_line->string[current_line->last_char] = c;
    draw();
}

void    cli_stream(char c) {
    gpu_putchar(c);
}
