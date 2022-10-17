/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 19:25:12 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*get_empty_string(void)
{
	char	*s;

	s = malloc(1);
	if (! s)
		return (NULL);
	s[0] = 0;
	return (s);
}

static int	char_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*(set)++ == c)
			return (1);
	}
	return (0);
}

static char	*null_return(char const *s1, char const *set)
{
	if (s1 == NULL && set == NULL)
		return (NULL);
	if (! s1)
		return (NULL);
	return (get_empty_string());
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*result;

	if (s1 == NULL || set == NULL || *s1 == 0)
		return (null_return(s1, set));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (char_in_set(s1[start], set))
		start++;
	if (start > end)
		return (get_empty_string());
	while (char_in_set(s1[end], set))
		end--;
	result = malloc(end - start + 2);
	if (! result)
		return (NULL);
	i = 0;
	while (start <= end)
		result[i++] = s1[start++];
	result[i] = 0;
	return (result);
}
