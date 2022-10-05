/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:33:38 by eclown            #+#    #+#             */
/*   Updated: 2022/09/29 20:09:17 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef IS_BONUS
#  define IS_BONUS_PART 1
# endif

# include	"../libft/libft.h"
# include	<stddef.h>
# include	<stdarg.h>
# include	<stdio.h>
# include	<sys/fcntl.h>
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
//#include <string.h>
//# include	"mlx/mlx_png.h"
# include	"get_next_line.h"


#define WIDTH 800
#define HEIGHT 600


#define FOV 90.0
#define AMBIENT 0.2
#define DGR_DELTA 2.0

//typedef struct s_scr {
	//void		*mlx;
	//void		*win;
	//int			size_x;
	//int			size_y;
//}	t_scr;
typedef struct	s_list
{
	void		*content;
	struct s_list	*next;
}	t_list;

enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

typedef struct s_qtr
{
	double	x;
	double	y;
	double	z;
	double	r;
}	t_qtr;

typedef struct s_color
{
	double 	r;
	double 	g;
	double 	b;
}	t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

/*--------------------------START MODIFIED STRUCTS--------------------------*/

typedef struct s_color_p
{
	int	transp;
	int	r;
	int	g;
	int	b;
}	t_color_p;

typedef struct s_alight_p
{
	float	ratio;
	t_color_p	*color;
}	t_alight_p;

typedef struct s_camera_p
{
	t_vec			*orig;
	t_vec			*dir;
	double			fov;
	t_vec			right;
	t_vec			up;
}	t_camera_p;

typedef struct s_light_p
{
	t_vec	*pos;
	double	intens;
	t_color_p	*color;
}	t_light_p;

typedef struct s_material_p
{
	t_color_p	*color;
	double	albedo[2];
	double	spec_exp;
}	t_material_p;

typedef struct s_object_p
{
	enum e_obj_type	type;
	t_material_p	*mat;
	void			*params;
}	t_object_p;

typedef struct s_sphere_data_p
{
	t_vec	*orig;
	double	r;
}	t_sphere_p;

typedef struct s_plane_data_p
{
	t_vec	*orig;
	t_vec	*normal;
}	t_plane_p;

typedef struct s_cylinder_data_p
{
	t_vec	*orig;
	t_vec	*dir;
	double	d;
	double	h;
}	t_cylinder_p;

typedef t_cylinder_p t_cone_p;

/*-------------------------- END MODIFIED STRUCTS --------------------------*/

typedef struct s_keys
{
	int	key_esc;
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_e;
	int	key_q;
	int	key_up;
	int	key_down;
	int	key_left;
	int	key_right;
	int	key_space;
	int	key_shift;
}	t_keys;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	orig;
	double	t;
	t_vec	phit;
}	t_ray;


/*--------------------------START ORIGINAL STRUCTS--------------------------*/

typedef struct s_alight
{
	float	ratio;
	t_color	color;
}	t_alight;

typedef struct s_camera
{
	t_vec			orig;
	t_vec			dir;
	double	fov;
	t_vec			right;
	t_vec			up;
}	t_camera;

typedef struct s_light
{
	t_vec	pos;
	double	intens;
	t_color	color;
}	t_light;

typedef struct s_material
{
	t_color	color;
	double	albedo[2];
	double	spec_exp;
}	t_material;

typedef struct s_object
{
	enum e_obj_type	type;
	void			*params;
	int				(*intersect)();
	t_vec			(*get_normal)();
	t_material		mat;
}	t_object;

typedef struct s_sphere_data
{
	t_vec	orig;
	double	r;
}	t_sphere;

typedef struct s_plane_data
{
	t_vec	orig;
	t_vec	normal;
}	t_plane;

typedef struct s_cylinder_data
{
	t_vec	orig;
	t_vec	dir;
	double	d;
	double	h;
}	t_cylinder;

typedef t_cylinder t_cone;

