#include "minirt.h"

t_vec	get_norm_plane(t_ray *ray, void *ptr)
{
	t_plane	*pl = (t_plane *)ptr;

	(void)ray;
	/*if (vec_dot(pl->normal, */
	return (vec_norm(pl->normal));
}

int	inter_plane(void *ptr, t_ray *ray)
{
	double	denom;
	t_vec	p0l0;
	t_plane	*pl = (t_plane *)ptr;

	/*t_ray test_ray = {(t_vec){0,0,1}, (t_vec){0,0,2}, 1, {0,0,0}};*/
	if (vec_dot((t_vec){0,0,-1}, pl->normal) < 0)
		pl->normal = vec_neg(pl->normal);
	/*denom = vec_dot(pl->normal, vec_norm(vec_sub(ray->dir, ray->orig)));*/
	denom = vec_dot(pl->normal, ray->dir);
	if ((denom) > DBL_EPSILON)
	{
		p0l0 = vec_norm(vec_sub(pl->orig, ray->orig));
		p0l0 = vec_sub(pl->orig, ray->orig);
		ray->t = vec_dot(p0l0, pl->normal) / denom;
		if (ray->t >= 0)
			return (1);
	}
	return (0);
}	
