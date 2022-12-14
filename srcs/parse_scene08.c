/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene08.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:43:14 by eclown            #+#    #+#             */
/*   Updated: 2022/10/05 18:31:21 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_t_plane_data(t_plane_p *data);
void	free_t_cylinder_data(t_cylinder_p *data);
void	free_object(t_object_p *object);
int		get_expected_args_count(char **args);

void	free_t_plane_data(t_plane_p *data)
{
	if (! data)
		return ;
	if (data->normal)
		free(data->normal);
	if (data->orig)
		free(data->orig);
	free(data);
}

void	free_t_cylinder_data(t_cylinder_p *data)
{
	if (! data)
		return ;
	if (data->dir)
		free(data->dir);
	if (data->orig)
		free(data->orig);
	free(data);
}

void	free_material(t_material_p *mat)
{
	if (! mat)
		return ;
	if (mat->color)
		free(mat->color);
	free(mat);
}

void	free_object(t_object_p *object)
{
	if (! object)
		return ;
	if (object->mat)
		free_material(object->mat);
	if (object->type == SPHERE && object->params)
	{
		if (((t_sphere_p *) object->params)->orig)
			free(((t_sphere_p *) object->params)->orig);
		free(object->params);
	}
	if (object->type == PLANE && object->params)
		free_t_plane_data(object->params);
	if ((object->type == CYLINDER || object->type == CONE) && object->params)
		free_t_cylinder_data(object->params);
	free(object);
}

int	are_there_add_params(char *str)
{
	int		args_cont_exp;
	int		args_count;
	char	**args;

	str = ft_strdup(str);
	replace_space_chars_to_space(str);
	args = ft_split_new(str, ' ');
	args_cont_exp = get_expected_args_count(args);
	args_count = text_len(args);
	free_text(args);
	free(str);
	return (args_cont_exp != args_count);
}
