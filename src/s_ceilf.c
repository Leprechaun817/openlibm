/* s_ceilf.c -- float version of s_ceil.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_ceilf.c,v 1.8 2008/02/22 02:30:35 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float huge = 1.0e30;

OLM_DLLEXPORT float
ceilf(float x)
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
			if (huge + x > (float)0.0) {/* return 0*sign(x) if |x|<1 */
				if (i0 < 0) { 
					i0 = 0x80000000; 
				}
				else if (i0 != 0) { 
					i0 = 0x3f800000; 
				}
			}
		}
		else {
			i = (0x007fffff) >> j0;

			if ((i0 & i) == 0) {
				return x; /* x is integral */
			}

			if (huge + x > (float)0.0) {	/* raise inexact flag */
				if (i0 > 0) {
					i0 += (0x00800000) >> j0;
				}

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
