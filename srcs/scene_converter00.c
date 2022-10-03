/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene10.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 17:33:32 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "scene_converter.h"*/
#include "minirt.h"

t_alight	*convert_alight(t_alight_p *in)
{
	t_alight *out;

	if (! in)
		return NULL;
	out = ft_calloc(1, sizeof(t_alight));
	if (! out)
		exit_error("Malloc error in convert_alight");
	out->ratio = in->ratio;
	out->color = *(in->color);
	return (out);
}

t_camera	*convert_camera(t_camera_p *in)
{
	t_camera	*out;

	if (! in)
		return NULL;
	out = ft_calloc(1, sizeof(t_camera));
	if (! out)
		exit_error("Malloc error in convert_camera");
	out->orig = *(in->orig);
	out->dir = *(in->dir);
	return (out);
}

t_light	*convert_light(t_light_p *in)
{
	t_light	*out;

	if (! in)
		return NULL;
	out = ft_calloc(1, sizeof(t_light));
	if (! out)
		exit_error("Malloc error in convert_light");
	out->pos = *(in->pos);
	out->intens = in->intens;
	out->color = *(in->color);
	return (out);
}

t_material	convert_material(t_material_p *in)
{
	t_material	out;

	out.color = *(in->color);
	out.albedo[0] = in->albedo[0];
	out.albedo[1] = in->albedo[1];
	out.albedo[2] = in->albedo[2];
	return (out);
}

//TODO MOVE
void	free_material(t_material_p *mat);
t_sphere	*convert_sphere(t_sphere_p *in);
t_plane	*convert_plane(t_plane_p *in);
t_cylinder	*convert_cylinder(t_cylinder_p *in);

t_object	*convert_object(t_object_p *in)
{
	t_object		*out;

	if (! in)
		return NULL;
	out = ft_calloc(1, sizeof(t_object));
	if (! out)
		exit_error("Malloc error in convert_object");
	out->type = in->type;
	if (in->type == SPHERE)
	{
		out->params = convert_sphere((t_sphere_p *) in->params);
		out->intersect = inter_sphere;
		out->get_normal = get_norm_sphere;
	}
	else if (in->type == PLANE)
	{
		out->params = convert_plane((t_plane_p *) in->params);
		out->intersect = inter_plane;
		out->get_normal = get_norm_plane;
	}
	else if (in->type == CYLINDER)
	{
		out->params = convert_cylinder((t_cylinder_p *) in->params);
		out->intersect = inter_cylinder;
		out->get_normal = get_norm_cylinder;
	}
	out->mat = convert_material(in->mat);
	return (out);
}

t_sphere	*convert_sphere(t_sphere_p *in)
{
	t_sphere	*out;

	if (! in)
		return NULL;
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
		return NULL;
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

int	get_array_count(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void convert_lights(t_minirt_p *in, t_minirt *out)
{
	int	i;
	int arr_size;

	i = 0;
	arr_size = get_array_count((void *)in->lights);
	if (arr_size == 0)
		return ;
	out->lights = ft_calloc(arr_size + 1, sizeof(t_light *));
	while (in->lights[i])
	{
		out->lights[i] = convert_light(in->lights[i]);
		i++;
	}
}

void convert_objects(t_minirt_p *in, t_minirt *out)
{
	int	i;
	int arr_size;

	i = 0;
	arr_size = get_array_count((void *)in->objects);
	if (arr_size == 0)
		return ;
	out->objects = ft_calloc(arr_size + 1, sizeof(t_object *));
	while (in->objects[i])
	{
		out->objects[i] = convert_object(in->objects[i]);
		i++;
	}
}

t_minirt	*convert_scene(t_minirt_p *in)
{
	t_minirt	*out;

	out = ft_calloc(1, sizeof(t_minirt));
	if (! out)
		exit_error("Malloc error in convert_scene");
	out->description = ft_strdup(in->description);
	out->alight = convert_alight(in->alight);
	out->camera = convert_camera(in->camera);
	convert_lights(in, out);
	convert_objects(in, out);
	return (out);
}

t_minirt	*parse_scene(char *filename)
{
	t_minirt_p	*scene_p;
	t_minirt 	*scene;

	scene_p = parse_scene_p(filename);
	scene = convert_scene(scene_p);
	free_scene_p(scene_p);
	return (scene);
}
