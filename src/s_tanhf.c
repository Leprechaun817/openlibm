/* s_tanhf.c -- float version of s_tanh.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_tanhf.c,v 1.9 2008/02/22 02:30:36 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float 
	one=1.0, 
	two=2.0, 
	tiny = 1.0e-30, 
	huge = 1.0e30;

OLM_DLLEXPORT float
tanhf(float x)
{
	float t, z;
	int32_t jx, ix;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(jx) = gf_u.word;
	} while (0);

	ix = jx & 0x7fffffff;

	/* x is INF or NaN */
	if(ix >= 0x7f800000) {
		if (jx >= 0) {
			return one / x + one;    /* tanh(+-inf)=+-1 */
		}
		else {
			return one / x - one;    /* tanh(NaN) = NaN */
		}
	}

	/* |x| < 9 */
	if (ix < 0x41100000) {		/* |x|<9 */
		if (ix < 0x39800000) {	/* |x|<2**-12 */
			if (huge + x > one) {
				return x; /* tanh(tiny) = tiny with inexact */
			}
		}

		if (ix >= 0x3f800000) {	/* |x|>=1  */
			t = expm1f(two * fabsf(x));
			z = one - two / (t + two);
		} 
		else {
			t = expm1f(-two * fabsf(x));
			z = -t / (t + two);
		}
	/* |x| >= 9, return +-1 */
	} 
	else {
		z = one - tiny;		/* raise inexact flag */
	}

	return (jx >= 0) ? z: -z;
}
