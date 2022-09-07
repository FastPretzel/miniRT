#include "minirt.h"

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
	px = (2 * (x + 0.5) / (double)WIDTH - 1) * scale * aspect;
	py = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	/*ret.dir = vec_norm(look_at(cam, px, py));*/
	ret.dir = vec_norm((t_vec){px, py, -1});
	ret.orig = cam->orig;
	ret.t = INFINITY;
	return (ret);
}

int	inter(t_minirt *minirt, double x, double y, t_color *color)
{
	t_list		*tmp;
	t_object	*obj;
	double		tnear;

	tnear = INFINITY;
	tmp = minirt->obj_lst;
	minirt->ray = gen_ray(minirt, x, y);
	while (tmp)
	{
		obj = (t_object *)tmp->content;
		if (obj->intersect((t_sphere *)obj->params, &(minirt->ray)) && minirt->ray.t < tnear)
		{
			tnear = minirt->ray.t;
			/**color = obj->color;*/
			minirt->ray.phit = vec_add(minirt->ray.orig, \
					vec_mul(minirt->ray.dir, minirt->ray.t));
			*color = calc_light(obj, minirt);
		}
		tmp = tmp->next;
	}
	if (minirt->ray.t < INFINITY)
		return (1);
	return (0);
}

int	render(void *rt)
{
	int	x;
	int	y;
	t_color	color = {0, 0, 0};
	t_minirt	*minirt;

	y = -1;
	minirt = (t_minirt *)rt;
	/*t_list *tmp = minirt->obj_lst;*/

	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (inter(minirt, x, y, &color))
				/*my_mlx_pixel_put(minirt->mlx, x, y, color);*/
				put_color(minirt->mlx, x, y, color);
		}
	}
	mlx_put_image_to_window(minirt->mlx->ptr, minirt->mlx->win, minirt->mlx->img, 0, 0);
	return (0);
}

int	main()
{
	t_mlx		mlx;
	t_minirt	minirt;

	mlx_start(&mlx);
	minirt.mlx = &mlx;
	minirt.obj_lst = 0;
	minirt.light_lst = 0;
	init_hooks(&minirt);
	reset_img(&minirt);
	init_camera(&minirt);
	init_objs(&minirt);
	init_light(&minirt);
	render(&minirt);
	/*mlx_loop_hook(mlx.ptr, &render, (void *)&minirt);*/
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
