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

/*void	matr_mult(double a[4][1], double b[4][1], double res[4][1])*/
/*{*/
	/*int	i;*/
	/*int	j;*/
	/*int	k;*/

	/*i = -1;*/
	/*while (++i < 4)*/
	/*{*/
		/*j = -1;*/
		/*while (++j < 1)*/
		/*{*/
			/*res[i][j] = 0;*/
			/*k = -1;*/
			/*while (++k < 1)*/
				/*res[i][j] += a[i][k] * b[k][j];*/
		/*}*/
	/*}*/
/*}*/
