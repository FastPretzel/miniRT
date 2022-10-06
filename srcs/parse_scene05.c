/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene05.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:46:35 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 18:31:08 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_p	*parse_color(char *str);
t_vec		*parse_coord(char *str);
t_vec		*parse_norm_vector(char *str);
int			get_expected_args_count(char **args);
int			are_there_add_params(char *str);

int	check_additional_params(char **args)
{
	int	args_count;
	int	args_cont_exp;
	int	result;

	args_cont_exp = get_expected_args_count(args);
	args_count = text_len(args);
	if (args_count == args_cont_exp)
		return (1);
	if (args_count != args_cont_exp + 3)
		return (0);
	result = ft_is_float(args[args_count - 3]);
	result = result & ft_is_float(args[args_count - 2]);
	result = result & ft_is_float(args[args_count - 1]);
	return (result);
}

int	check_base_object_args(char **args)
{
	int			args_count;
	t_color_p	*color;
	t_vec		*coord;

	args_count = text_len(args);
	if (args_count < 4)
		return (0);
	if (args_count >= 7 && ! (check_additional_params(args)))
		return (0);
	coord = parse_coord(args[1]);
	if (coord == NULL)
		return (0);
	free(coord);
	if (args_count >= 7)
		color = parse_color(args[args_count - 4]);
	else
		color = parse_color(args[args_count - 1]);
	if (color == NULL)
		return (0);
	free(color);
	return (1);
}

int	check_sphere_args(char **args)
{
	float	diametr;

	if (text_len(args) != 4 && text_len(args) != 7)
		return (0);
	if (check_base_object_args(args) == 0)
		return (0);
	if (ft_is_float(args[2]) == 0)
		return (0);
	diametr = ft_atof(args[2]);
	if (diametr <= 0)
		return (0);
	return (1);
}

int	check_plane_args(char **args)
{
	t_vec	*coord;

	if (text_len(args) != 4 && text_len(args) != 7)
		return (0);
	if (check_base_object_args(args) == 0)
		return (0);
	coord = parse_norm_vector(args[2]);
	if (coord == NULL)
		return (0);
	free(coord);
	return (1);
}

int	check_cylinder_args(char **args)
{
	t_vec	*coord;
	float	diametr;
	float	height;

	if (text_len(args) != 6 && text_len(args) != 9)
		return (0);
	if (check_base_object_args(args) == 0)
		return (0);
	coord = parse_norm_vector(args[2]);
	if (coord == NULL)
		return (0);
	free(coord);
	if (! ft_is_float(args[3]) || ! ft_is_float(args[4]))
		return (0);
	diametr = ft_atof(args[3]);
	height = ft_atof(args[4]);
	if (diametr <= 0 || height <= 0)
		return (0);
	return (1);
}
