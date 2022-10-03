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


void	free_light_array(t_light **light_array)
{
	int	i;

	if (! light_array)
		return ;
	i = 0;
	while (light_array[i])
	{
		free(light_array[i]);
		i++;
	}
	free(light_array);
}

void	free_object_array(t_object **object_array)
{
	int	i;

	if (! object_array)
		return ;
	i = 0;
	while (object_array[i])
	{
		free(object_array[i]->params);
		free(object_array[i++]);
	}
	free(object_array);
}

void	free_scene(t_minirt *scene)
{
	if (! scene)
		return ;
	if (scene->description)
		free(scene->description);
	if (scene->alight)
		free(scene->alight);
	if (scene->camera)
		free(scene->camera);
	if (scene->lights)
		free_light_array(scene->lights);
	if (scene->objects)
		free_object_array(scene->objects);
	free(scene);
}
