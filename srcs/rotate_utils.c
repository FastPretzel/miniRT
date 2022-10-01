#include "minirt.h"

void	neg_qtr(t_qtr *q, t_qtr *q_neg)
{
	q_neg->x = -q->x;
	q_neg->y = -q->y;
	q_neg->z = -q->z;
	q_neg->r = q->r;
}

t_qtr	*vec2qtr(t_vec *p)
{
	t_qtr	*res;
	t_qtr	q;

	q.x = p->x;
	q.y = p->y;
	q.z = p->z;
	q.r = 0;
	res = &q;
	return (res);
}

void	update_vec(t_qtr *pos, t_vec *p)
{
	p->x = pos->x;
	p->y = pos->y;
	p->z = pos->z;
}

double	degree(t_keys *keys)
{
	double	deg;

	deg = 0;
	if (keys->key_s)
		deg = deg2rad(DGR_DELTA/2);
	else if (keys->key_w)
		deg = deg2rad(-DGR_DELTA/2);
	if (keys->key_a)
		deg = deg2rad(DGR_DELTA/2);
	else if (keys->key_d)
		deg = deg2rad(-DGR_DELTA/2);
	if (keys->key_q)
		deg = deg2rad(DGR_DELTA/2);
	else if (keys->key_e)
		deg = deg2rad(-DGR_DELTA/2);
	return (deg);
}
