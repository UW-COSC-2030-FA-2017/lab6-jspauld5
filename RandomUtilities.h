// RandomUtilities.h

// tom bailey   7 mar 03
// Random Variate generation.

// tom bailey   0900  21 feb 2012
// Revisions to match current version of rand().

// tom bailey   1420   23 mar 2012
// Revision of the definition of randomInt.


#ifndef _RANDOM_UTILITIES_H_
#define _RANDOM_UTILITIES_H_

#include <cmath>
#include <ctime>
#include <algorithm>


// Seed the random-number generator with current time so that
// the numbers will be different every time we run.
// WARNING:  Only do this once per run!
// The static variable called enforces the one call per run 
// rule.
void randomizeSeed()
{
	static bool called = false;
	if( ! called )
	{
      srand( std::time( NULL ) ) ;
		called = true;
	}
}


// Return a random variate distributed uniformly between
// zero and one.  All doubles in this range are 
// approximately equally likely.
// 0 <= r < 1
double randUniform()
{
   double r = double( rand() ) / ( RAND_MAX + 1.0 );
   r = ( double( rand() ) + r ) / ( RAND_MAX + 1.0 );
   r = ( double( rand() ) + r ) / ( RAND_MAX + 1.0 );
   r = ( double( rand() ) + r ) / ( RAND_MAX + 1.0 );
	return  r;
};


// Return a random variate distributed uniformly on the
// range minReal upto, not including, maxReal.
// minReal is assumed < maxReal.
double randReal( double minReal, double maxReal )
{
	return minReal 
		+ ( maxReal - minReal ) * randUniform();
}


// Return a random variate distributed uniformly on the
// range minInt upto, not including, maxInt.
// minInt is assumed < maxInt.
int randInt( int minInt, int maxInt )
{
	return int( minInt 
		+ ( maxInt - minInt ) * randUniform() );
}


// Return a random variate from the exponential
// distribution with mean one.
double randExpon()
{
	double unif = randUniform();
	double expon = -log( unif );
	return expon;
}


// Return a random variate from the triangle distribution 
// with the minimum, most likely, and maximum values given
// by the three parameters.
double randTriangle( double minimum, double mode, double maximum )
{
   double larger( randUniform() );
   double other( randUniform() );
   if( larger < other )
   {
      larger = other;
   }

	if( randUniform() * ( maximum - minimum ) < ( mode - minimum ) )
	{
		return minimum + larger * ( mode - minimum );
	}
	else
	{
		return maximum + larger * ( mode - maximum );
	}
}


// Return a random variate from the Erlang ( sum of k 
// exponential samples ) distribution.  The mean of the 
// distribution is k.
double randErlang( short k )
{
	double sum = 0.0;
	for( short i=0; i<k; i++ )
	{
		sum += randExpon();
	}
	return sum / double( k );
}

#endif