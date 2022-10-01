#include "minirt.h"

static void	qtr_mul(t_qtr *q, t_qtr *p, t_qtr *res)
{
	res->r = q->r*p->r - q->x*p->x - q->y*p->y - q->z*p->z;
	res->x = q->r*p->x + q->x*p->r - q->y*p->z + q->z*p->y;
	res->y = q->r*p->y + q->x*p->z + q->y*p->r - q->z*p->x;
	res->z = q->r*p->z - q->x*p->y + q->y*p->x + q->z*p->r;
}

static void	rotate_xyz(t_minirt *rt, t_vec *axis, t_vec *p1, t_vec *p2)
{
	t_qtr	q;
	t_qtr	q_neg;
	t_qtr	res;
	t_qtr	pos;
	double	deg;

	deg = degree(rt->keys);
	q.x = sin(deg)*axis->x;
	q.y = sin(deg)*axis->y;
	q.z = sin(deg)*axis->z;
	q.r = cos(deg);
	neg_qtr(&q, &q_neg);
	qtr_mul(&q, vec2qtr(p1), &res);
	qtr_mul(&res, &q_neg, &pos);
	update_vec(&pos, p1);
	qtr_mul(&q, vec2qtr(p2), &res);
	qtr_mul(&res, &q_neg, &pos);
	update_vec(&pos, p2);
}

void	rotate(t_minirt *rt)
{
	if (rt->keys->key_w || rt->keys->key_s)
	{
		rotate_xyz(rt, &(rt->camera->right), &(rt->camera->up), &(rt->camera->dir));
		rt->keys->key_w = 0;
		rt->keys->key_s = 0;
	}
	if (rt->keys->key_a || rt->keys->key_d)
	{
		rotate_xyz(rt, &(rt->camera->up), &(rt->camera->right), &(rt->camera->dir));
		rt->keys->key_a = 0;
		rt->keys->key_d = 0;
	}
	if (rt->keys->key_q || rt->keys->key_e)
	{
		rotate_xyz(rt, &(rt->camera->dir), &(rt->camera->up), &(rt->camera->right));
		rt->keys->key_q = 0;
		rt->keys->key_e = 0;
	}
}
