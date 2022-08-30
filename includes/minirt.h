#ifndef MINIRT_H
#define MINIRT_H

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define WIDTH 1920
#define HEIGHT 1080

//tmp defines
#define FOV 90.0

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
}	t_ray;

typedef struct	s_camera
{
	t_vec	orig;
	t_vec	dir;
	double	fov;
	t_vec	right;
	t_vec	up;
}	t_camera;

typedef struct	s_sphere
{
	t_vec	orig;
	double	r;
	int	color;
}	t_sphere;

typedef struct s_mlx {
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_mlx;

typedef struct	s_solver
{
	double	tca;
	double	thc;
}	t_solver;

typedef struct s_minirt
{
	t_mlx		*mlx;
	t_camera	*camera;
	t_sphere	*sp;
	t_ray		ray;
}	t_minirt;

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int	cross_exit(t_minirt *minirt);
void	init_hooks(t_minirt *minirt);
void	mlx_start(t_mlx *mlx);
//int	render(t_minirt *minirt);
void	paint_black(t_minirt *minirt);

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

void	init_camera(t_minirt *minirt);
void	init_objs(t_minirt *minirt);
#endif
