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

static void	fill_vars(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->v = ray->dir;
	q->h = cone->dir;
	q->w = vec_sub(ray->orig, cone->orig);
	q->m = pow(cone->d / 2, 2) / pow(vec_len(q->h), 2);
	q->a = vec_dot(q->v, q->v) - q->m * pow(vec_dot(q->v, q->h), 2) - \
		pow(vec_dot(q->v, q->h), 2);
	q->b = 2 * (vec_dot(q->v, q->w) - q->m * vec_dot(q->v, q->h) * \
			vec_dot(q->w, q->h) - vec_dot(q->v, q->h) * vec_dot(q->w, q->h));
	q->c = vec_dot(q->w, q->w) - q->m * pow(vec_dot(q->w, q->h), 2) - \
		pow(vec_dot(q->w, q->h), 2);
	q->dis = q->b * q->b - 4 * q->a * q->c;
}

static int	solver2(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->t1 = (-q->b - sqrt(q->dis)) / (2 * q->a);
	q->t2 = (-q->b + sqrt(q->dis)) / (2 * q->a);
	if (q->t1 < 0 && q->t2 < 0)
		return (0);
	q->t = q->t1;
	if (q->t < 0)
		q->t = q->t2;
	return (reject_sh_cone(cone, ray, q->t));
}

static int	solver1(t_quad *q, t_cone *cone, t_ray *ray)
{
	q->alpha = cone->h / (sqrt(pow(cone->h, 2) + pow(cone->d / 2, 2)));
	if (fabs(vec_dot(q->v, q->h)) != q->alpha)
	{
		q->t = -q->b / (2 * q->a);
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
