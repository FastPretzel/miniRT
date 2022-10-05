/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*res;
	size_t	i;

	if (! s)
		return (NULL);
	s_len = ft_strlen(s);
	if (! s_len || s_len <= start)
		return (get_empty_string());
	if (start + len < s_len)
		res = malloc(len + 1);
	else
		res = malloc(s_len - start + 1);
	if (! res)
		return (NULL);
	i = start;
	while (i < start + len && s[i])
	{
		res[i - start] = s[i];
		i++;
	}
	res[i - start] = 0;
	return (res);
}
