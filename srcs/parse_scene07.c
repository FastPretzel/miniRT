/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene07.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:43:14 by eclown            #+#    #+#             */
/*   Updated: 2022/09/26 18:48:48 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_t_plane_data(t_plane_p *data);
void	free_t_cylinder_data(t_cylinder_p *data);
void	free_object(t_object_p *object);

void	free_alight(t_alight_p *alight)
{
	if (! alight)
		return ;
	if (alight->color)
		free(alight->color);
	free(alight);
}

void	free_camera(t_camera_p *camera)
{
	if (! camera)
		return ;
	if (camera->orig)
		free(camera->orig);
	if (camera->dir)
		free(camera->dir);
	free(camera);
}

void	free_light_array_p(t_light_p **light_array)
{
	int	i;

	if (! light_array)
		return ;
	i = 0;
	while (light_array[i])
	{
		if (! light_array[i])
			return ;
		if (light_array[i]->color)
			free(light_array[i]->color);
		if (light_array[i]->pos)
			free(light_array[i]->pos);
		free(light_array[i]);
		i++;
	}
	free(light_array);
}

void	free_object_array_p(t_object_p **object_array)
{
	int	i;

	if (! object_array)
		return ;
	i = 0;
	while (object_array[i])
		free_object(object_array[i++]);
	free(object_array);
}

void	free_scene_p(t_minirt_p *scene)
{
	if (! scene)
		return ;
	if (scene->description)
		free(scene->description);
	if (scene->alight)
		free_alight(scene->alight);
	if (scene->camera)
		free_camera(scene->camera);
	if (scene->lights)
		free_light_array_p(scene->lights);
	if (scene->objects)
		free_object_array_p(scene->objects);
	free(scene);
}
