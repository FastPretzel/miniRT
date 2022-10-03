/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_funcs0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 20:32:58 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 16:46:41 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_error(char *msg)
{
	ft_putstr_fd("Fatal error: ", 2);
	if (msg != NULL)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

char	*get_trim_str(char *s1, char const *set)
{
	char	*result;

	if (! s1)
		return (NULL);
	result = ft_strtrim(s1, set);
	if (result == s1)
		return (s1);
	free(s1);
	return (result);
}

int	text_len(char **text)
{
	int	i;

	if (text == NULL)
		return (0);
	i = 0;
	while (text[i])
	{
		i++;
	}
	return (i);
}

void	free_text(char **text)
{
	int	i;

	if (! text)
		return ;
	i = 0;
	while (text[i])
	{
		free(text[i++]);
	}
	free(text);
}

int	ft_num_len(int n)
{
	int	res;

	if (n == 0)
		return (1);
	res = 0;
	while (n)
	{
		res++;
		n = n / 10;
	}
	return (n);
}
