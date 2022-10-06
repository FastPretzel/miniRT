/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:28:18 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:28:19 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_start(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, \
			&mlx->line_length, &mlx->endian);
}

int	cross_exit(t_minirt *minirt)
{
	mlx_destroy_window(minirt->mlx->ptr, minirt->mlx->win);
	printf("\e[38;5;202mEXIT\e[0m\n");
	exit(0);
}

void	init_hooks(t_minirt *rt)
{
	mlx_hook(rt->mlx->win, 17, 0, cross_exit, rt);
	mlx_hook(rt->mlx->win, 2, 0, key_down, rt->keys);
	mlx_hook(rt->mlx->win, 3, 0, key_up, rt->keys);
}
