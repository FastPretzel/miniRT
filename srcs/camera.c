#include "minirt.h"

static t_vec	init_orig()
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 0;
	ret.z = 1;
	return (ret);
}

static t_vec	init_dir()
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 0;
	ret.z = -1;
	return (ret);
}

void	init_camera(t_minirt *minirt)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->orig = init_orig();
	cam->dir = vec_norm(init_dir());
	cam->right = vec_norm(vec_cross(cam->dir, (t_vec){0, 1, 0}));
	cam->up = vec_norm(vec_cross(cam->right, cam->dir));
	cam->fov = FOV;
	minirt->camera = cam;
}
