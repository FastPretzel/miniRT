/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_funcs1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:00:18 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 16:48:27 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	remove_dbl_space(char *str);

int	ft_ipow(int base, int pow)
{
	int	tmp;

	tmp = base;
	while (pow > 1)
	{
		base = base * tmp;
		pow--;
	}
	return (base);
}

double	ft_atod(char *str)
{
	double	result;
	int		part1;
	double	part2;
	char	**splits;

	splits = ft_split_new(str, '.');
	if (text_len(splits) > 2)
	{
		free_text(splits);
		return (0);
	}
	part1 = ft_atoi(splits[0]);
	if (text_len(splits) == 2)
	{
		part2 = ft_atoi(splits[1]);
		part2 = part2 / ft_ipow(10, ft_strlen(splits[1]));
	}
	else
		part2 = 0;
	result = (double) part1 + part2;
	free_text(splits);
	return (result);
}

float	ft_atof(char *str)
{
	float	result;
	int		part1;
	float	part2;
	char	**splits;

	splits = ft_split_new(str, '.');
	if (text_len(splits) > 2)
	{
		free_text(splits);
		return (0);
	}
	part1 = ft_atoi(splits[0]);
	if (text_len(splits) == 2)
	{
		part2 = ft_atoi(splits[1]);
		part2 = part2 / (float) ft_ipow(10, ft_strlen(splits[1]));
	}
	else
		part2 = 0;
	result = (float) part1 + part2;
	free_text(splits);
	return (result);
}

int	ft_is_spc(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	replace_space_chars_to_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_is_spc(str[i]))
			str[i] = 32;
		i++;
	}
	remove_dbl_space(str);
}
