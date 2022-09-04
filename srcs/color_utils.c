#include "minirt.h"

/*void	put_color(t_minirt *rt, t_img img, int x, int y)*/
/*{*/
	/*t_color	color;*/

	/*color = rt->nearest->get_color(rt->nearest->params);*/
	/*color = apply_lights(rt, color);*/
	/*img.data[x * (img.bpp >> 3) + y **/
		/*img.size_line] = (char)(color.b * 255);*/
	/*img.data[x * (img.bpp >> 3) + y **/
		/*img.size_line + 1] = (char)(color.g * 255);*/
	/*img.data[x * (img.bpp >> 3) + y **/
		/*img.size_line + 2] = (char)(color.r * 255);*/
/*}*/
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
