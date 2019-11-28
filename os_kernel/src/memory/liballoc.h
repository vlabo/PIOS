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

#ifndef _LIBALLOC_H
#define _LIBALLOC_H

#include <stdlib.h>

/** \defgroup ALLOCHOOKS liballoc hooks 
 *
 * These are the OS specific functions which need to 
 * be implemented on any platform that the library
 * is expected to work on.
 */

/** @{ */



// If we are told to not define our own size_t, then we skip the define.
//#define _HAVE_UINTPTR_T
//typedef	unsigned long	uintptr_t;

//This lets you prefix malloc and friends
#define PREFIX(func)		func

#ifdef __cplusplus
extern "C" {
#endif



/** This function is supposed to lock the memory data structures. It
 * could be as simple as disabling interrupts or acquiring a spinlock.
 * It's up to you to decide. 
 *
 * \return 0 if the lock was acquired successfully. Anything else is
 * failure.
 */
extern int liballoc_lock();

/** This function unlocks what was previously locked by the liballoc_lock
 * function.  If it disabled interrupts, it enables interrupts. If it
 * had acquiried a spinlock, it releases the spinlock. etc.
 *
 * \return 0 if the lock was successfully released.
 */
extern int liballoc_unlock();

/** This is the hook into the local system which allocates pages. It
 * accepts an integer parameter which is the number of pages
 * required.  The page size was set up in the liballoc_init function.
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */
extern void* liballoc_alloc(size_t);

/** This frees previously allocated memory. The void* parameter passed
 * to the function is the exact same value returned from a previous
 * liballoc_alloc call.
 *
 * The integer value is the number of pages to free.
 *
 * \return 0 if the memory was successfully freed.
 */
extern int liballoc_free(void*,size_t);


       

void    *PREFIX(malloc)(size_t);                 ///< The standard function.
void    *PREFIX(realloc)(void *, size_t);        ///< The standard function.
void    *PREFIX(calloc)(size_t, size_t);         ///< The standard function.
void     PREFIX(free)(void *);                   ///< The standard function.
//void    *PREFIX(memset)(void*, int, size_t);     ///< The standard function.
//void    *PREFIX(memcpy)(void*, void*, size_t);   ///< The standard function.


#ifdef __cplusplus
}
#endif


/** @} */

#endif


