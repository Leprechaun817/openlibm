/* s_tanf.c -- float version of s_tan.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_tanf.c,v 1.17 2008/02/25 22:19:17 bde Exp $");

#include <float.h>
#include <openlibm_math.h>

//#define	INLINE_KERNEL_TANDF
//#define INLINE_REM_PIO2F
#include "math_private.h"
//#include "e_rem_pio2f.c"
//#include "k_tanf.c"

/* Small multiples of pi/2 rounded to double precision. */
static const double
t1pio2 = 1* 1.57079632679489661923,			/* 0x3FF921FB, 0x54442D18 */
t2pio2 = 2* 1.57079632679489661923,			/* 0x400921FB, 0x54442D18 */
t3pio2 = 3* 1.57079632679489661923,			/* 0x4012D97C, 0x7F3321D2 */
t4pio2 = 4* 1.57079632679489661923;			/* 0x401921FB, 0x54442D18 */

OLM_DLLEXPORT float
tanf(float x)
{
	double y;
	int32_t n, hx, ix;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	ix = hx & 0x7fffffff;

	if (ix <= 0x3f490fda) {		/* |x| ~<= pi/4 */
		if (ix < 0x39800000) {		/* |x| < 2**-12 */
			if (((int)x) == 0) {
				return x;	/* x with inexact if x != 0 */
			}
		}
		
		return __kernel_tandf(x, 1);
	}

	if(ix <= 0x407b53d1) {		/* |x| ~<= 5*pi/4 */
		if (ix <= 0x4016cbe3) {		/* |x| ~<= 3pi/4 */
			return __kernel_tandf(x + (hx > 0 ? -t1pio2 : t1pio2), -1);
		}
		else {
			return __kernel_tandf(x + (hx > 0 ? -t2pio2 : t2pio2), 1);
		}
	}

	if(ix <= 0x40e231d5) {		/* |x| ~<= 9*pi/4 */
		if (ix <= 0x40afeddf) {		/* |x| ~<= 7*pi/4 */
			return __kernel_tandf(x + (hx > 0 ? -t3pio2 : t3pio2), -1);
		}
		else {
			return __kernel_tandf(x + (hx > 0 ? -t4pio2 : t4pio2), 1);
		}
	}
	else if (ix >= 0x7f800000) {	/* tan(Inf or NaN) is NaN */
		return x - x;
	}
	else {							/* general argument reduction needed */
		n = __ieee754_rem_pio2f(x, &y);

		/* integer parameter: 1 -- n even; -1 -- n odd */
		return __kernel_tandf(y, 1 - ((n & 1) << 1));
	}
}
