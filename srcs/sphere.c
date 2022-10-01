#include "minirt.h"

typedef struct	s_quad
{
	double	d2;
	double	t0;
	double	t1;
	double	tca;
	double	thc;
}	t_quad;

t_vec	get_norm_sphere(t_ray *ray, void *ptr)
{
	t_vec		normal;
	t_sphere	*sp = (t_sphere *)ptr;

	normal = vec_norm(vec_sub(ray->phit, sp->orig));
	return (normal);
}

int	inter_sphere(void *ptr, t_ray *ray)
{
	t_vec		l;
	t_quad		q;
	t_sphere	*sp = (t_sphere *)ptr;

	l = vec_sub(sp->orig, ray->orig);
	q.tca = vec_dot(ray->dir, l);
	if (q.tca < 0)
		return (0);
	q.d2 = vec_dot(l, l) - q.tca * q.tca;
	if (q.d2 > sp->r * sp->r)
		return (0);
	q.thc = sqrt(sp->r * sp->r - q.d2);
	q.t0 = q.tca - q.thc;
	q.t1 = q.tca + q.thc;
	if (q.t0 < 1e-4 || q.t0 > ray->t)
	{
		q.t0 = q.t1;
		if (q.t0 < 1e-4 || q.t0 > ray->t)
			return (0);
	}
	ray->t = q.t0;
	return (1);
}
