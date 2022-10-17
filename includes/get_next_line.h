/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:36:48 by EClown            #+#    #+#             */
/*   Updated: 2022/09/16 14:59:00 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stddef.h>
# include <stdlib.h>
# include <sys/fcntl.h>
# include <unistd.h>
# include "libft.h"

char			*get_next_line(int fd);
char			*ft_strjoin2(char *s1, char *s2, char *nl);

#endif
