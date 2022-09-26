#include "minirt.h"

t_vec	get_norm_cone(t_ray *ray, void *ptr)
{
	t_vec	normal;
	t_cone	*cone = (t_cone *)ptr;
	t_plane	cap;
	t_ray	cray;

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

static int	intersect_cap(t_cone *cone, t_ray *ray)
{
	t_plane	cap;
	t_ray	cray;

	cray.orig = ray->orig;
	cray.dir = ray->dir;
	cray.t = INFINITY;
	cap.orig = vec_add(cone->orig, vec_mul(cone->dir, cone->h));
	cap.normal = cone->dir;
	if (inter_plane((void *)(&cap), &cray) && 
		vec_len(vec_sub(vec_add(cray.orig, 
		vec_mul(cray.dir, cray.t)), cap.orig)) <= cone->d && cray.t < ray->t)
	{
		ray->t = cray.t;
		return (1);
	}
	return (0);
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
int	inter_cone(void *ptr, t_ray *ray)
{
	t_cone	*cone = (t_cone *)ptr;
	t_vec	w;
	t_vec	v;
	t_vec	h;
	double	m;
	double	a;
	double	b;
	double	c;
	double	dis;
	double	t1;
	double	t2;
	double	t;
	double	alpha;

	if (intersect_cap(cone, ray))
		return (1);
	v = ray->dir;
	h = cone->dir;
	w = vec_sub(ray->orig, cone->orig);
	m = pow(cone->d/2, 2)/pow(vec_len(h),2);
	a = vec_dot(v,v) - m*pow(vec_dot(v,h),2) - pow(vec_dot(v,h),2);
	b = 2*(vec_dot(v,w) - m*vec_dot(v,h)*vec_dot(w,h) - vec_dot(v,h)*vec_dot(w,h));
	c = vec_dot(w,w) - m*pow(vec_dot(w,h),2) - pow(vec_dot(w,h),2);
	dis = b*b - 4*a*c;
	if (dis > 0)
	{
		t1 = (-b - sqrt(dis)) / (2*a);
		t2 = (-b + sqrt(dis)) / (2*a);
		if (t1 < 0 && t2 < 0)
			return (0);
		t = t1;
		if (t < 0)
			t = t2;
		/*return (ray->t = t);*/
		return (reject_sh_cone(cone, ray, t));
	}
	else if (dis == 0)
	{
		alpha = cone->h / (sqrt(pow(cone->h,2)+pow(cone->d/2,2)));
		if (fabs(vec_dot(v,h)) != alpha)
		{
			t = -b/(2*a);
			/*return (ray->t = t);*/
			return (reject_sh_cone(cone, ray, t));
		}
		else
			return (0);
	}
	return (0);
}
