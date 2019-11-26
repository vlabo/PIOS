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

#ifndef STDINT_H
#define STDINT_H

#ifndef _INT8_T
#define _INT8_T
typedef __signed char           int8_t;
#endif /* _INT8_T */

#ifndef _INT16_T
#define _INT16_T
typedef short                   int16_t;
#endif /* _INT16_T */

#ifndef _INT32_T
#define _INT32_T
typedef int                     int32_t;
#endif /* _INT32_T */

#ifndef _INT64_T
#define _INT64_T
typedef long long               int64_t;
#endif /* _INT64_T */

#ifndef _U_INT8_T
#define _U_INT8_T
typedef unsigned char           uint8_t;
#endif /* _U_INT8_T */

#ifndef _U_INT16_T
#define _U_INT16_T
typedef unsigned short          uint16_t;
#endif /* _U_INT16_T */

#ifndef _U_INT32_T
#define _U_INT32_T
typedef unsigned int            uint32_t;
#endif /* _U_INT32_T */

#ifndef _U_INT64_T
#define _U_INT64_T
typedef unsigned long long      uint64_t;
#endif /* _U_INT64_T */

#if __LP64__
typedef int64_t                 register_t;

#ifndef _UINTPTR_T
#define _UINTPTR_T
typedef uint64_t           uintptr_t;
#endif /* _UINTPTR_T */

#ifndef _INTPTR_T
#define _INTPTR_T
typedef int64_t           intptr_t;
#endif /* _UINTPTR_T */

#else
typedef int32_t                 register_t;

#ifndef _UINTPTR_T
#define _UINTPTR_T
typedef uint32_t           uintptr_t;
#endif /* _UINTPTR_T */

#ifndef _INTPTR_T
#define _INTPTR_T
typedef int32_t           intptr_t;
#endif /* _INTPTR_T */

#endif

typedef long long                intmax_t;
typedef unsigned long long      uintmax_t;




/*Limits of exact-width integer types */
#define INT8_MAX         127
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807LL

#define INT8_MIN          -128
#define INT16_MIN         -32768
   /*
      Note:  the literal "most negative int" cannot be written in C --
      the rules in the standard (section 6.4.4.1 in C99) will give it
      an unsigned type, so INT32_MIN (and the most negative member of
      any larger signed type) must be written via a constant expression.
   */
#define INT32_MIN        (-INT32_MAX-1)
#define INT64_MIN        (-INT64_MAX-1)

#define UINT8_MAX         255
#define UINT16_MAX        65535
#define UINT32_MAX        4294967295U
#define UINT64_MAX        18446744073709551615ULL

/* 7.18.2.2 Limits of minimum-width integer types */
#define INT_LEAST8_MIN    INT8_MIN
#define INT_LEAST16_MIN   INT16_MIN
#define INT_LEAST32_MIN   INT32_MIN
#define INT_LEAST64_MIN   INT64_MIN

#define INT_LEAST8_MAX    INT8_MAX
#define INT_LEAST16_MAX   INT16_MAX
#define INT_LEAST32_MAX   INT32_MAX
#define INT_LEAST64_MAX   INT64_MAX

#define UINT_LEAST8_MAX   UINT8_MAX
#define UINT_LEAST16_MAX  UINT16_MAX
#define UINT_LEAST32_MAX  UINT32_MAX
#define UINT_LEAST64_MAX  UINT64_MAX

/* 7.18.2.3 Limits of fastest minimum-width integer types */
#define INT_FAST8_MIN     INT8_MIN
#define INT_FAST16_MIN    INT16_MIN
#define INT_FAST32_MIN    INT32_MIN
#define INT_FAST64_MIN    INT64_MIN

#define INT_FAST8_MAX     INT8_MAX
#define INT_FAST16_MAX    INT16_MAX
#define INT_FAST32_MAX    INT32_MAX
#define INT_FAST64_MAX    INT64_MAX

#define UINT_FAST8_MAX    UINT8_MAX
#define UINT_FAST16_MAX   UINT16_MAX
#define UINT_FAST32_MAX   UINT32_MAX
#define UINT_FAST64_MAX   UINT64_MAX

/* 7.18.2.4 Limits of integer types capable of holding object pointers */

#if __WORDSIZE == 64
#define INTPTR_MIN	  INT64_MIN
#define INTPTR_MAX	  INT64_MAX
#else
#define INTPTR_MIN        INT32_MIN
#define INTPTR_MAX        INT32_MAX
#endif

#if __WORDSIZE == 64
#define UINTPTR_MAX	  UINT64_MAX
#else
#define UINTPTR_MAX       UINT32_MAX
#endif

/* 7.18.2.5 Limits of greatest-width integer types */
#define INTMAX_MIN        INT64_MIN
#define INTMAX_MAX        INT64_MAX

#define UINTMAX_MAX       UINT64_MAX

/* 7.18.3 "Other" */
#if __WORDSIZE == 64
#define PTRDIFF_MIN	  INT64_MIN
#define PTRDIFF_MAX	  INT64_MAX
#else
#define PTRDIFF_MIN       INT32_MIN
#define PTRDIFF_MAX       INT32_MAX
#endif

/* We have no sig_atomic_t yet, so no SIG_ATOMIC_{MIN,MAX}.
   Should end up being {-127,127} or {0,255} ... or bigger.
   My bet would be on one of {U}INT32_{MIN,MAX}. */

#if __WORDSIZE == 64
#define SIZE_MAX	  UINT64_MAX
#else
#define SIZE_MAX          UINT32_MAX
#endif

#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1
#define RSIZE_MAX         (SIZE_MAX >> 1)
#endif

#ifndef WCHAR_MAX
#  ifdef __WCHAR_MAX__
#    define WCHAR_MAX     __WCHAR_MAX__
#  else
#    define WCHAR_MAX     0x7fffffff
#  endif
#endif

/* WCHAR_MIN should be 0 if wchar_t is an unsigned type and
   (-WCHAR_MAX-1) if wchar_t is a signed type.  Unfortunately,
   it turns out that -fshort-wchar changes the signedness of
   the type. */
#ifndef WCHAR_MIN
#  if WCHAR_MAX == 0xffff
#    define WCHAR_MIN       0
#  else
#    define WCHAR_MIN       (-WCHAR_MAX-1)
#  endif
#endif

#define WINT_MIN	  INT32_MIN
#define WINT_MAX	  INT32_MAX

#define SIG_ATOMIC_MIN	  INT32_MIN
#define SIG_ATOMIC_MAX	  INT32_MAX

/* 7.18.4 Macros for integer constants */
#define INT8_C(v)    (v)
#define INT16_C(v)   (v)
#define INT32_C(v)   (v)
#define INT64_C(v)   (v ## LL)

#define UINT8_C(v)   (v ## U)
#define UINT16_C(v)  (v ## U)
#define UINT32_C(v)  (v ## U)
#define UINT64_C(v)  (v ## ULL)

#define INTMAX_C(v)  (v ## LL)
#define UINTMAX_C(v) (v ## ULL)

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef uint64_t    ptrdiff_t;
#endif  /* _PTRDIFF_T */

#ifndef _HAVE_SIZE_T
#define _HAVE_SIZE_T
typedef uint64_t            size_t;
#endif


#endif  /* STDINT_H */