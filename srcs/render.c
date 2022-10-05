#include "minirt.h"

static t_vec	look_at(t_camera *camera, double x, double y)
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
	ret.dir = vec_norm(look_at(cam, px, py));
	ret.orig = cam->orig;
	ret.t = INFINITY;
	return (ret);
}

static void	coloring(t_minirt *rt, double x, double y, void *nearest_obj)
{
	t_color		color;

	rt->ray.phit = vec_add(rt->ray.orig, \
			vec_mul(rt->ray.dir, rt->ray.t));
	color = calc_light((t_object *)nearest_obj, rt);
	/*printf("%f,%f,%f\n", color.r, color.g, color.b);*/
	/*calc_light((t_object *)nearest_obj, rt, &color);*/
	put_color(rt->mlx, x, y, color);
}

static void	inter(t_minirt *rt, double x, double y)
{
	t_object	**obj;
	void		*nearest_obj;
	int		i;

	nearest_obj = 0;
	rt->tnear = INFINITY;
	obj = rt->objects;
	rt->ray = gen_ray(rt, x, y);
	i = -1;
	while (obj[++i])
	{
		if (obj[i]->intersect(obj[i]->params, &(rt->ray)) && rt->ray.t < rt->tnear)
		{
			rt->tnear = rt->ray.t;
			nearest_obj = obj[i];
		}
	}
	if (nearest_obj)
		coloring(rt, x, y, nearest_obj);
}

int	render(void *ptr)
{
	int	x;
	int	y;
	t_minirt	*rt;

	y = -1;
	rt = (t_minirt *)ptr;
	if (rt->keys->key_esc)
		exit(0);
	reset_img(rt);
	rotate(rt);
	translate(rt);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			inter(rt, x, y);
	}
	mlx_put_image_to_window(rt->mlx->ptr, rt->mlx->win, \
			rt->mlx->img, 0, 0);
	return (0);
}
