/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:00:26 by eclown            #+#    #+#             */
/*   Updated: 2022/09/29 20:18:26 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*#include "scene_converter.h"*/

int	main(int argc, char **argv)
{
	t_minirt	*scene;
	t_mlx		mlx;

	if (argc != 2)
		return (0);
	scene = parse_scene(argv[1]);
	if (scene == NULL)
		return (1);
	mlx_start(&mlx);
	scene->mlx = &mlx;
	init_keys(scene);
	init_hooks(scene);
	printf("\e[38;5;141mREADY\e[0m\n");
	mlx_loop_hook(mlx.ptr, &render, (void *)scene);
	mlx_loop(mlx.ptr);
	free_scene(scene);
	return (0);
}
