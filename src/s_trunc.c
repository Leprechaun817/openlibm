/* @(#)s_floor.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_trunc.c,v 1.4 2008/02/22 02:27:34 das Exp $");

/*
 * trunc(x)
 * Return x rounded toward 0 to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to trunc(x).
 */

#include <float.h>
#include "../include/openlibm_math.h"

#include "math_private.h"

static const double huge = 1.0e300;

OLM_DLLEXPORT double
trunc(double x)
{
	int32_t i0, i1, j0;
	u_int32_t i;

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (x); 
		(i0) = ew_u.parts.msw; 
		(i1) = ew_u.parts.lsw;
	} while (0);

	j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
	
	if (j0 < 20) {
		if (j0 < 0) { 	/* raise inexact if x != 0 */
			if (huge + x > 0.0) {/* |x|<1, so return 0*sign(x) */
				i0 &= 0x80000000U;
				i1 = 0;
			}
		}
		else {
			i = (0x000fffff) >> j0;

			if (((i0 & i) | i1) == 0) {
				return x; /* x is integral */
			}

			if (huge + x > 0.0) {	/* raise inexact flag */
				i0 &= (~i); 
				i1 = 0;
			}
		}
	}
	else if (j0 > 51) {
		if (j0 == 0x400) {
			return x + x;	/* inf or NaN */
		}
		else {
			return x;		/* x is integral */
		}
	}
	else {
		i = ((u_int32_t)(0xffffffff)) >> (j0 - 20);

		if ((i1 & i) == 0) {
			return x;	/* x is integral */
		}

		if (huge + x > 0.0) {/* raise inexact flag */
			i1 &= (~i);
		}
	}

	do {
		ieee_double_shape_type iw_u; 
		iw_u.parts.msw = (i0); 
		iw_u.parts.lsw = (i1); 
		(x) = iw_u.value;
	} while (0);
	
	return x;
}

#if LDBL_MANT_DIG == 53
openlibm_weak_reference(trunc, truncl);
#endif
