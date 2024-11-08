/* e_atanhf.c -- float version of e_atanh.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_atanhf.c,v 1.7 2008/02/22 02:30:34 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float one = 1.0, huge = 1e30;

static const float zero = 0.0;

OLM_DLLEXPORT float
__ieee754_atanhf(float x)
{
	float t;
	int32_t hx, ix;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	ix = hx & 0x7fffffff;

	if (ix > 0x3f800000) {/* |x|>1 */
		return (x - x) / (x - x);
	}

	if (ix == 0x3f800000) {
		return x / zero;
	}
	
	if (ix<0x31800000 && (huge + x)>zero) {
		return x;	/* x<2**-28 */
	}

	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = (ix); 
		(x) = sf_u.value;
	} while (0);

	if(ix < 0x3f000000) {		/* x < 0.5 */
	    t = x + x;
	    t = (float)0.5 * log1pf(t + t * x / (one - x));
	} 
	else {
		t = (float)0.5 * log1pf((x + x) / (one - x));
	}

	if (hx >= 0) {
		return t;
	}
	else {
		return -t;
	}
}
