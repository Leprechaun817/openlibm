/* e_acosf.c -- float version of e_acos.c.
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
//__FBSDID("$FreeBSD: src/lib/msun/src/e_acosf.c,v 1.11 2008/08/03 17:39:54 das Exp $");

#include "../include/openlibm_math.h"

#include "math_private.h"

static const float
one =  1.0000000000e+00, /* 0x3F800000 */
pi =  3.1415925026e+00, /* 0x40490fda */
pio2_hi =  1.5707962513e+00; /* 0x3fc90fda */
static volatile float
pio2_lo =  7.5497894159e-08; /* 0x33a22168 */
static const float
pS0 =  1.6666586697e-01,
pS1 = -4.2743422091e-02,
pS2 = -8.6563630030e-03,
qS1 = -7.0662963390e-01;

OLM_DLLEXPORT float
__ieee754_acosf(float x)
{
	float z, p, q, r, w, s, c, df;
	int32_t hx, ix;

	do {
		ieee_float_shape_type gf_u; 
		gf_u.value = (x); 
		(hx) = gf_u.word;
	} while (0);

	ix = hx & 0x7fffffff;
	if(ix >= 0x3f800000) {		/* |x| >= 1 */
		if(ix == 0x3f800000) {	/* |x| == 1 */
			if(hx > 0) 
				return 0.0;	/* acos(1) = 0 */
			else 
				return pi + (float) 2.0 * pio2_lo;	/* acos(-1)= pi */
	    }
	    
		return (x - x) / (x - x);		/* acos(|x|>1) is NaN */
	}

	if(ix < 0x3f000000) {	/* |x| < 0.5 */
		if (ix <= 0x32800000) {
			return pio2_hi + pio2_lo; /*if|x|<2**-26*/
		}

	    z = x * x;
	    p = z * (pS0 + z * (pS1 + z * pS2));
	    q = one + z * qS1;
	    r = p / q;

	    return pio2_hi - (x - (pio2_lo - x * r));
	} 
	else if (hx < 0) {		/* x < -0.5 */
	    z = (one + x) * (float)0.5;
	    p = z * (pS0 + z * (pS1 + z * pS2));
	    q = one + z * qS1;
	    
		s = sqrtf(z);
	    r = p / q;
	    w = r * s - pio2_lo;

	    return pi - (float)2.0 * (s + w);
	}
	else {			/* x > 0.5 */
	    int32_t idf;
	    z = (one - x) * (float)0.5;
	    s = sqrtf(z);
	    df = s;

		do {
			ieee_float_shape_type gf_u; 
			gf_u.value = (df); 
			(idf) = gf_u.word;
		} while (0);

		do {
			ieee_float_shape_type sf_u; 
			sf_u.word = (idf & 0xfffff000); 
			(df) = sf_u.value;
		} while (0);

	    c  = (z - df * df) / (s + df);
	    p = z * (pS0 + z * (pS1 + z * pS2));
	    q = one + z * qS1;

	    r = p / q;
	    w = r * s + c;
	    
		return (float)2.0 * (df + w);
	}
}
