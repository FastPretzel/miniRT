/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:29:12 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:29:13 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
