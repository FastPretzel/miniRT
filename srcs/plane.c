#include "minirt.h"

t_vec	get_norm_plane(t_ray *ray, void *ptr)
{
	t_plane	*pl = (t_plane *)ptr;

	(void)ray;
	return (pl->normal);
}

int	inter_plane(void *ptr, t_ray *ray)
{
	double	denom;
	double	t;
	t_vec	p0l0;
	t_plane	*pl = (t_plane *)ptr;

	denom = vec_dot(pl->normal, ray->dir);
	if ((denom) < 1e-4)
	{
		p0l0 = vec_sub(pl->orig, ray->orig);
		t = vec_dot(p0l0, pl->normal) / denom;
		if (t >= 0 && t < ray->t)
			ray->t = t;
		return (t >= 0);
	}
	return (0);
}	
