/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:29:19 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:29:20 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	deg2rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	ft_min_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

void	reset_img(t_minirt *rt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			put_color(rt->mlx, j, i, (t_color){0, 0, 0});
	}
}
