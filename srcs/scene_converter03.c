/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_converter03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 15:09:03 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int			get_array_count(void **arr);
t_light		*convert_light(t_light_p *in);
t_object	*convert_object(t_object_p *in);
t_alight	*convert_alight(t_alight_p *in);
t_camera	*convert_camera(t_camera_p *in);

void	convert_lights(t_minirt_p *in, t_minirt *out)
{
	int	i;
	int	arr_size;

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

void	convert_objects(t_minirt_p *in, t_minirt *out)
{
	int	i;
	int	arr_size;

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
	t_minirt	*scene;

	scene_p = parse_scene_p(filename);
	scene = convert_scene(scene_p);
	free_scene_p(scene_p);
	return (scene);
}
