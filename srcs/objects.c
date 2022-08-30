#include "minirt.h"

static void	init_sphere(t_minirt *minirt)
{
	minirt->sp = malloc(sizeof(t_sphere));
	minirt->sp->orig = (t_vec){0, 0, 0};
	minirt->sp->r = 0.2;
	minirt->sp->color = 0xFF0000;
}

void	init_objs(t_minirt *minirt)
{
	init_sphere(minirt);
}
