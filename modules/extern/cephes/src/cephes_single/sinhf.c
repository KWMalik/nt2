/*							sinhf.c
 *
 *	Hyperbolic sine
 *
 *
 *
 * SYNOPSIS:
 *
 * float x, y, cephes_sinhf();
 *
 * y = cephes_sinhf( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns hyperbolic sine of argument in the range MINLOGF to
 * MAXLOGF.
 *
 * The range is partitioned into two segments.  If |x| <= 1, a
 * polynomial approximation is used.
 * Otherwise the calculation is sinh(x) = ( exp(x) - exp(-x) )/2.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     +-MAXLOG     100000      1.1e-7      2.9e-8
 *
 */

/*
Cephes Math Library Release 2.2:  June, 1992
Copyright 1984, 1987, 1989, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

/* Single precision hyperbolic sine
 * test interval: [-1, +1]
 * trials: 10000
 * peak relative error: 9.0e-8
 * rms relative error: 3.0e-8
 */
#include "mconf.h"
extern float MAXLOGF, MAXNUMF;

#ifdef ANSIC
float cephes_expf( float );

float cephes_sinhf( float xx )
#else
float cephes_expf();

float cephes_sinhf(xx)
double xx;
#endif
{
register float z;
float x;

x = xx;
if( xx < 0 )
	z = -x;
else
	z = x;

if( z > MAXLOGF )
	{
	  if( x > 0 )
	    return( 1.0f/ZEROF );
	  else
	    return( -1.0f/ZEROF );
	}
if( z > 1.0f )
	{
	z = cephes_expf(z);
	z = 0.5f*z - (0.5f/z);
	if( x < 0 )
		z = -z;
	return z;
	}
 else if( z <= 1.0f )
	{
	z = x * x;
	z =
	(( 2.03721912945E-4f * z
	  + 8.33028376239E-3f) * z
	  + 1.66667160211E-1f) * z * x
	  + x;
	return z;
	}
 return( x );
}
