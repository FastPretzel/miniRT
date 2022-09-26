#include "minirt.h"

int	main()
{
	t_mlx		mlx;
	t_minirt	minirt;

	mlx_start(&mlx);
	minirt.mlx = &mlx;
	minirt.obj_lst = 0;
	minirt.light_lst = 0;
	init_keys(&minirt);
	init_hooks(&minirt);
	init_camera(&minirt);
	init_objs(&minirt);
	init_light(&minirt);
	printf("\e[38;5;141mREADY\e[0m\n");
	mlx_loop_hook(mlx.ptr, &render, (void *)&minirt);
	mlx_loop(mlx.ptr);
	return (0);
}
