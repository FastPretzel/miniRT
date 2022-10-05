/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 19:25:12 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		s1_size;
	int		i;

	s1_size = ft_strlen(s1) + 1;
	i = 0;
	result = malloc(s1_size);
	if (! result)
		return (0);
	while (i < s1_size)
	{
		result[i] = s1[i];
		i++;
	}
	return (result);
}
