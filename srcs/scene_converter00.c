/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_converter00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 14:48:53 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	convert_color(t_color_p *in)
{
	t_color	out;

	out.r = (double) in->r / 255;
	out.g = (double) in->g / 255;
	out.b = (double) in->b / 255;
	return (out);
}

t_alight	*convert_alight(t_alight_p *in)
{
	t_alight	*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_alight));
	if (! out)
		exit_error("Malloc error in convert_alight");
	out->ratio = in->ratio;
	out->color = convert_color(in->color);
	return (out);
}

t_camera	*convert_camera(t_camera_p *in)
{
	t_camera	*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_camera));
	if (! out)
		exit_error("Malloc error in convert_camera");
	out->orig = *(in->orig);
	out->dir = vec_norm(*(in->dir));
	out->right = vec_norm(vec_cross(out->dir, (t_vec){0, 1, 0}));
	out->up = vec_norm(vec_cross(out->right, out->dir));
	out->fov = in->fov;
	return (out);
}

t_light	*convert_light(t_light_p *in)
{
	t_light	*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_light));
	if (! out)
		exit_error("Malloc error in convert_light");
	out->pos = *(in->pos);
	out->intens = in->intens;
	out->color = convert_color(in->color);
	return (out);
}

t_material	convert_material(t_material_p *in)
{
	t_material	out;

	out.color = convert_color(in->color);
	out.albedo[0] = 0.6;
	out.albedo[1] = 0.3;
	out.spec_exp = 50;
	return (out);
}
