#include "minirt.h"

void	reset_img(t_minirt *minirt)
{
	int	size;

	size = WIDTH * HEIGHT * (minirt->mlx->bits_per_pixel / 8);
	while (size--)
		minirt->mlx->addr[size] = 0;
}

double	deg2rad(double deg)
{
	return (deg * M_PI / 180.0);
}

t_vec	look_at(t_camera *camera, double x, double y)
{
	t_vec	rows[3];
	t_vec	ret;

	rows[0] = camera->right;
	rows[1] = camera->up;
	rows[2] = camera->dir;
	ret = vec_mat_mul((t_vec){x, y, 1}, rows);
	return (ret);
}

t_ray	gen_ray(t_minirt *minirt, double x, double y)
{
	double	scale;
	double	aspect;
	double	px;
	double	py;
	t_camera	*cam;
	t_ray	ret;

	cam = minirt->camera;
	scale = tan(deg2rad(cam->fov * 0.5));
	aspect = WIDTH / (double)HEIGHT;
	px = (2 * (x + 0.5) / WIDTH - 1) * scale * aspect;
	py = (1 - 2 * (y + 0.5) / HEIGHT) * scale;
	ret.dir = vec_norm(look_at(cam, px, py));
	ret.orig = cam->orig;
	ret.t = INFINITY;
	return (ret);
}

double	ft_min_double(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

int	inter_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec		l;
	double		d2;
	double		t0;
	double		t1;
	t_solver	solver;

	l = vec_sub(sp->orig, ray->orig);
	solver.tca = vec_dot(ray->dir, l);
	d2 = vec_dot(l, l) - solver.tca * solver.tca;
	if (d2 > sp->r * sp->r)
		return (0);
	solver.thc = sqrt(sp->r * sp->r - d2);
	t0 = solver.tca - solver.thc;
	t1 = solver.tca + solver.thc;
	if (t0 < 0 && t1 < 0)
		return (0);
	ray->t = ft_min_double(t0, t1);
	return (1);
}

int	inter(t_minirt *minirt, double x, double y)
{
	minirt->ray = gen_ray(minirt, x, y);
	if (inter_sphere(minirt->sp, &(minirt->ray)))
		return (1);
	return (0);
}

void	render(t_minirt *minirt)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (inter(minirt, x, y))
				my_mlx_pixel_put(minirt->mlx, x, y, minirt->sp->color);
		}
	}
}

int	main()
{
	t_mlx		mlx;
	t_minirt	minirt;

	mlx_start(&mlx);
	minirt.mlx = &mlx;
	init_hooks(&minirt);
	reset_img(&minirt);
	init_camera(&minirt);
	init_objs(&minirt);
	render(&minirt);
	/*for(int	y = 56; y <= 390; y++)*/
	/*{*/
		/*int x = 123;*/
		/*my_mlx_pixel_put(minirt.mlx, x, y, 0xFFFFFF);*/
	/*}*/
	/*mlx_loop_hook(mlx.ptr, &render, &minirt);*/
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
