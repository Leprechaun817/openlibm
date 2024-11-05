/* s_frexpf.c -- float version of s_frexp.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_frexpf.c,v 1.10 2008/02/22 02:30:35 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float
two25 = 3.3554432000e+07; /* 0x4c000000 */

OLM_DLLEXPORT float
frexpf(float x, int *eptr)
{
	int32_t hx, ix;
	
	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);
	
	ix = 0x7fffffff & hx;
	*eptr = 0;

	if (ix >= 0x7f800000 || (ix == 0)) {
		return x;	/* 0,inf,nan */
	}

	if (ix < 0x00800000) {		/* subnormal */
	    x *= two25;

		do {
			ieee_float_shape_type gf_u; 
			gf_u.value = (x); 
			(hx) = gf_u.word;
		} while (0);

	    ix = hx & 0x7fffffff;
	    *eptr = -25;
	}

	*eptr += (ix >> 23) - 126;
	hx = (hx & 0x807fffff) | 0x3f000000;
	
	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = (hx); 
		(x) = sf_u.value;
	} while (0);
	
	return x;
}
