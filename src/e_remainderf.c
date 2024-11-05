/* e_remainderf.c -- float version of e_remainder.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_remainderf.c,v 1.8 2008/02/12 17:11:36 bde Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float zero = 0.0;


OLM_DLLEXPORT float
__ieee754_remainderf(float x, float p)
{
	int32_t hx, hp;
	u_int32_t sx;
	float p_half;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (p); 
		(hp) = gf_u.word;
	} while (0);

	sx = hx & 0x80000000;

	hp &= 0x7fffffff;
	hx &= 0x7fffffff;

	/* purge off exception values */
	if (hp == 0) {
		return (x * p) / (x * p);	 	/* p = 0 */
	}

	/* x not finite */			/* p is NaN */
	if ((hx >= 0x7f800000) || ((hp > 0x7f800000))) {
		return ((long double)x * p) / ((long double)x * p);
	}

	if (hp <= 0x7effffff) {
		x = __ieee754_fmodf(x, p + p);	/* now x < 2p */
	}

	if ((hx - hp) == 0) {
		return zero * x;
	}

	x  = fabsf(x);
	p  = fabsf(p);
	
	if (hp < 0x01000000) {
		if (x + x > p) {
			x -= p;

			if (x + x >= p) {
				x -= p;
			}
		}
	}
	else {
		p_half = (float)0.5 * p;
		
		if (x > p_half) {
			x -= p;

			if (x >= p_half) {
				x -= p;
			}
		}
	}

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	if ((hx & 0x7fffffff) == 0) {
		hx = 0;
	}

	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = (hx ^ sx); 
		(x) = sf_u.value;
	} while (0);

	return x;
}