typedef struct s_mlx {
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_mlx;

typedef struct s_scene
{
	char		*description;
	t_alight 	*alight;
	t_camera	*camera;
	t_light 	**lights;
	t_object 	**objects;
	t_mlx		*mlx;
	t_keys		*keys;
	t_ray		ray;
	double		tnear;
}	t_minirt;

/*-------------------------- END ORIGINAL STRUCTS --------------------------*/




typedef struct s_scene_p
{
	char		*description;
	t_alight_p 	*alight;
	t_camera_p	*camera;
	t_light_p 	**lights;
	t_object_p 	**objects;
	//t_mlx		*mlx;
	t_keys		*keys;
	t_ray		ray;
	double		tnear;
}	t_minirt_p;





void		exit_error(char *msg);
char		**ft_split_new(char *str, char sep);
int			text_len(char **text);
int			ft_is_spc(char c);
void		free_text(char **text);
int			ft_num_len(int n);
double		ft_atod(char *str);
float		ft_atof(char *str);
void		replace_space_chars_to_space(char *str);
int			ft_is_integer(char *str);
int			ft_is_float(char *str);
int			is_all_float(char **text);
int			is_all_pos_int(char **text);
void		*file_format_error(char *str_err);
void		free_scene_p(t_minirt_p *scene);
t_minirt_p	*parse_scene_p(char *filename);
t_minirt	*parse_scene(char *filename);
void		free_scene(t_minirt *scene);


/*-------------------------- RT FUNCS --------------------------*/

//temp utils
t_color get_color(double r, double g, double b);
int	get_int_color(int r, int g, int b);
void	reset_img(t_minirt *minirt);

//void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int	cross_exit(t_minirt *minirt);
void	init_hooks(t_minirt *minirt);
void	init_keys(t_minirt *rt);
int	key_down(int keycode, t_keys *keys);
//int	key_up(int keycode, t_keys *keys);
void	mlx_start(t_mlx *mlx);
//int	render(void *ptr);

//lst_utils
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

//vec_utils
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mul(t_vec a, double b);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
double	vec_len(t_vec v);
t_vec	vec_norm(t_vec v);
t_vec	vec_neg(t_vec v);
t_vec	vec_mat_mul(t_vec v, t_vec rows[3]);

//other utils
double	ft_min_double(double a, double b);
double	deg2rad(double deg);
//void	matr_mult(double a[4][4], double b[4][4], double res[4][4]);
//void	put_color(t_rt *rt, t_img img, int x, int y);
void	put_color(t_mlx *mlx, int x, int y, t_color color);
t_color	col_mul(t_color a, double b);
t_color	col_add(t_color a, t_color b);
t_color	col_mul_vec(t_color a, t_color b);

//void	init_camera(t_minirt *minirt);
//void	init_objs(t_minirt *minirt);
//void	init_light(t_minirt *minirt);

//rt
int	render(void *ptr);
void	translate(t_minirt *rt);
void	rotate(t_minirt *rt);

//qtr utils
void	neg_qtr(t_qtr *q, t_qtr *q_neg);
t_qtr	*vec2qtr(t_vec *p);
void	update_vec(t_qtr *pos, t_vec *p);
double	degree(t_keys *keys);

//intersections
//int	inter(t_minirt *minirt, double x, double y, t_color *color);
//void	inter(t_minirt *minirt, double x, double y);
int	inter_sphere(void *ptr, t_ray *ray);
int	inter_plane(void *ptr, t_ray *ray);
int	inter_cylinder(void *ptr, t_ray *ray);
int	inter_cone(void *ptr, t_ray *ray);

//get_normal
t_vec	get_norm_sphere(t_ray *ray, void *ptr);
t_vec	get_norm_plane(t_ray *ray, void *ptr);
t_vec	get_norm_cylinder(t_ray *ray, void *ptr);
t_vec	get_norm_cone(t_ray *ray, void *ptr);

t_color	calc_light(t_object *obj, t_minirt *rt);
//void	calc_light(t_object *obj, t_minirt *rt, t_color *color);
#endif	//MINIRT_H
