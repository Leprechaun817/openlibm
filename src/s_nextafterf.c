/* s_nextafterf.c -- float version of s_nextafter.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_nextafterf.c,v 1.11 2008/02/22 02:30:35 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

OLM_DLLEXPORT float
nextafterf(float x, float y)
{
	volatile float t;
	int32_t hx, hy, ix, iy;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (y); 
		(hy) = gf_u.word;
	} while (0);

	ix = hx & 0x7fffffff;		/* |x| */
	iy = hy & 0x7fffffff;		/* |y| */

		/* x is nan */			/* y is nan */
	if ((ix > 0x7f800000) || (iy > 0x7f800000)) {
		return x + y;
	}

	if (x == y) {
		return y;		/* x=y, return y */
	}

	if (ix == 0) {				/* x == 0 */
		do {
			ieee_float_shape_type sf_u; 
			sf_u.word = ((hy & 0x80000000) | 1); 
			(x) = sf_u.value;
		} while (0);/* return +-minsubnormal */

		t = x * x;
		
		if (t == x) {
			return t;
		}
		else {
			return x;	/* raise underflow flag */
		}
	}

	if (hx >= 0) {				/* x > 0 */
		if (hx > hy) {				/* x > y, x -= ulp */
			hx -= 1;
		}
		else {				/* x < y, x += ulp */
			hx += 1;
		}
	}
	else {				/* x < 0 */
		if (hy >= 0 || hx > hy) {			/* x < y, x -= ulp */
			hx -= 1;
		}
		else {				/* x > y, x += ulp */
			hx += 1;
		}
	}

	hy = hx & 0x7f800000;
	
	if (hy >= 0x7f800000) {
		return x + x;	/* overflow  */
	}

	if (hy < 0x00800000) {		/* underflow */
		t = x * x;
		
		if (t != x) {		/* raise underflow flag */
			do {
				ieee_float_shape_type sf_u; 
				sf_u.word = (hx); 
				(y) = sf_u.value;
			} while (0);

			return y;
		}
	}
	
	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = (hx); 
		(x) = sf_u.value;
	} while (0);

	return x;
}
