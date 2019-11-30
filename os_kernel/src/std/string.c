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
    char* p = (char*)str;
    for(int i = 0; i < n; i++) {
        if(*p == (char)c) {
            return p;
        }
        p++;
    }
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

void *memcpy_forward(void *dest, const void *src, size_t n) {

    uint64_t* dest64 = (uint64_t*) dest;
    uint64_t* src64 = (uint64_t*) src;

    while(n >= sizeof(uint64_t)) {
        *dest64 = *src64;
        dest64++;
        src64++;
        n -= sizeof(uint64_t);
    }

    char* p1 = (char*) dest64;
    char* p2 = (char*) src64;
    while(n > 0) {
        *p1 = *p2;
        n--;
    }

    return dest;
}

void *memcpy_backword(void *dest, const void *src, size_t n) {
    // TODO: optimize with 64 bit chunks of memory when possible.
    char* p1 = (char*)dest + n - 1;
    char* p2 = (char*)src + n - 1;
    for(int i = 0; i < n; i++, p1--, p2--) {
        *p1 = *p2;
    }

    return dest;
}

void *memcpy(void *dest, const void *src, size_t n) {
    return memcpy_forward(dest, src, n);
} 

void *memmove(void *dest, const void *src, size_t n) {
    // memory dose not overlap
    if(dest > src + n - 1 || dest + n - 1 < src) {
        return memcpy_forward(dest, src, n);
    }

    if(dest > src) {
        memcpy_backword(dest, src, n);
    } else if (dest < src){
        memcpy_forward(dest, src, n);
    }

    return dest;
}

void *memset(void *str, int c, size_t n) {
    for(int i = 0; i < n; i++) {
        ((char*)str)[i] = (char)c;
    }
    return str;
}

char *strcat(char *dest, const char *src) {
    while(*dest != '\0') {
        dest++;
    }

    do{
        *dest = *src;
        dest++;
        src++;
    } while(*src != '\0');

    return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
    while(*dest != '\0') {
        dest++;
    }
    for(int i = 0; i < n && *src == '\0'; i++, dest++, src++) {
        *dest = *src;   
    }
    dest++;
    *dest = '\0';

    return dest;
}

const char *strchr(const char *str, int c) {
    while(*str != '\0') {
        if(*str == (char) c) {
            break;
        }
        str++;
    }
    return str;
}

int strcmp(const char *str1, const char *str2) {
    for(; str1 != '\0' && str2 != '\0'; str1++, str2++) {
        if(*str1 != *str2) {
            return *str1 - *str2;
        }
    }
    return 0;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    for(int i = 0; i < n && str1 != '\0' && str2 != '\0'; i++, str1++, str2++) {
        if(*str1 != *str2) {
            return *str1 - *str2;
        }
    }
    return 0;
}

int strcoll(const char *str1, const char *str2) {
    warning("strcoll() not implemented calling strcmp() insted.");
    return strcmp(str1, str2);
}

char *strcpy(char *dest, const char *src) {
    do {
        *dest = *src;
        dest++;
        src++;
    } while(*src != '\0');
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
    return memcpy((void*)dest, (void*)src, n);
}

size_t strcspn(const char *str1, const char *str2) {
    size_t size2 = strlen(str1);
    size_t count = 0;
    while(*str1 != '\0') {
        char current_char = *str1;
        bool is_charecter_in = false;
        for(int i = 0;i < size2; i++) {
            if(current_char == str2[i]) {
                is_charecter_in = true;
                break;
            }
        }

        if(is_charecter_in) {
            count++;
        }
    }
    return count;
}

char *strerror(int errnum) {
    not_implemented();
    return NULL;
}

size_t strlen(const char *str) {
    const char* p = str;
    while(*p != '\0') {
        p++;
    }
    return p - str;
}

const char *strpbrk(const char *str1, const char *str2) {
    size_t size2 = strlen(str2);
    while(*str1 != '\0') {
        for(int i = 0; i < size2; i++) {
            if(*str1 == str2[i]) {
                return str1;
            }
        }
        str1++;
    }
    return NULL;
}

const char *strrchr(const char *str, int c) {
    size_t size = strlen(str);
    for(int i = size - 1; i >= 0; i--) {
        if(str[i] == (char)c) {
            return &str[i];
        }

    }
    return NULL;
}

const char *strstr(const char *str1, const char *str2) {
    size_t size1 = strlen(str1);
    size_t size2 = strlen(str2);
    if(size1 < size2) {
        return NULL;
    }

    for(int i = 0; i < size1; i++) {
        bool found = false;
        for(int j = 0; j < size2; j++) {
            if(str1[i] != str2[j]) {
                break;
            }
            found = true;
        }
        if(found) {
            return &str1[i];
        }
    } 
    return NULL;
}
