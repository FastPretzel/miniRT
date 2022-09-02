#include "minirt.h"

int	inter_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec		l;
	double		d2;
	double		t0;
	double		t1;
	double		tca;
	double		thc;

	l = vec_sub(sp->orig, ray->orig);
	tca = vec_dot(ray->dir, l);
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
