#include "minirt.h"

t_color get_color(double r, double g, double b)
{
	t_color	ret;

	ret.r = r / 255.0;
	ret.g = g / 255.0;
	ret.b = b / 255.0;
	return (ret);
}

int	get_int_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	reset_img(t_minirt *minirt)
{
	/*int	size;*/
	int	i;
	int	j;

	/*size = WIDTH * HEIGHT * (minirt->mlx->bits_per_pixel / 8);*/
	/*while (size--)*/
		/*minirt->mlx->addr[size] = 0;*/
	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			my_mlx_pixel_put(minirt->mlx, j, i, get_int_color(20, 20, 60));
	}
}
