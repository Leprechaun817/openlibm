/* @(#)s_nextafter.c 5.1 93/09/24 */
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
//__FBSDID("$FreeBSD: src/lib/msun/src/s_nextafter.c,v 1.12 2008/02/22 02:30:35 das Exp $");

/* IEEE functions
 *	nextafter(x,y)
 *	return the next machine floating-point number of x in the
 *	direction toward y.
 *   Special cases:
 */

#include <float.h>
#include "../include/openlibm_math.h"

#include "math_private.h"

OLM_DLLEXPORT double
nextafter(double x, double y)
{
	volatile double t;
	int32_t hx, hy, ix, iy;
	u_int32_t lx, ly;

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (x); 
		(hx) = ew_u.parts.msw; 
		(lx) = ew_u.parts.lsw;
	} while (0);

	do {
		ieee_double_shape_type ew_u; 
		ew_u.value = (y); 
		(hy) = ew_u.parts.msw; 
		(ly) = ew_u.parts.lsw;
	} while (0);

	ix = hx & 0x7fffffff;		/* |x| */
	iy = hy & 0x7fffffff;		/* |y| */

	if (((ix >= 0x7ff00000) && ((ix - 0x7ff00000) | lx) != 0) ||   /* x is nan */
		((iy >= 0x7ff00000) && ((iy - 0x7ff00000) | ly) != 0)) {    /* y is nan */
		return x + y;
	}

	if (x == y) {
		return y;		/* x=y, return y */
	}

	if ((ix | lx) == 0) {			/* x == 0 */
		do {
			ieee_double_shape_type iw_u; 
			iw_u.parts.msw = (hy & 0x80000000); 
			iw_u.parts.lsw = (1); 
			(x) = iw_u.value;
		} while (0);	/* return +-minsubnormal */

		t = x * x;

		if (t == x) {
			return t;
		}
		else {
			return x;	/* raise underflow flag */
		}
	}

	if (hx >= 0) {				/* x > 0 */
		if (hx > hy || ((hx == hy) && (lx > ly))) {	/* x > y, x -= ulp */
			if (lx == 0) {
				hx -= 1;
			}

			lx -= 1;
		}
		else {				/* x < y, x += ulp */
			lx += 1;
			
			if (lx == 0) {
				hx += 1;
			}
		}
	}
	else {				/* x < 0 */
		if (hy >= 0 || hx > hy || ((hx == hy) && (lx > ly))) {/* x < y, x -= ulp */
			if (lx == 0) {
				hx -= 1;
			}

			lx -= 1;
		}
		else {				/* x > y, x += ulp */
			lx += 1;
			
			if (lx == 0) {
				hx += 1;
			}
		}
	}
	hy = hx & 0x7ff00000;

	if (hy >= 0x7ff00000) {
		return x + x;	/* overflow  */
	}

	if (hy < 0x00100000) {		/* underflow */
		t = x * x;
		
		if (t != x) {		/* raise underflow flag */
			do {
				ieee_double_shape_type iw_u; 
				iw_u.parts.msw = (hx); 
				iw_u.parts.lsw = (lx); 
				(y) = iw_u.value;
			} while (0);

			return y;
		}
	}

	do {
		ieee_double_shape_type iw_u; 
		iw_u.parts.msw = (hx); 
		iw_u.parts.lsw = (lx); 
		(x) = iw_u.value;
	} while (0);

	return x;
}

#if (LDBL_MANT_DIG == 53)
openlibm_weak_reference(nextafter, nexttoward);
openlibm_weak_reference(nextafter, nexttowardl);
openlibm_weak_reference(nextafter, nextafterl);
#endif
