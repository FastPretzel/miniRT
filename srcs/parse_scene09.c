/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene09.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:14:06 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 17:19:58 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			add_light_to_array(t_light_p ***array, t_light_p *new_light);
t_alight_p		*parse_alight(char *str);
t_light_p		*parse_light(char *str);
t_camera_p		*parse_camera(char *str);

int	parse_error(int line_num, char *str)
{
	char	*line_num_str;

	ft_putstr_fd("Parsing error in line ", 2);
	line_num_str = ft_itoa(line_num);
	if (line_num_str == NULL)
		exit_error("malloc error in parse_error");
	ft_putstr_fd(line_num_str, 2);
	free(line_num_str);
	ft_putstr_fd(". ", 2);
	ft_putstr_fd(str, 2);
	return (1);
}

int	add_alight_to_scene(t_minirt_p *scene, char *str, int line_num)
{
	if (scene->alight)
		return (parse_error(line_num, "There is second \
		ambient light in scene."));
	scene->alight = parse_alight(str);
	if (scene->alight == NULL)
		return (parse_error(line_num, "Ambient light parse error"));
	return (0);
}

int	get_light_count(t_light_p	**lights)
{
	int	i;

	if (lights == NULL)
		return (0);
	i = 0;
	while (lights[i])
		i++;
	return (i);
}

int	add_light_to_scene(t_minirt_p *scene, char *str, int line_num)
{
	int	lights_count;

	lights_count = get_light_count(scene->lights);
	if (IS_BONUS_PART == 0 && lights_count > 0)
		return (parse_error(line_num, "There is second light in scene."));
	add_light_to_array(&(scene->lights), parse_light(str));
	if (lights_count == get_light_count(scene->lights))
		return (parse_error(line_num, "Light parse error"));
	return (0);
}

int	add_camera_to_scene(t_minirt_p *scene, char *str, int line_num)
{
	if (scene->camera)
	{
		free(str);
		return (parse_error(line_num, "There is second camera in scene."));
	}
	scene->camera = parse_camera(str);
	if (scene->camera == NULL)
		return (parse_error(line_num, "Camera parse error"));
	return (0);
}
