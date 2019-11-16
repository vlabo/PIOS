#ifndef TYPES_H
#define TYPES_H

#define NULL ((void*)0)
typedef unsigned long       uint64_t;
typedef unsigned int        uint32_t;
typedef unsigned short      uint16_t;
typedef unsigned char       uint8_t;

typedef uint64_t            size_t;
typedef unsigned long       uintptr_t;

typedef unsigned long long  intmax_t;
typedef unsigned long       ptrdiff_t;

#define	__bool_true_false_are_defined	1

#define	false	0
#define	true	1

#define	bool	_Bool
#if __STDC_VERSION__ < 199901L && __GNUC__ < 3
typedef	int	_Bool;
#endif

#endif
