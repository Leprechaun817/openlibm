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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_truncf.c,v 1.1 2004/06/20 09:25:43 das Exp $");

/*
 * truncf(x)
 * Return x rounded toward 0 to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to truncf(x).
 */

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float huge = 1.0e30F;

OLM_DLLEXPORT float
truncf(float x)
{
	int32_t i0, j0;
	u_int32_t i;
	
	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(i0) = gf_u.word;
	} while (0);
	
	j0 = ((i0 >> 23) & 0xff) - 0x7f;

	if (j0 < 23) {
		if (j0 < 0) { 	/* raise inexact if x != 0 */
			if (huge + x > 0.0F) {/* |x|<1, so return 0*sign(x) */
				i0 &= 0x80000000;
			}
		}
		else {
			i = (0x007fffff) >> j0;
			
			if ((i0 & i) == 0) {
				return x; /* x is integral */
			}

			if (huge + x > 0.0F) {/* raise inexact flag */
				i0 &= (~i);
			}
		}
	}
	else {
		if (j0 == 0x80) {
			return x + x;	/* inf or NaN */
		}
		else {
			return x;		/* x is integral */
		}
	}

	do {
		ieee_float_shape_type sf_u; 
		sf_u.word = (i0); 
		(x) = sf_u.value;
	} while (0);
	
	return x;
}
