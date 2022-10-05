#include "minirt.h"

void	translate(t_minirt *rt)
{
	if (rt->keys->key_up)
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->dir);
	if (rt->keys->key_down)
		rt->camera->orig = vec_add(rt->camera->orig, vec_neg(rt->camera->dir));
	if (rt->keys->key_right)
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->right);
	if (rt->keys->key_left)
		rt->camera->orig = vec_add(rt->camera->orig, \
				vec_neg(rt->camera->right));
	if (rt->keys->key_space)
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->up);
	if (rt->keys->key_shift)
		rt->camera->orig = vec_add(rt->camera->orig, vec_neg(rt->camera->up));
}
