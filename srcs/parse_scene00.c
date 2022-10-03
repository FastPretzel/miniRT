/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:30:38 by eclown            #+#    #+#             */
/*   Updated: 2022/09/26 18:56:36 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char			*get_file_name(char *str);
t_vec			*parse_coord(char *str);
int				check_norm_vector(t_vec *vector);
void			*error_open_file(char *filename);
t_minirt_p			*create_scene(void);
int				open_scene_file(char *filename, int *fd);
int				parse_str_scene(t_minirt_p *scene, char *str, int line_num);

int	check_scene_file_extension(char *filename)
{
	int	strlen;

	strlen = ft_strlen(filename);
	if (filename[strlen - 1] != 't' || filename[strlen - 2] != 'r')
		return (0);
	if (filename[strlen - 3] != '.')
		return (0);
	return (1);
}

t_minirt_p	*parse_scene_p(char *filename)
{
	int		fd;
	char	*str;
	t_minirt_p	*scene;
	int		parse_error;
	int		line_num;

	if (! open_scene_file(filename, &fd))
		return (error_open_file(filename));
	str = get_next_line(fd);
	scene = create_scene();
	scene->description = get_file_name(filename);
	line_num = 1;
	while (str)
	{
		parse_error = parse_str_scene(scene, str, line_num);
		free(str);
		if (parse_error)
			return (error_open_file(filename));
		str = get_next_line(fd);
		line_num++;
	}
	return (scene);
}

/*	TODO DELETE
	t_object_p	*create_object(enum e_obj_type type, t_vec *coord,
	t_color *color, void *params)
{	
	t_object_p	*obj;

	obj = malloc(sizeof(obj));
	if (! obj)
		exit_error("malloc error in create_object");
	obj->type = type;
	obj->coord = coord;
	obj->color = color;
	obj->params = params;
	return (obj);
}*/

t_camera_p	*create_camera(t_vec *vp, t_vec *vector, int fov)
{
	t_camera_p	*camera;

	camera = malloc(sizeof(t_camera_p));
	if (! camera)
		exit_error("malloc error in create_camera");
	camera->orig = vp;
	camera->dir = vector;
	camera->fov = fov;
	return (camera);
}

t_vec	*parse_norm_vector(char *str)
{
	t_vec	*vector;

	if (! str)
		return (NULL);
	vector = parse_coord(str);
	if (! vector)
		return (NULL);
	if (check_norm_vector(vector) == 0)
	{
		free(vector);
		return (NULL);
	}
	return (vector);
}
