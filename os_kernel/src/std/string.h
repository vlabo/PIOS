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

#ifndef STRING_H
#define STRING_H

#include <stdlib.h>

/*
* Searches for the first occurrence of the character c (an unsigned char) in the first n bytes of the string pointed to,by the argument str.
*/
void *memchr(const void *str, int c, size_t n);

/*
* Compares the first n bytes of str1 and str2.
*/
int memcmp(const void *str1, const void *str2, size_t n);

/*
* Copies n characters from src to dest.
*/
void *memcpy(void *dest, const void *src, size_t n);

/*
* Another function to copy n characters from str2 to str1.
*/
void *memmove(void *dest, const void *src, size_t n);

/*
* Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.
*/
void *memset(void *str, int c, size_t n);

/*
* Appends the string pointed to, by src to the end of the string pointed to by dest.
*/
char *strcat(char *dest, const char *src);

/*
* Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long.
*/
char *strncat(char *dest, const char *src, size_t n);

/*
* Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str.
*/
const char *strchr(const char *str, int c);

/*
* Compares the string pointed to, by str1 to the string pointed to by str2.
*/
int strcmp(const char *str1, const char *str2);

/*
* Compares at most the first n bytes of str1 and str2.
*/
int strncmp(const char *str1, const char *str2, size_t n);

/*
* Compares string str1 to str2. The result is dependent on the LC_COLLATE setting of the location.
*/
int strcoll(const char *str1, const char *str2);

/*
* Copies the string pointed to, by src to dest.
*/
char *strcpy(char *dest, const char *src);

/*
* Copies up to n characters from the string pointed to, by src to dest.
*/
char *strncpy(char *dest, const char *src, size_t n);

/*
* Calculates the length of the initial segment of str1 which consists entirely of characters not in str2.
*/
size_t strcspn(const char *str1, const char *str2);

/*
* Searches an internal array for the error number errnum and returns a pointer to an error message string.
*/
char *strerror(int errnum);

/*
* Computes the length of the string str up to but not including the terminating null character.
*/
size_t strlen(const char *str);

/*
* Finds the first character in the string str1 that matches any character specified in str2.
*/
const char *strpbrk(const char *str1, const char *str2);

/*
* Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
*/
const char *strrchr(const char *str, int c);

/*
* Calculates the length of the initial segment of str1 which consists entirely of characters in str2.
*/
size_t strspn(const char *str1, const char *str2);

/*
* Finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
*/
const char *strstr(const char *str1, const char *str2);

#endif /* STRING_H */
