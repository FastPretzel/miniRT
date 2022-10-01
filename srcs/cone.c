#include "minirt.h"

typedef struct s_quad
{
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
}	t_quad;

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

static int	reject_sh_cone(t_cone *cone, t_ray *ray, double t)
{
	t_vec	p;
	double	hp;

	p = vec_add(ray->orig, vec_mul(ray->dir, t));
	hp = vec_dot(vec_sub(p, cone->orig), cone->dir);
	if (hp > 0 && hp <= cone->h)
		return (ray->t = t);
	return (0);
}

static void	fill_vars(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->v = ray->dir;
	q->h = cone->dir;
	q->w = vec_sub(ray->orig, cone->orig);
	q->m = pow(cone->d/2, 2)/pow(vec_len(q->h),2);
	q->a = vec_dot(q->v,q->v) - q->m*pow(vec_dot(q->v,q->h),2) -
		pow(vec_dot(q->v,q->h),2);
	q->b = 2*(vec_dot(q->v,q->w) - q->m*vec_dot(q->v,q->h)*vec_dot(q->w,q->h) -
			vec_dot(q->v,q->h)*vec_dot(q->w,q->h));
	q->c = vec_dot(q->w,q->w) - q->m*pow(vec_dot(q->w,q->h),2) -
		pow(vec_dot(q->w,q->h),2);
	q->dis = q->b*q->b - 4*q->a*q->c;
}

static int	solver2(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->t1 = (-q->b - sqrt(q->dis)) / (2*q->a);
	q->t2 = (-q->b + sqrt(q->dis)) / (2*q->a);
	if (q->t1 < 0 && q->t2 < 0)
		return (0);
	q->t = q->t1;
	if (q->t < 0)
		q->t = q->t2;
	return (reject_sh_cone(cone, ray, q->t));
}

static int	solver1(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->alpha = cone->h / (sqrt(pow(cone->h,2)+pow(cone->d/2,2)));
	if (fabs(vec_dot(q->v,q->h)) != q->alpha)
	{
		q->t = -q->b/(2*q->a);
		return (reject_sh_cone(cone, ray, q->t));
	}
	else
		return (0);
}

int	inter_cone(void *ptr, t_ray *ray)
{
	t_cone	*cone;
	t_quad	q;

	cone = (t_cone *)ptr;
	if (intersect_cap(cone, ray))
		return (1);
	fill_vars(&q, cone, ray);
	if (q.dis > 0)
		return (solver2(&q, cone, ray));
	else if (q.dis == 0)
		return (solver1(&q, cone, ray));
	return (0);
}
