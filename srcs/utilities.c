
#include "utilities.h"

double		absdiv(double a, double b)
{
	double c;

	c = a - b;
	return (c < 0 ? -c : c);
}
