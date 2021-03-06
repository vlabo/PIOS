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

#ifndef ASSERT_H
#define ASSERT_H

#define static_assert(bool_constexpr, message) 		_Static_assert(bool_constexpr, message)

#ifdef NDEBUG
	#define assert(expr)	((void) 0)
#else
	void assertion_failed(const char *expresion, const char *file, const char *function, unsigned line);
	void not_implemented_error(const char *file, const char *function, unsigned line);
	void display_warning(const char *message, const char *file, const char *function, unsigned line);

	#define assert(expr)		((expr)	? ((void) 0) : assertion_failed (#expr, __FILE__, __FUNCTION__, __LINE__))
	#define not_implemented()	not_implemented_error( __FILE__, __FUNCTION__, __LINE__)
	#define warning(message)	display_warning(message, __FILE__, __FUNCTION__, __LINE__)
#endif

#endif