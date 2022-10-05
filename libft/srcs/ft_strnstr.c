/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 19:25:12 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	i;
	size_t	j;

	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *) haystack);
	i = 0;
	while (i + n_len <= ft_strlen(haystack) && i + n_len <= len)
	{
		j = 0;
		while (j < n_len)
		{
			if (haystack[i + j] != needle[j])
			{
				j = 0;
				break ;
			}
			j++;
		}
		if (j)
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
