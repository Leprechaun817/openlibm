/* s_sinf.c -- float version of s_sin.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 * Optimized by Bruce D. Evans.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/s_sinf.c,v 1.17 2008/02/25 22:19:17 bde Exp $");

#include <float.h>
#include "../include/openlibm_math.h"

//#define	INLINE_KERNEL_COSDF
//#define	INLINE_KERNEL_SINDF
//#define INLINE_REM_PIO2F
#include "math_private.h"
//#include "e_rem_pio2f.c"
//#include "k_cosf.c"
//#include "k_sinf.c"

/* Small multiples of pi/2 rounded to double precision. */
static const double
s1pio2 = 1* 1.57079632679489661923,			/* 0x3FF921FB, 0x54442D18 */
s2pio2 = 2* 1.57079632679489661923,			/* 0x400921FB, 0x54442D18 */
s3pio2 = 3* 1.57079632679489661923,			/* 0x4012D97C, 0x7F3321D2 */
s4pio2 = 4* 1.57079632679489661923;			/* 0x401921FB, 0x54442D18 */

OLM_DLLEXPORT float
sinf(float x)
{
	double y;
	int32_t n, hx, ix;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	ix = hx & 0x7fffffff;

	if(ix <= 0x3f490fda) {		/* |x| ~<= pi/4 */
		if (ix < 0x39800000) {	/* |x| < 2**-12 */
			if (((int)x) == 0) {
				return x;	/* x with inexact if x != 0 */
			}
		}

		return __kernel_sindf(x);
	}

	if(ix <= 0x407b53d1) {		/* |x| ~<= 5*pi/4 */
		if(ix <= 0x4016cbe3) {	/* |x| ~<= 3pi/4 */
			if (hx > 0) {
				return __kernel_cosdf(x - s1pio2);
			}
			else {
				return -__kernel_cosdf(x + s1pio2);
			}
		} 
		else {
			return __kernel_sindf((hx > 0 ? s2pio2 : -s2pio2) - x);
		}
	}

	if(ix <= 0x40e231d5) {		/* |x| ~<= 9*pi/4 */
		if(ix <= 0x40afeddf) {	/* |x| ~<= 7*pi/4 */
			if (hx > 0) {
				return -__kernel_cosdf(x - s3pio2);
			}
			else {
				return __kernel_cosdf(x + s3pio2);
			}
		} 
		else {
			return __kernel_sindf(x + (hx > 0 ? -s4pio2 : s4pio2));
		}
	}
	else if (ix >= 0x7f800000) {		/* sin(Inf or NaN) is NaN */
		return x - x;
	}
	else {								/* general argument reduction needed */
		n = __ieee754_rem_pio2f(x, &y);

		switch(n & 3) {
			case 0: 
				return __kernel_sindf(y);
			case 1: 
				return __kernel_cosdf(y);
			case 2: 
				return __kernel_sindf(-y);
			default:
				return -__kernel_cosdf(y);
		}
	}
}
