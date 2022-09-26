#include "minirt.h"

/*void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)*/
/*{*/
	/*char	*dst;*/

	/*if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))*/
	/*{*/
		/*dst = mlx->addr + (y * mlx->line_length + \*/
				/*x * (mlx->bits_per_pixel / 8));*/
		/**(unsigned int *)dst = color;*/
	/*}*/
/*}*/

void	mlx_start(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "minirt");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
			&mlx->line_length, &mlx->endian);
}

int	cross_exit(t_minirt *minirt)
{
	mlx_destroy_window(minirt->mlx->ptr, minirt->mlx->win);
	exit(0);
}

void	init_hooks(t_minirt *rt)
{
	mlx_hook(rt->mlx->win, 17, 0, cross_exit, rt);
	mlx_hook(rt->mlx->win, 2, 0, key_down, rt->keys);
	/*mlx_hook(rt->mlx->win, 3, 0, key_up, rt->keys);*/
}
