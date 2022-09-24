#include "minirt.h"

void	put_color(t_mlx *mlx, int x, int y, t_color color)
{
	/*t_color	color;*/

	/*color = rt->nearest->get_color(rt->nearest->params);*/
	/*color = apply_lights(rt, color);*/
	mlx->addr[x * (mlx->bits_per_pixel >> 3) + y *
		mlx->line_length] = (char)(color.b * 255);
	mlx->addr[x * (mlx->bits_per_pixel >> 3) + y *
		mlx->line_length + 1] = (char)(color.g * 255);
	mlx->addr[x * (mlx->bits_per_pixel >> 3) + y *
		mlx->line_length + 2] = (char)(color.r * 255);
}

t_color	col_mul(t_color a, double c)
{
	t_color	ret;

	ret.r = a.r * c;
	ret.g = a.g * c;
	ret.b = a.b * c;
	return (ret);
}

t_color	col_mul_vec(t_color a, t_color b)
{
	t_color	ret;

	ret.r = a.r * b.r;
	ret.g = a.g * b.g;
	ret.b = a.b * b.b;
	return (ret);
}

t_color	col_add(t_color a, t_color b)
{
	t_color	ret;

	ret.r = fmin(1.0, a.r + b.r);
	ret.g = fmin(1.0, a.g + b.g);
	ret.b = fmin(1.0, a.b + b.b);
	return (ret);
}
