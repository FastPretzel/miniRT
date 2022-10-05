#include "minirt.h"

t_vec	get_norm_cone(t_ray *ray, void *ptr)
{
	t_vec	normal;
	t_cone	*cone;
	t_plane	cap;
	t_ray	cray;

	cone = (t_cone *)ptr;
	cray.orig = cone->orig;
	cray.dir = cone->dir;
	cray.t = INFINITY;
	cap.orig = ray->phit;
	cap.normal = vec_neg(cone->dir);
	if (inter_plane(((void *)&cap), &cray) && fabs(cray.t - cone->h) < 1e-5)
		return (cone->dir);
	normal = vec_cross(vec_cross(cone->dir, vec_sub(ray->phit,
					cone->orig)), vec_sub(ray->phit, cone->orig));
	normal = vec_norm(normal);
	return (normal);
}

int	reject_sh_cone(t_cone *cone, t_ray *ray, double t)
{
	t_vec	p;
	double	hp;

	p = vec_add(ray->orig, vec_mul(ray->dir, t));
	hp = vec_dot(vec_sub(p, cone->orig), cone->dir);
	if (hp > 0 && hp <= cone->h)
		return (ray->t = t);
	return (0);
}

int	intersect_cap(t_cone *cone, t_ray *ray)
{
	t_plane	cap;
	t_ray	cray;

	cray.orig = ray->orig;
	cray.dir = ray->dir;
	cray.t = INFINITY;
	cap.orig = vec_add(cone->orig, vec_mul(cone->dir, cone->h));
	cap.normal = cone->dir;
	if (inter_plane((void *)(&cap), &cray) && \
		vec_len(vec_sub(vec_add(cray.orig,
		vec_mul(cray.dir, cray.t)), cap.orig)) <= cone->d && cray.t < ray->t)
	{
		ray->t = cray.t;
		return (1);
	}
	return (0);
}
