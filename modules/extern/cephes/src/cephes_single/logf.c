/*							logf.c
 *
 *	Natural logarithm
 *
 *
 *
 * SYNOPSIS:
 *
 * float x, y, cephes_logf();
 *
 * y = cephes_logf( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the base e (2.718...) logarithm of x.
 *
 * The argument is separated into its exponent and fractional
 * parts.  If the exponent is between -1 and +1, the logarithm
 * of the fraction is approximated by
 *
 *     log(1+x) = x - 0.5 x**2 + x**3 P(x)
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0.5, 2.0    100000       7.6e-8     2.7e-8
 *    IEEE      1, MAXNUMF  100000                  2.6e-8
 *
 * In the tests over the interval [1, MAXNUM], the logarithms
 * of the random arguments were uniformly distributed over
 * [0, MAXLOGF].
 *
 * ERROR MESSAGES:
 *
 * logf singularity:  x = 0; returns MINLOG
 * logf domain:       x < 0; returns MINLOG
 */

/*
Cephes Math Library Release 2.2:  June, 1992
Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

/* Single precision natural logarithm
 * test interval: [sqrt(2)/2, sqrt(2)]
 * trials: 10000
 * peak relative error: 7.1e-8
 * rms relative error: 2.7e-8
 */

#include "mconf.h"
extern float MINLOGF, SQRTHF;


#if ANSIC
float cephes_frexpf( float, int * );

float cephes_logf( float xx )
#else
float cephes_frexpf();

float cephes_logf( xx )
double xx;
#endif
{
register float y;
float x, z, fe;
int e;

x = xx;
fe = 0.0;
/* Test for domain */
if( x <= 0.0f )
	{
	if( x == 0.0f )
	  return -1.0f/ZEROF;
	else
	  return 0.0f/ZEROF;
	}

x = cephes_frexpf( x, &e );
if( x < SQRTHF )
	{
	e -= 1;
	x = x + x - 1.0f; /*  2x - 1  */
	}	
 else if( x >= SQRTHF )
	{
	x = x - 1.0f;
	}
 else return x;

z = x * x;
/* 3.4e-9 */
/*
p = logfcof;
y = *p++ * x;
for( i=0; i<8; i++ )
	{
	y += *p++;
	y *= x;
	}
y *= z;
*/

y =
(((((((( 7.0376836292E-2f * x
- 1.1514610310E-1f) * x
+ 1.1676998740E-1f) * x
- 1.2420140846E-1f) * x
+ 1.4249322787E-1f) * x
- 1.6668057665E-1f) * x
+ 2.0000714765E-1f) * x
- 2.4999993993E-1f) * x
+ 3.3333331174E-1f) * x * z;

if( e )
	{
	fe = e;
	y += -2.12194440e-4f * fe;
	}

y +=  -0.5f * z;  /* y - 0.5 x^2 */
z = x + y;   /* ... + x  */

if( e )
	z += 0.693359375f * fe;

return( z );
}
