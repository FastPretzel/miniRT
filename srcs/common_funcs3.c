/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_funcs3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eclown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:56:27 by eclown            #+#    #+#             */
/*   Updated: 2022/09/23 16:56:45 by eclown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	remove_dbl_space(char *str)
{
	int		i;
	int		j;
	char	*old_str;
	char	*new_str;

	old_str = ft_strdup(str);
	if (! old_str)
		exit_error("malloc error in remove_dbl_space");
	new_str = str;
	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (old_str[i] != ' ')
			new_str[j++] = old_str[i++];
		else if (old_str[i + 1] != ' ')
			new_str[j++] = old_str[i++];
		else
			i++;
	}
	new_str[j] = 0;
	free(old_str);
}

char	*get_file_name(char *str)
{
	char	**parts;
	int		parts_len;
	char	*result;

	if (! str || *str == 0)
		return (NULL);
	parts = ft_split_new(str, '/');
	parts_len = text_len(parts);
	result = ft_strdup(parts[parts_len - 1]);
	free_text(parts);
	return (result);
}
