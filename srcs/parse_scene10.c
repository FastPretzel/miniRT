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

#include "minirt.h"

t_object_p	*parse_sphere(char *str);
t_object_p	*parse_plane(char *str);
t_object_p	*parse_cylinder(char *str);
int			parse_error(int line_num, char *str);
int			add_alight_to_scene(t_minirt_p *scene, char *str, int line_num);
int			add_camera_to_scene(t_minirt_p *scene, char *str, int line_num);
int			add_light_to_scene(t_minirt_p *scene, char *str, int line_num);

int	get_object_count(t_object_p	**object_array)
{
	int	i;

	if (object_array == NULL)
		return (0);
	i = 0;
	while (object_array[i])
		i++;
	return (i);
}

void	add_object_to_array(t_object_p ***object_array, t_object_p *new_object)
{
	t_object_p	**old_obj_array;
	t_object_p	**new_obj_array;
	int			i;

	old_obj_array = *object_array;
	new_obj_array = malloc(sizeof(t_object_p *)
			*(get_object_count(old_obj_array) +2));
	if (! new_obj_array)
		exit_error("malloc error in add_object_to_array");
	i = 0;
	while (old_obj_array && old_obj_array[i])
	{
		new_obj_array[i] = old_obj_array[i];
		i++;
	}
	new_obj_array[i++] = new_object;
	new_obj_array[i] = NULL;
	free(old_obj_array);
	*object_array = new_obj_array;
}

int	add_object_to_scene(t_minirt_p *scene, char *str, int line_num)
{
	t_object_p	*new_object;

	if (str[0] == 's')
		new_object = parse_sphere(str);
	else if (str[0] == 'p')
		new_object = parse_plane(str);
	else if (str[0] == 'c')
		new_object = parse_cylinder(str);
	else
		return (parse_error(line_num, "Wrong object indetifier"));
	if (new_object == NULL)
		return (parse_error(line_num, "Object parse error. "));
	add_object_to_array(&(scene->objects), new_object);
	return (0);
}

int	is_object_in_str(char *str)
{
	if (str[0] != 's' && str[0] != 'p' && str[0] != 'c')
		return (0);
	if (str[1] != 'p' && str[1] != 'l' && str[1] != 'y')
		return (0);
	if (! ft_is_spc(str[2]))
		return (0);
	return (1);
}

int	parse_str_scene(t_minirt_p *scene, char *str, int line_num)
{
	int	add_error;

	str = ft_strtrim(str, " \t\n");
	if (str[0] == 0)
		add_error = 0;
	else if (str[0] == 'A' && ft_is_spc(str[1]))
		add_error = add_alight_to_scene(scene, str, line_num);
	else if (str[0] == 'C' && ft_is_spc(str[1]))
		add_error = add_camera_to_scene(scene, str, line_num);
	else if (str[0] == 'L' && ft_is_spc(str[1]))
		add_error = add_light_to_scene(scene, str, line_num);
	else if (is_object_in_str(str))
		add_error = add_object_to_scene(scene, str, line_num);
	else
		add_error = 1;
	free(str);
	if (add_error != 0)
	{
		free_scene_p(scene);
		return (1);
	}
	return (add_error);
}
