/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:51:29 by eclown            #+#    #+#             */
/*   Updated: 2022/09/24 19:11:57 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_light_count(t_light_p	**lights);

t_alight_p	*create_alight(float ratio, t_color *color)
{
	t_alight_p	*alight;

	alight = malloc(sizeof(t_alight_p));
	if (! alight)
		exit_error("malloc error in create_alight");
	alight->ratio = ratio;
	alight->color = color;
	return (alight);
}

t_vec	*create_coord(float x, float y, float z)
{
	t_vec	*coord;

	coord = malloc(sizeof(t_vec));
	if (! coord)
		exit_error("malloc error in create_coord");
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

t_color	*create_trgb(int transp, int r, int g, int b)
{
	t_color	*rgb;

	rgb = malloc(sizeof(t_color));
	if (! rgb)
		exit_error("malloc error in create_trgb");
	rgb->transp = transp;
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	return (rgb);
}

void	add_light_to_array(t_light_p ***array, t_light_p *new_light)
{
	t_light_p	**new_array;
	t_light_p	**old_array;
	int		i;

	old_array = *array;
	i = get_light_count(old_array);
	new_array = malloc(sizeof(t_light_p *) * (i + 2));
	if (! new_array)
		exit_error("malloc error in add_light_to_array");
	i = 0;
	while (old_array && old_array[i])
	{
		new_array[i] = old_array[i];
		i++;
	}
	new_array[i++] = new_light;
	new_array[i] = NULL;
	if (old_array != NULL)
		free(old_array);
	*array = new_array;
}

t_light_p	*create_light(t_vec *point, float brightness, t_color *color)
{
	t_light_p	*light;

	light = malloc(sizeof(t_light_p));
	if (! light)
		exit_error("malloc error in create_light");
	light->pos = point;
	light->intens = brightness;
	if (color != NULL)
		light->color = color;
	else
		light->color = NULL;
	return (light);
}
