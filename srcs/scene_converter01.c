/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_converter01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 14:49:15 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_material	convert_material(t_material_p *in);
void		free_material(t_material_p *mat);
t_sphere	*convert_sphere(t_sphere_p *in);
t_plane		*convert_plane(t_plane_p *in);
t_cylinder	*convert_cylinder(t_cylinder_p *in);
t_cone		*convert_cone(t_cone_p *in);

void	convert_object_sp(t_object_p *in, t_object *out)
{
		out->params = convert_sphere((t_sphere_p *) in->params);
		out->intersect = inter_sphere;
		out->get_normal = get_norm_sphere;
}

void	convert_object_pl(t_object_p *in, t_object *out)
{
		out->params = convert_plane((t_plane_p *) in->params);
		out->intersect = inter_plane;
		out->get_normal = get_norm_plane;
}

void	convert_object_cl(t_object_p *in, t_object *out)
{
		out->params = convert_cylinder((t_cylinder_p *) in->params);
		out->intersect = inter_cylinder;
		out->get_normal = get_norm_cylinder;
}

void	convert_object_cn(t_object_p *in, t_object *out)
{
		out->params = convert_cone((t_cone_p *) in ->params);
		out->intersect = inter_cone;
		out->get_normal = get_norm_cone;
}

t_object	*convert_object(t_object_p *in)
{
	t_object		*out;

	if (! in)
		return (NULL);
	out = ft_calloc(1, sizeof(t_object));
	if (! out)
		exit_error("Malloc error in convert_object");
	out->type = in->type;
	if (in->type == SPHERE)
		convert_object_sp(in, out);
	else if (in->type == PLANE)
		convert_object_pl(in, out);
	else if (in->type == CYLINDER)
		convert_object_cl(in, out);
	else
		convert_object_cn(in, out);
	out->mat = convert_material(in->mat);
	return (out);
}
