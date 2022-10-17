/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:49:36 by EClown            #+#    #+#             */
/*   Updated: 2022/01/29 21:22:45 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*strj_return(char *s1, char *s2, int nulled, char *nl)
{
	size_t	len;

	if (nulled)
	{
		if (!s1 && !s2)
			return (NULL);
		if (!s1)
			return (s2);
		return (s1);
	}
	len = ft_strlen(s1);
	if (nl)
	{
		s1[len] = '\n';
		s1[len + 1] = 0;
	}
	return (s1);
}

char	*ft_strjoin2(char *s1, char *s2, char *nl)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result;

	if (! s1 || ! s2)
		return (strj_return(s1, s2, 1, nl));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 2);
	if (! result)
		return (NULL);
	i = 0;
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			result[i] = s1[i];
		if (i < s2_len)
			result[i + s1_len] = s2[i];
		i++;
	}
	result[s1_len + s2_len] = 0;
	free(s1);
	return (strj_return(result, NULL, 0, nl));
}
