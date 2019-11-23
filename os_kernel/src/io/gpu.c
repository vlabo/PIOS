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
#include "gpu.h"
#include "uart.h"
#include "mbox.h"

/* PC Screen Font as used by Linux Console */
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
    unsigned char glyphs;
} __attribute__((packed)) psf_t;
extern volatile unsigned char _binary_res_font_psf_start;

psf_t *font = (psf_t*)&_binary_res_font_psf_start;

uint32_t        m_width, m_height, m_pitch;
unsigned char   *lfb;


uint32_t        m_width_chars, m_height_chars;
uint32_t        m_x, m_y;

#define INIT_WIDTH  1920
#define INIT_HEIGHT 1080

#define BACKGROUND_COLOR 0x0000FF
#define FOREGROUND_COLOR 0xFFFF00

/**
 * Set screen resolution to 1024x768
 */
bool gpu_init()
{
    mbox[0] = 35*4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MAILBOX_TAG_SET_PHYSICAL_WIDTH_HEIGHT;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = INIT_WIDTH;         //FrameBufferInfo.width
    mbox[6] = INIT_HEIGHT;          //FrameBufferInfo.height

    mbox[7] = MAILBOX_TAG_SET_VIRTUAL_WIDTH_HEIGHT;  //set virt wh
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = INIT_WIDTH;        //FrameBufferInfo.virtual_width
    mbox[11] = INIT_HEIGHT;         //FrameBufferInfo.virtual_height
    
    mbox[12] = MAILBOX_TAG_SET_VIRTUAL_OFFSET; //set virt offset
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0;           //FrameBufferInfo.x_offset
    mbox[16] = 0;           //FrameBufferInfo.y.offset
    
    mbox[17] = MAILBOX_TAG_SET_COLOUR_DEPTH; //set depth
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32;          //FrameBufferInfo.depth

    mbox[21] = MAILBOX_TAG_SET_PIXEL_ORDER; //set pixel order
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1;           //RGB, not BGR preferably

    mbox[25] = MAILBOX_TAG_ALLOCATE_FRAMEBUFFER; //get framebuffer, gets alignment on request
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096;        //FrameBufferInfo.pointer
    mbox[29] = 0;           //FrameBufferInfo.size

    mbox[30] = MAILBOX_TAG_GET_PITCH; //get pitch
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0;           //FrameBufferInfo.pitch

    mbox[34] = MBOX_TAG_LAST;

    if(mbox_call(MBOX_CH_PROP) && mbox[20]==32 && mbox[28]!=0) {
        mbox[28]    &= 0x3FFFFFFF;
        m_width   = mbox[5];
        m_height  = mbox[6];
        m_pitch   = mbox[33];
        lfb     = (void*)((unsigned long)mbox[28]);
    } else {
        return false;   // Error unable to set the resolution to 1024x768
    }

    m_width_chars     = m_width / font->width;
    m_height_chars    = m_height / font->height;
    m_x     = 0;
    m_y    = 0;

    return true;
}

static void    char_to_real_coordinates(uint32_t cx, uint32_t cy, uint32_t* x, uint32_t* y) {
    *x = cx * font->width;
    *y = cy * font->height;
}

/**
 * Display a string
 */
void gpu_putc(char s, int x, int y)
{
    // draw next character if it's not zero

    // get the offset of the glyph. Need to adjust this to support unicode table
    unsigned char *glyph = (unsigned char*)&_binary_res_font_psf_start +
        font->headersize + ( s < font->numglyph ? s:0)*font->bytesperglyph;
    // calculate the offset on screen
    uint32_t real_x = 0;
    uint32_t real_y = 0;

    char_to_real_coordinates(x, y, &real_x, &real_y);

    int offset = (real_y * m_pitch) + real_x * 4;
    // variables
    int bytesperline = (font->width + 7) / 8;
    // handle carrige return

    // display a character
    for(int j = 0; j < font->height; j++) {
        
        int line = offset;
        int mask = 1 << (font->width-1);
        for(int i=0; i < font->width; i++) {
            *((unsigned int*)(lfb + line))=((int)*glyph) & mask ? FOREGROUND_COLOR : BACKGROUND_COLOR;
            mask >>= 1;
            line += 4;
        }
        // adjust to next line
        glyph += bytesperline;
        offset += m_pitch;
    }

}

void gpu_clear_screen() {
    for( int y = 0; y < m_height; y++) {
        for( int x = 0; x < m_width; x++) {
            *((unsigned int*)(lfb + (y * m_width + x)*4)) = BACKGROUND_COLOR;
        }
    }
}

void putc(char c) {
    if(c == '\n') {
        m_x = 0;
        m_y++;
    } else {
        gpu_putc(c, m_x, m_y);
        m_x++;
        if(m_x >= m_width_chars) {
            m_x = 0;
            m_y++;
        }
    }

    if( m_y >= m_height_chars )
        m_y = 0;
}

/*void _putchar(char c) {
    putc(c);
    uart_send(c);
}*/

size_t  gpu_get_line_char_count() {
    return m_width_chars;
}

size_t  gpu_get_lines_count() {
    return m_height_chars;
}