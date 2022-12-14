/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <cgoth@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:27:23 by cgoth            #+#    #+#             */
/*   Updated: 2022/10/06 16:27:48 by cgoth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_keys(t_minirt *rt)
{
	rt->keys = malloc(sizeof(t_keys));
	rt->keys->key_esc = 0;
	rt->keys->key_w = 0;
	rt->keys->key_a = 0;
	rt->keys->key_s = 0;
	rt->keys->key_d = 0;
	rt->keys->key_e = 0;
	rt->keys->key_q = 0;
	rt->keys->key_up = 0;
	rt->keys->key_down = 0;
	rt->keys->key_left = 0;
	rt->keys->key_right = 0;
	rt->keys->key_space = 0;
	rt->keys->key_shift = 0;
}

static void	key_down_2(int keycode, t_keys *keys)
{
	if (keycode == 257)
		keys->key_shift = 1;
	if (keycode == 126)
		keys->key_up = 1;
	if (keycode == 125)
		keys->key_down = 1;
	if (keycode == 124)
		keys->key_right = 1;
	if (keycode == 123)
		keys->key_left = 1;
}

int	key_down(int keycode, t_keys *keys)
{
	if (keycode == 53)
		keys->key_esc = 1;
	if (keycode == 13)
		keys->key_w = 1;
	if (keycode == 0)
		keys->key_a = 1;
	if (keycode == 1)
		keys->key_s = 1;
	if (keycode == 2)
		keys->key_d = 1;
	if (keycode == 14)
		keys->key_e = 1;
	if (keycode == 12)
		keys->key_q = 1;
	if (keycode == 49)
		keys->key_space = 1;
	if (keycode > 100)
		key_down_2(keycode, keys);
	return (0);
}

int	key_up(int keycode, t_keys *keys)
{
	if (keycode == 13)
		keys->key_w = 0;
	if (keycode == 0)
		keys->key_a = 0;
	if (keycode == 1)
		keys->key_s = 0;
	if (keycode == 2)
		keys->key_d = 0;
	if (keycode == 14)
		keys->key_e = 0;
	if (keycode == 12)
		keys->key_q = 0;
	if (keycode == 49)
		keys->key_space = 0;
	if (keycode == 257)
		keys->key_shift = 0;
	if (keycode == 126)
		keys->key_up = 0;
	if (keycode == 125)
		keys->key_down = 0;
	if (keycode == 124)
		keys->key_right = 0;
	if (keycode == 123)
		keys->key_left = 0;
	return (0);
}
