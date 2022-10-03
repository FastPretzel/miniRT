/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:00:22 by EClown            #+#    #+#             */
/*   Updated: 2022/01/29 21:23:44 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	re_buffer(char *s1, char *s2)
{
	if (s1 == s2)
		return ;
	while (*s2)
		*(s1++) = *(s2++);
	*s1 = 0;
}

char	*gen_line(int fd, char *line, size_t i)
{
	char		*nl;
	static char	buffers[1024][BUFFER_SIZE + 1];

	while (i)
	{
		nl = ft_strchr(buffers[fd], '\n');
		if (nl != 0)
			*(nl++) = 0;
		line = ft_strjoin2(line, buffers[fd], nl);
		if (nl == 0)
		{
			i = read(fd, &buffers[fd][0], BUFFER_SIZE);
			buffers[fd][i] = 0;
			continue ;
		}
		re_buffer(buffers[fd], nl);
		break ;
	}
	if (i == 0 && line[0] == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*result;
	char			*line;
	ssize_t			i;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(BUFFER_SIZE + 2);
	if (line == NULL)
		return (NULL);
	*line = 0;
	i = 1;
	result = gen_line(fd, line, i);
	if (result == NULL)
		return (NULL);
	return (result);
}
