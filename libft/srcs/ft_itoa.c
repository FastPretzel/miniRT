/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 19:25:12 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	abs_i(int i)
{
	long int	n;

	n = (long int)i;
	if (n < 0)
		return (n * -1);
	return (n);
}

static int	get_int_size(int n)
{
	int			size;

	if (n == 0)
		return (1);
	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long int	ln;
	int			size;
	char		*res;
	int			sign;

	size = get_int_size(n);
	ln = abs_i(n);
	sign = 1;
	if (n < 0)
		sign = 2;
	res = malloc(size + sign);
	if (! res)
		return (NULL);
	res[size + sign - 1] = 0;
	while (size)
	{
		res[size - 2 + sign] = (char)((ln % 10) + 48);
		size--;
		ln /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
