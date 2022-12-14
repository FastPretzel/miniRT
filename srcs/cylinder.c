/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:26:57 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:26:58 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_quad
{
	t_vec	cx;
	t_vec	cy;
	double	t;
	double	a;
	double	b;
	double	c;
	double	x1;
	double	x2;
	double	det;
}	t_quad;

static int	check_height(t_cylinder *cy, t_vec p)
{
	t_ray	cray;
	t_plane	cap;

	cray.orig = cy->orig;
	cray.dir = cy->dir;
	cray.t = INFINITY;
	cap.orig = p;
	cap.normal = vec_neg(cy->dir);
	inter_plane((void *)(&cap), &cray);
	if (cray.t <= cy->h / 2)
		return (1);
	cray.dir = vec_neg(cy->dir);
	cray.t = INFINITY;
	cap.normal = cy->dir;
	inter_plane((void *)(&cap), &cray);
	if (cray.t <= cy->h / 2)
		return (1);
	return (0);
}

static int	intersect_caps(t_cylinder *cy, t_ray *ray)
{
	t_plane	cap;
	t_ray	cray;

	cray.orig = ray->orig;
	cray.dir = ray->dir;
	cray.t = INFINITY;
	cap.orig = vec_add(cy->orig, vec_mul(cy->dir, cy->h / 2));
	cap.normal = cy->dir;
	if (inter_plane((void *)(&cap), &cray) &&
		vec_len(vec_sub(vec_add(cray.orig,
		vec_mul(cray.dir, cray.t)), cap.orig)) <= cy->d / 2 && cray.t < ray->t)
	{
		ray->t = cray.t;
		return (1);
	}
	cap.orig = vec_sub(cy->orig, vec_mul(cy->dir, cy->h / 2));
	cap.normal = vec_neg(cy->dir);
	if (inter_plane((void *)(&cap), &cray) &&
		vec_len(vec_sub(vec_add(cray.orig,
		vec_mul(cray.dir, cray.t)), cap.orig)) <= cy->d / 2 && cray.t < ray->t)
	{
		ray->t = cray.t;
		return (1);
	}
	return (0);
}

t_vec	get_norm_cylinder(t_ray *ray, void *ptr)
{
	t_vec		po;
	t_plane		cap;
	t_ray		cray;
	t_cylinder	*cy;

	cy = (t_cylinder *)ptr;
	cray.orig = cy->orig;
	cray.dir = cy->dir;
	cray.t = INFINITY;
	cap.orig = ray->phit;
	cap.normal = vec_neg(cy->dir);
	if (inter_plane(((void *)&cap), &cray) && fabs(cray.t - cy->h / 2) < 1e-5)
		return (cy->dir);
	cray.dir = vec_neg(cy->dir);
	cray.t = INFINITY;
	cap.normal = cy->dir;
	if (inter_plane(((void *)&cap), &cray) && fabs(cray.t - cy->h / 2) < 1e-5)
		return (vec_neg(cy->dir));
	po = vec_sub(ray->phit, cy->orig);
	return (vec_norm(vec_sub(po, vec_mul(cy->dir, vec_dot(cy->dir, po)))));
}

static void	fill_quad(t_quad *q, t_cylinder *cyl, t_ray *ray)
{
	q->cx = vec_cross(ray->dir, cyl->dir);
	q->cy = vec_cross(cyl->dir, vec_sub(cyl->orig, ray->orig));
	q->a = vec_dot(q->cx, q->cx);
	q->b = 2 * vec_dot(q->cx, q->cy);
	q->c = vec_dot(q->cy, q->cy) - (pow(cyl->d / 2, 2) * \
			vec_dot(cyl->dir, cyl->dir));
	q->det = pow(q->b, 2) - 4 * q->a * q->c;
}

int	inter_cylinder(void *ptr, t_ray *ray)
{
	t_cylinder	*cyl;
	t_quad		q;

	cyl = (t_cylinder *)ptr;
	if (intersect_caps(cyl, ray))
		return (1);
	fill_quad(&q, cyl, ray);
	if (q.det < 0)
		return (0);
	q.det = sqrt(q.det);
	q.x1 = (-q.b + q.det) / (2 * q.a);
	q.x2 = (-q.b - q.det) / (2 * q.a);
	if (q.x1 < 0 && q.x2 < 0)
		return (0);
	q.t = q.x2;
	if (q.t < 0)
		q.t = q.x1;
	if (check_height(cyl, vec_add(ray->orig, vec_mul(ray->dir,
					q.t))) && q.t < ray->t)
	{
		ray->t = q.t;
		return (1);
	}
	return (0);
}
