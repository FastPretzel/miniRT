#include "minirt.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec	vec_mul(t_vec a, double b)
{
	t_vec	ret;

	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return (ret);
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

double	vec_len(t_vec v)
{
	return (fabs(sqrt(v.x * v.x + v.y * v.y + v.z * v.z)));
}

t_vec	vec_norm(t_vec v)
{
	t_vec	ret;
	double	len;

	len = vec_len(v);
	ret.x = v.x / len;
	ret.y = v.y / len;
	ret.z = v.z / len;
	return (ret);
}

t_vec	vec_neg(t_vec v)
{
	t_vec	ret;

	ret.x = -v.x;
	ret.y = -v.y;
	ret.z = -v.z;
	return (ret);
}

t_vec	vec_mat_mul(t_vec v, t_vec rows[3])
{
	t_vec	ret;

	ret.x = v.x * rows[0].x + v.y * rows[1].x + v.z * rows[2].x;
	ret.y = v.x * rows[0].y + v.y * rows[1].y + v.z * rows[2].y;
	ret.z = v.x * rows[0].z + v.y * rows[1].z + v.z * rows[2].z;
	return (ret);
}
