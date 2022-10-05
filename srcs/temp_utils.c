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

void	reset_img(t_minirt *rt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			put_color(rt->mlx, j, i, get_color(0, 0, 0));
	}
}
