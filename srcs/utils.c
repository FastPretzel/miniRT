#include "minirt.h"

double	deg2rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	ft_min_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
