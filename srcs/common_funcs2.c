/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_funcs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:39:13 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 17:18:06 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
return 1 if str is positive integer
NOT int, just INTEGER (any lenght)
 */
int	ft_is_pos_integer(char *str)
{	
	if (str == NULL || *str == 0)
		return (0);
	while (*str)
	{
		if (! ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_is_integer(char *str)
{
	if (str[0] == '-')
		str++;
	else if (! ft_isdigit(str[0]))
		return (0);
	return (ft_is_pos_integer(str));
}

int	ft_is_float(char *str)
{
	char	**parts;
	int		parts_len;
	int		result;

	if (str == NULL || *str == 0)
		return (0);
	parts = ft_split(str, '.');
	parts_len = text_len(parts);
	if (parts_len > 2 || parts_len < 1)
		return (0);
	result = ft_is_integer(parts[0]);
	if (parts_len == 2)
			result = (result && ft_is_pos_integer(parts[1]));
	free_text(parts);
	return (result);
}

int	is_all_float(char **text)
{
	if (text == NULL || text[0] == NULL)
		return (0);
	while (*text)
	{
		if (ft_is_float(*text) == 0)
			return (0);
		text++;
	}
	return (1);
}

int	is_all_pos_int(char **text)
{
	if (text == NULL || text[0] == NULL)
		return (0);
	while (*text)
	{
		if (ft_is_pos_integer(*text) == 0)
			return (0);
		text++;
	}
	return (1);
}
