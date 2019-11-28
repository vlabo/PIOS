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

#include "string.h"
#include <assert.h>

void *memchr(const void *str, int c, size_t n) {
    not_implemented();
    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    char* p1 = (char*)str1;
    char* p2 = (char*)str2;
    for(int i = 0; i < n; i++, p1++, p2++) {
        if(*p1 != *p2) {
            return *p1 - *p2;
        }
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char* p1 = (char*)dest;
    char* p2 = (char*)src;
    for(int i = 0; i < n; i++, p1++, p2++) {
        *p1 = *p2;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    not_implemented();
    return NULL;
}

void *memset(void *str, int c, size_t n) {
    char* p = (char*)str;
    for(int i = 0; i < n; i++) {
        *p = (char)c;
    }
    return str;
}

char *strcat(char *dest, const char *src) {
    not_implemented();
    return NULL;
}

char *strncat(char *dest, const char *src, size_t n) {
    not_implemented();
    return NULL;
}

char *strchr(const char *str, int c) {
    not_implemented();
    return NULL;
}

int strcmp(const char *str1, const char *str2) {
    not_implemented();
    return 0;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    not_implemented();
    return 0;
}

int strcoll(const char *str1, const char *str2) {
    not_implemented();
    return 0;
}

char *strcpy(char *dest, const char *src) {
    not_implemented();
    return NULL;
}

char *strncpy(char *dest, const char *src, size_t n) {
    not_implemented();
    return NULL;
}

size_t strcspn(const char *str1, const char *str2) {
    not_implemented();
    return 0;
}

char *strerror(int errnum) {
    not_implemented();
    return NULL;
}

size_t strlen(const char *str) {
    size_t size = 0;
    while(*str != '\0') {
        size++;
        str++;
    }
    return size;
}

char *strpbrk(const char *str1, const char *str2) {
    not_implemented();
    return NULL;
}

char *strrchr(const char *str, int c) {
    not_implemented();
    return NULL;
}

size_t strspn(const char *str1, const char *str2) {
    not_implemented();
    return 0;
}

char *strstr(const char *haystack, const char *needle) {
    not_implemented();
    return NULL;
}

char *strtok(char *str, const char *delim) {
    not_implemented();
    return NULL;
}

size_t strxfrm(char *dest, const char *src, size_t n) {
    not_implemented();
    return 0;
}