/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:11 by EClown            #+#    #+#             */
/*   Updated: 2021/12/13 20:56:22 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	short int	d;
	char		digs[20];
	int			i;

	i = 0;
	if (n == 0)
		write(fd, "0", 1);
	else if (n > 0)
		d = 1;
	else
	{
		d = -1;
		write(fd, "-", 1);
	}
	while (n)
	{
		digs[i] = (char)((n % 10) * d + 48);
		n = n / 10;
		i++;
	}
	while (i)
	{
		write(fd, &digs[i - 1], 1);
		i--;
	}
}
