/* @(#)s_frexp.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_frexp.c,v 1.11 2008/02/22 02:30:35 das Exp $");

/*
 * for non-zero x
 *	x = frexp(arg,&exp);
 * return a double fp quantity x such that 0.5 <= |x| <1.0
 * and the corresponding binary exponent "exp". That is
 *	arg = x*2^exp.
 * If arg is inf, 0.0, or NaN, then frexp(arg,&exp) returns arg
 * with *exp=0.
 */

#include <float.h>
#include "../include/openlibm_math.h"

#include "math_private.h"

static const double
two54 =  1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */

OLM_DLLEXPORT double
frexp(double x, int *eptr)
{
	int32_t hx, ix, lx;

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (x); 
		(hx) = ew_u.parts.msw; 
		(lx) = ew_u.parts.lsw;
	} while (0);

	ix = 0x7fffffff & hx;
	*eptr = 0;

	if (ix >= 0x7ff00000 || ((ix | lx) == 0)) {
		return x;	/* 0,inf,nan */
	}

	if (ix < 0x00100000) {		/* subnormal */
	    x *= two54;

		do {
			ieee_double_shape_type gh_u; 
			gh_u.value = (x); 
			(hx) = gh_u.parts.msw;
		} while (0);

	    ix = hx & 0x7fffffff;
	    *eptr = -54;
	}

	*eptr += (ix >> 20) - 1022;
	hx = (hx & 0x800fffff) | 0x3fe00000;

	do {
		ieee_double_shape_type sh_u; 
		sh_u.value = (x); 
		sh_u.parts.msw = (hx); 
		(x) = sh_u.value;
	} while (0);

	return x;
}

#if (LDBL_MANT_DIG == 53)
openlibm_weak_reference(frexp, frexpl);
#endif
