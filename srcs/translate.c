#include "minirt.h"
//переделать через сумму векторов (к радиус вектору камеры(orig) прибавить вектор направления перемещения)
//вперед-назад == dir
//вправо-влево == right
//вверх-вниз == up
void	translate(t_minirt *rt)
{
	if (rt->keys->key_up)
	{
		rt->camera->orig.z -= 0.5;
		rt->keys->key_up = 0;
	}
	if (rt->keys->key_down)
	{
		rt->camera->orig.z += 0.5;
		rt->keys->key_down = 0;
	}
	if (rt->keys->key_left)
	{
		rt->camera->orig.x -= 0.5;
		rt->camera->dir.x -= 0.5;
		rt->keys->key_left = 0;
	}
	if (rt->keys->key_right)
	{
		rt->camera->orig.x += 0.5;
		rt->camera->dir.x += 0.5;
		rt->keys->key_right = 0;
	}
	if (rt->keys->key_space)
	{
		rt->camera->orig.y += 0.5;
		rt->camera->dir.y += 0.5;
		rt->keys->key_space = 0;
	}
	if (rt->keys->key_shift)
	{
		rt->camera->orig.y -= 0.5;
		rt->camera->dir.y -= 0.5;
		rt->keys->key_shift = 0;
	}
}
