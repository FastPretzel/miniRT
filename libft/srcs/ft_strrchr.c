/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:11 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 19:25:11 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	if (c > 255)
		c = c % 256;
	last = NULL;
	while (*s)
	{
		if (*s == c)
			last = (char *) s;
		s++;
	}
	if (c == 0)
		return ((char *) s);
	return (last);
}
