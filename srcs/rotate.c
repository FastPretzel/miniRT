#include "minirt.h"

typedef struct s_prev
{
	double	x;
	double	y;
	double	z;
}	t_prev;

static void	rotate_xyz(t_minirt *rt)
{
	t_prev	prev;
	t_camera	*cam;
//подставить вместо xyz соотв вектора камеры x == right y == up z == dir
	cam = rt->camera;
	//Ox == right
	prev.y = cam->y;
	cam->y = prev.y * cos(cam->alpha) + cam->z * sin(cam->alpha);
	cam->z = -prev.y * sin(cam->alpha) + cam->z * cos(cam->alpha);
	//Oy == up
	prev.x = cam->x;
	cam->x = prev.x * cos(cam->beta) + cam->z * sin(cam->beta);
	cam->z = -prev.x * sin(cam->beta) + cam->z * cos(cam->beta);
	//Oz == dir
	prev.x = cam->x;
	cam->x = prev.x * cos(cam->gamma) - cam->y * sin(cam->gamma);
	cam->y = prev.x * sin(cam->gamma) + cam->y * cos(cam->gamma);
}

void	rotate(t_minirt *rt)
{
	if (rt->keys->w_key)
	{
		rt->camera->alpha += 0.05;
		rt->keys->w_key = 0;
	}
	if (rt->keys->s_key)
	{
		rt->camera->alpha -= 0.05;
		rt->keys->s_key = 0;
	}
	if (rt->keys->a_key)
	{
		rt->camera->beta += 0.05;
		rt->keys->a_key = 0;
	}
	if (rt->keys->d_key)
	{
		rt->camera->beta -= 0.05;
		rt->keys->d_key = 0;
	}
	if (rt->keys->e_key)
	{
		rt->camera->gamma += 0.05;
		rt->keys->e_key = 0;
	}
	if (rt->keys->q_key)
	{
		rt->camera->gamma -= 0.05;
		rt->keys->q_key = 0;
	}
	rotate_xyz(rt);
}
