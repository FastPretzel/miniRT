#include "minirt.h"

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
	/*if (t0 < 0 && t1 < 0)*/
		/*return (0);*/
	if (t0 < 1e-4 || t0 > ray->t)
	{
		t0 = t1;
		if (t0 < 1e-4 || t0 > ray->t)
			return (0);
	}
	/*ray->t = ft_min_double(t0, t1);*/
	ray->t = t0;
	return (1);
}

/*int	inter_sphere(void *ptr, t_ray *ray)*/
/*{*/
	/*t_sphere *sp = (t_sphere *)ptr;*/
	/*t_vec oc = vec_sub(ray->orig, sp->orig);*/
	/*double a = vec_dot(ray->dir, ray->dir);*/
	/*double b = 2.0 * vec_dot(oc, ray->dir);*/
	/*double c = vec_dot(oc, oc) - sp->r * sp->r;*/
	/*double discr = b*b - 4*a*c;*/
	/*if (discr < 0)*/
		/*return (0);*/
	/*ray->t = (-b - sqrt(discr))/(2.0*a);*/
	/*return (1);*/
/*}*/
