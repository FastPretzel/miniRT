/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:45:06 by eclown            #+#    #+#             */
/*   Updated: 2022/09/24 19:11:57 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*parse_color(char *str);
t_vec	*parse_coord(char *str);
t_light_p	*create_light(t_vec *point, float brightness, t_color *color);

int	check_light_args(char **args)
{
	t_color	*color;
	t_vec	*coord;
	float	ratio;
	int		args_count;

	args_count = text_len(args);
	if (args_count != 3 && args_count != 4)
		return (0);
	if (! ft_is_float(args[2]))
		return (0);
	ratio = ft_atof(args[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	coord = parse_coord(args[1]);
	if (coord == NULL)
		return (0);
	free(coord);
	if (args_count == 3)
		return (1);
	color = parse_color(args[3]);
	if (color == NULL)
		return (0);
	free(color);
	return (1);
}

t_light_p	*parse_light(char *str)
{
	char	**bloks;
	t_light_p	*light;
	t_color	*color;

	str = ft_strdup(str);
	replace_space_chars_to_space(str);
	bloks = ft_split_new(str, ' ');
	if (check_light_args(bloks) == 0)
	{
		free_text(bloks);
		free(str);
		return (file_format_error("Light wrong args"));
	}
	if (text_len(bloks) == 4)
		color = parse_color(bloks[3]);
	else
		color = NULL;
	light = create_light(
			parse_coord(bloks[1]),
			ft_atod(bloks[2]),
			color);
	free_text(bloks);
	free(str);
	return (light);
}

int	check_norm_vector(t_vec *vector)
{
	if (vector->x < -1 || vector->x > 1)
		return (0);
	if (vector->y < -1 || vector->y > 1)
		return (0);
	if (vector->z < -1 || vector->z > 1)
		return (0);
	return (1);
}

void	*error_open_file(char *filename)
{
	ft_putstr_fd("Error open file or file format is wrong: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
