/* @(#)s_modf.c 5.1 93/09/24 */
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

/*
 * modf(double x, double *iptr)
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *	Bit twiddling.
 *
 * Exception:
 *	No exception.
 */

#include "../include/openlibm_math.h"

#include "math_private.h"

static const double one = 1.0;

OLM_DLLEXPORT double
modf(double x, double* iptr)
{
	int32_t i0, i1, j0;
	u_int32_t i;

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (x); 
		(i0) = ew_u.parts.msw; 
		(i1) = ew_u.parts.lsw;
	} while (0);

	j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;	/* exponent of x */

	if (j0 < 20) {			/* integer part in high x */
		if (j0 < 0) {			/* |x|<1 */
			do {
				ieee_double_shape_type iw_u; 
				iw_u.parts.msw = (i0 & 0x80000000); 
				iw_u.parts.lsw = (0); 
				(*iptr) = iw_u.value;
			} while (0);	/* *iptr = +-0 */

			return x;
		}
		else {
			i = (0x000fffff) >> j0;

			if (((i0 & i) | i1) == 0) {		/* x is integral */
				u_int32_t high;

				*iptr = x;
				
				do {
					ieee_double_shape_type gh_u; 
					gh_u.value = (x); 
					(high) = gh_u.parts.msw;
				} while (0);

				do {
					ieee_double_shape_type iw_u; 
					iw_u.parts.msw = (high & 0x80000000); 
					iw_u.parts.lsw = (0); 
					(x) = iw_u.value;
				} while (0);	/* return +-0 */

				return x;
			}
			else {
				do {
					ieee_double_shape_type iw_u; 
					iw_u.parts.msw = (i0 & (~i)); 
					iw_u.parts.lsw = (0); 
					(*iptr) = iw_u.value;
				} while (0);
				
				return x - *iptr;
			}
		}
	}
	else if (j0 > 51) {		/* no fraction part */
		u_int32_t high;

		if (j0 == 0x400) {		/* inf/NaN */
			*iptr = x;

			return 0.0 / x;
		}

		*iptr = x * one;

		do {
			ieee_double_shape_type gh_u; 
			gh_u.value = (x); 
			(high) = gh_u.parts.msw;
		} while (0);

		do {
			ieee_double_shape_type iw_u; 
			iw_u.parts.msw = (high & 0x80000000); 
			iw_u.parts.lsw = (0); 
			(x) = iw_u.value;
		} while (0);	/* return +-0 */

		return x;
	}
	else {			/* fraction part in low x */
		i = ((u_int32_t)(0xffffffff)) >> (j0 - 20);

		if ((i1 & i) == 0) { 		/* x is integral */
			u_int32_t high;

			*iptr = x;

			do {
				ieee_double_shape_type gh_u; 
				gh_u.value = (x); 
				(high) = gh_u.parts.msw;
			} while (0);

			do {
				ieee_double_shape_type iw_u; 
				iw_u.parts.msw = (high & 0x80000000); 
				iw_u.parts.lsw = (0); 
				(x) = iw_u.value;
			} while (0);	/* return +-0 */

			return x;
		}
		else {
			do {
				ieee_double_shape_type iw_u; 
				iw_u.parts.msw = (i0); 
				iw_u.parts.lsw = (i1 & (~i)); 
				(*iptr) = iw_u.value;
			} while (0);

			return x - *iptr;
		}
	}
}
