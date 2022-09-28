#include "minirt.h"

void	translate(t_minirt *rt)
{
	if (rt->keys->key_up)
	{
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->dir);
		rt->keys->key_up = 0;
	}
	if (rt->keys->key_down)
	{
		rt->camera->orig = vec_add(rt->camera->orig, vec_neg(rt->camera->dir));
		rt->keys->key_down = 0;
	}
	if (rt->keys->key_right)
	{
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->right);
		rt->keys->key_right = 0;
	}
	if (rt->keys->key_left)
	{
		rt->camera->orig = vec_add(rt->camera->orig, vec_neg(rt->camera->right));
		rt->keys->key_left = 0;
	}
	if (rt->keys->key_space)
	{
		rt->camera->orig = vec_add(rt->camera->orig, rt->camera->up);
		rt->keys->key_space = 0;
	}
	if (rt->keys->key_shift)
	{
		rt->camera->orig = vec_add(rt->camera->orig, vec_neg(rt->camera->up));
		rt->keys->key_shift = 0;
	}
}
