/* @(#)s_copysign.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_copysign.c,v 1.10 2008/02/22 02:30:35 das Exp $");

/*
 * copysign(double x, double y)
 * copysign(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

#include "../include/openlibm_math.h"

#include "math_private.h"

OLM_DLLEXPORT double
copysign(double x, double y)
{
	u_int32_t hx,hy;
	do {
		ieee_double_shape_type gh_u; 
		gh_u.value = (x); 
		(hx) = gh_u.parts.msw;
	} while (0);

	do {
		ieee_double_shape_type gh_u; 
		gh_u.value = (y); 
		(hy) = gh_u.parts.msw;
	} while (0);

	do {
		ieee_double_shape_type sh_u; 
		sh_u.value = (x); 
		sh_u.parts.msw = ((hx & 0x7fffffff) | (hy & 0x80000000)); 
		(x) = sh_u.value;
	} while (0);

        return x;
}
