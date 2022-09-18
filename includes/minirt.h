#ifndef MINIRT_H
#define MINIRT_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <time.h>
#include <float.h>

#define WIDTH 1920
#define HEIGHT 1080

//tmp defines
#define FOV 90.0
#define AMBIENT 0.2

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	orig;
	double	t;
	t_vec	phit;
}	t_ray;

typedef struct	s_camera
{
	t_vec	orig;
	t_vec	dir;
	double	fov;
	t_vec	right;
	t_vec	up;

	//t_vec	u;
	//t_vec	v;
	//t_vec	w;
	//t_vec	horiz;
	//t_vec	vert;
	//t_vec	low_left_corner;
}	t_camera;

typedef struct	s_sphere
{
	t_vec	orig;
	double	r;
	//int	color;
}	t_sphere;

typedef struct	s_plane
{
	t_vec	orig;
	t_vec	normal;
}	t_plane;

typedef struct	s_light
{
	t_vec	pos;
	double	intens;
}	t_light;

typedef struct s_mlx {
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_mlx;

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct	s_material
{
	t_color	color;
	double	albedo[2];
	double	spec_exp;
}	t_material;

typedef struct	s_object
{
	t_material	mat;
	void	*params;
	int	(*intersect)();
	t_vec	(*get_normal)();
	//t_color	color;
}	t_object;

typedef struct	s_list
{
	void		*content;
	struct s_list	*next;
}	t_list;

typedef struct s_minirt
{
	t_mlx		*mlx;
	t_camera	*camera;
	t_list		*obj_lst;
	t_list		*light_lst;
	t_ray		ray;
	double		tnear;
	double		t;
}	t_minirt;

//temp utils
t_color get_color(double r, double g, double b);
int	get_int_color(int r, int g, int b);
void	reset_img(t_minirt *minirt);

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int	cross_exit(t_minirt *minirt);
void	init_hooks(t_minirt *minirt);
void	mlx_start(t_mlx *mlx);
//int	render(t_minirt *minirt);
//void	paint_black(t_minirt *minirt);

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
void	matr_mult(double a[4][4], double b[4][4], double res[4][4]);
//void	put_color(t_rt *rt, t_img img, int x, int y);
void	put_color(t_mlx *mlx, int x, int y, t_color color);
t_color	col_mul(t_color a, double b);
t_color	col_add(t_color a, t_color b);

void	init_camera(t_minirt *minirt);
void	init_objs(t_minirt *minirt);
void	init_light(t_minirt *minirt);

//intersections
//int	inter(t_minirt *minirt, double x, double y, t_color *color);
void	inter(t_minirt *minirt, double x, double y);
int	inter_sphere(void *ptr, t_ray *ray);
int	inter_plane(void *ptr, t_ray *ray);

//get_normal
t_vec	get_norm_sphere(t_ray *ray, void *ptr);
t_vec	get_norm_plane(t_ray *ray, void *ptr);

t_color	calc_light(t_object *obj, t_minirt *rt);
#endif
