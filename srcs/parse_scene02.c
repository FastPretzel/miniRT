/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:07:54 by eclown            #+#    #+#             */
/*   Updated: 2022/09/29 20:03:51 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_p	*create_trgb(int transp, int r, int g, int b);
t_vec	*create_coord(float x, float y, float z);

t_sphere_p	*create_sphere_data(double r, t_vec *orig)
{
	t_sphere_p	*data;

	if (orig == NULL)
		return (NULL);
	data = malloc(sizeof(t_sphere_p));
	if (! data)
		exit_error("malloc error in create_sphere_data");
	data->r = r;
	data->orig = orig;
	return (data);
}

t_plane_p	*create_plane_data(t_vec *vector, t_vec *orig)
{
	t_plane_p	*data;

	data = malloc(sizeof(t_plane_p));
	if (! data)
		exit_error("malloc error in create_plane_data");
	data->normal = vector;
	data->orig = orig;
	return (data);
}

t_cylinder_p	*create_cylinder_data(t_vec *orig,
									  double diam,
									  double h,
									  t_vec *vector)
{
	t_cylinder_p	*data;

	data = malloc(sizeof(t_cylinder_p));
	if (! data)
		exit_error("malloc error in create_cylinder_data");
	data->orig = orig;
	data->d = diam;
	data->dir = vector;
	data->h = h;
	return (data);
}

/* 
str: str with 3 or 4 integers separated by comma
ex: 0,5,100,35
*/
t_color_p	*parse_color(char *str)
{
	t_color_p	*color;
	char	**params;
	int		count;
	int		transp;

	if (str == NULL)
		return (NULL);
	params = ft_split_new(str, ',');
	count = text_len(params);
	if (count > 4 || count < 3 || ! is_all_pos_int(params))
	{
		free_text(params);
		return (NULL);
	}
	transp = 0;
	if (count == 4)
		transp = (int)(unsigned char) ft_atoi(params[0]);
	color = create_trgb(transp, ft_atoi(params[count - 3]),
			ft_atoi(params[count - 2]), ft_atoi(params[count - 1]));
	color->r = (int)(unsigned char) color->r;
	color->g = (int)(unsigned char) color->g;
	color->b = (int)(unsigned char) color->b;
	free_text(params);
	return (color);
}

/* 
str: str with 3 or 4 integers separated by comma
ex: 0.5,5.15,-100,35
*/
t_vec	*parse_coord(char *str)
{
	t_vec	*coord;
	char	**params;
	int		count;

	if (str == NULL)
		return (NULL);
	params = ft_split_new(str, ',');
	count = text_len(params);
	if (count != 3 || ! is_all_float(params))
	{
		free_text(params);
		return (NULL);
	}
	coord = create_coord(ft_atof(params[0]),
			ft_atof(params[1]), ft_atof(params[2]));
	free_text(params);
	return (coord);
}
