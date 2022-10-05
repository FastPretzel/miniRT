/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_converter02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 14:50:33 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere	*convert_sphere(t_sphere_p *in)
{
	t_sphere	*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_sphere));
	if (! out)
		exit_error("Malloc error in convert_sphere");
	out->orig = *(in->orig);
	out->r = in->r;
	return (out);
}

t_plane	*convert_plane(t_plane_p *in)
{
	t_plane	*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_plane));
	if (! out)
		exit_error("Malloc error in convert_plane");
	out->orig = *(in->orig);
	out->normal = *(in->normal);
	return (out);
}

t_cylinder	*convert_cylinder(t_cylinder_p *in)
{
	t_cylinder	*out;

	out = ft_calloc(1, sizeof(t_cylinder));
	if (! out)
		exit_error("Malloc error in convert_cylinder");
	out->orig = *(in->orig);
	out->dir = *(in->dir);
	out->d = in->d;
	out->h = in->h;
	return (out);
}

t_cone	*convert_cone(t_cone_p *in)
{
	t_cylinder	*out;

	out = ft_calloc(1, sizeof(t_cone));
	if (! out)
		exit_error("Malloc error in convert_cone");
	out->orig = *(in->orig);
	out->dir = *(in->dir);
	out->d = in->d;
	out->h = in->h;
	return (out);
}

int	get_array_count(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
