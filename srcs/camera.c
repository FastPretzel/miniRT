#include "minirt.h"

static t_vec	init_orig()
{
	t_vec	ret;

	ret.x = 0;
	ret.y = 0;
	ret.z = 2;
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
	cam->fov = FOV;
	cam->orig = init_orig();
	cam->dir = vec_norm(init_dir());
	cam->right = vec_norm(vec_cross(cam->dir, (t_vec){0, 1, 0}));
	cam->up = vec_norm(vec_cross(cam->right, cam->dir));
	/*cam->alpha = 0;*/
	/*cam->beta = 0;*/
	/*cam->gamma = 0;*/
	/*cam->w = vec_neg(cam->dir);*/
	/*cam->u = vec_norm(vec_cross((t_vec){0,1,0}, cam->w));*/
	/*cam->v = vec_cross(cam->w, cam->u);*/
	/*double	h = tan(deg2rad(FOV * 0.5));*/
	/*double	viewport_height = h * 2;*/
	/*double	viewport_width = WIDTH / (double)HEIGHT * viewport_height;;*/
	/*cam->horiz = vec_mul(cam->u, viewport_width);*/
	/*cam->vert = vec_mul(cam->v, viewport_height);*/
	/*cam->low_left_corner = vec_sub(vec_sub(vec_sub(cam->orig,*/
		/*vec_mul(cam->horiz, 0.5)), vec_mul(cam->vert, 0.5)), cam->w);*/
	minirt->camera = cam;
}
