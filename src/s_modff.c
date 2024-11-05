/* s_modff.c -- float version of s_modf.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_modff.c,v 1.9 2008/02/22 02:30:35 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float one = 1.0;

OLM_DLLEXPORT float
modff(float x, float* iptr)
{
	int32_t i0, j0;
	u_int32_t i;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(i0) = gf_u.word;
	} while (0);

	j0 = ((i0 >> 23) & 0xff) - 0x7f;	/* exponent of x */

	if (j0 < 23) {			/* integer part in x */
		if (j0 < 0) {			/* |x|<1 */
			do {
				ieee_float_shape_type sf_u; 
				sf_u.word = (i0 & 0x80000000); 
				(*iptr) = sf_u.value;
			} while (0);	/* *iptr = +-0 */

			return x;
		}
		else {
			i = (0x007fffff) >> j0;

			if ((i0 & i) == 0) {			/* x is integral */
				u_int32_t ix;
				*iptr = x;

				do {
					ieee_float_shape_type gf_u; 
					gf_u.value = (x); 
					(ix) = gf_u.word;
				} while (0);

				do {
					ieee_float_shape_type sf_u; 
					sf_u.word = (ix & 0x80000000); 
					(x) = sf_u.value;
				} while (0);	/* return +-0 */

				return x;
			}
			else {
				do {
					ieee_float_shape_type sf_u; 
					sf_u.word = (i0 & (~i)); 
					(*iptr) = sf_u.value;
				} while (0);

				return x - *iptr;
			}
		}
	}
	else {			/* no fraction part */
		u_int32_t ix;

		*iptr = x * one;

		if (x != x) {/* NaN */
			return x;
		}

		do {
			ieee_float_shape_type gf_u; 
			gf_u.value = (x); 
			(ix) = gf_u.word;
		} while (0);

		do {
			ieee_float_shape_type sf_u; 
			sf_u.word = (ix & 0x80000000); 
			(x) = sf_u.value;
		} while (0);	/* return +-0 */

		return x;
	}
}
