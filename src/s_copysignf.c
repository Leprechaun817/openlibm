/* s_copysignf.c -- float version of s_copysign.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_copysignf.c,v 1.10 2008/02/22 02:30:35 das Exp $");

/*
 * copysignf(float x, float y)
 * copysignf(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

#include "../include/openlibm_math.h"

#include "math_private.h"

OLM_DLLEXPORT float
copysignf(float x, float y)
{
	u_int32_t ix,iy;
	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(ix) = gf_u.word;
	} while (0);

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (y); 
		(iy) = gf_u.word;
	} while (0);

	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = ((ix & 0x7fffffff) | (iy & 0x80000000)); 
		(x) = sf_u.value;
	} while (0);
        return x;
}
