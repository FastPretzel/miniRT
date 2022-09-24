#include "minirt.h"

void	init_keys(t_minirt *rt)
{
	rt->keys = malloc(sizeof(t_keys));
	rt->keys->key_esc = 0;
}

int	key_down(int keycode, t_keys *keys)
{
	if (keycode == 53)
		keys->key_esc = 1;
	return (0);
}

int	key_up(int keycode, t_keys *keys)
{
	(void)keycode;
	(void)keys;
	return (0);
}
