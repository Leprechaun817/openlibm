
/* @(#)e_remainder.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

#include "cdefs-compat.h"
//__FBSDID("$FreeBSD: src/lib/msun/src/e_remainder.c,v 1.12 2008/03/30 20:47:42 das Exp $");

/* __ieee754_remainder(x,p)
 * Return :                  
 * 	returns  x REM p  =  x - [x/p]*p as if in infinite 
 * 	precise arithmetic, where [x/p] is the (infinite bit) 
 *	integer nearest x/p (in half way case choose the even one).
 * Method : 
 *	Based on fmod() return x-[x/p]chopped*p exactlp.
 */

#include <float.h>
#include "../include/openlibm_math.h"

#include "math_private.h"

static const double zero = 0.0;


OLM_DLLEXPORT double
__ieee754_remainder(double x, double p)
{
	int32_t hx, hp;
	u_int32_t sx, lx, lp;
	double p_half;

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (x); 
		(hx) = ew_u.parts.msw; 
		(lx) = ew_u.parts.lsw;
	} while (0);

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (p); 
		(hp) = ew_u.parts.msw; 
		(lp) = ew_u.parts.lsw;
	} while (0);

	sx = hx & 0x80000000;

	hp &= 0x7fffffff;
	hx &= 0x7fffffff;

	/* purge off exception values */
	if ((hp | lp) == 0) {
		return (x * p) / (x * p); 	/* p = 0 */
	}

	/* x not finite */			/* p is NaN */
	if ((hx >= 0x7ff00000) || ((hp >= 0x7ff00000) && (((hp - 0x7ff00000) | lp) != 0))) {
		return ((long double)x * p) / ((long double)x * p);
	}


	if (hp <= 0x7fdfffff) {
		x = __ieee754_fmod(x, p + p);	/* now x < 2p */
	}

	if (((hx - hp) | (lx - lp)) == 0) {
		return zero * x;
	}

	x  = fabs(x);
	p  = fabs(p);

	if (hp < 0x00200000) {
		if (x + x > p) {
			x -= p;

			if (x + x >= p) {
				x -= p;
			}
		}
	}
	else {
		p_half = 0.5 * p;

		if (x > p_half) {
			x -= p;

			if (x >= p_half) {
				x -= p;
			}
		}
	}

	do {
		ieee_double_shape_type gh_u; 
		gh_u.value = (x); 
		(hx) = gh_u.parts.msw;
	} while (0);

	if ((hx & 0x7fffffff) == 0) {
		hx = 0;
	}

	do {
		ieee_double_shape_type sh_u; 
		sh_u.value = (x); 
		sh_u.parts.msw = (hx ^ sx); 
		(x) = sh_u.value;
	} while (0);

	return x;
}

#if LDBL_MANT_DIG == 53
openlibm_weak_reference(remainder, remainderl);
#endif
