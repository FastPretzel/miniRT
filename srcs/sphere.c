#include "minirt.h"

t_vec	get_norm_sphere(t_ray ray, void *ptr)
{
	t_vec		normal;
	t_sphere	*sp = (t_sphere *)ptr;

	normal = vec_norm(vec_sub(ray.phit, sp->orig));
	return (normal);
}

int	inter_sphere(void *ptr, t_ray *ray)
{
	t_vec		l;
	double		d2;
	double		t0;
	double		t1;
	double		tca;
	double		thc;
	t_sphere	*sp = (t_sphere *)ptr;

	l = vec_sub(sp->orig, ray->orig);
	tca = vec_dot(ray->dir, l);
	if (tca < 0)
		return (0);
	d2 = vec_dot(l, l) - tca * tca;
	if (d2 > sp->r * sp->r)
		return (0);
	thc = sqrt(sp->r * sp->r - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 < 0 && t1 < 0)
		return (0);
	ray->t = ft_min_double(t0, t1);
	return (1);
}
