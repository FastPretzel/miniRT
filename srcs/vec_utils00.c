/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:29:15 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:29:16 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
