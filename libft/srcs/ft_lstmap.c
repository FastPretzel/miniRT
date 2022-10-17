/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:11 by EClown            #+#    #+#             */
/*   Updated: 2021/10/18 20:26:13 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	lst_map_iter(t_list **first, t_list **last, t_list *tmp)
{
	if (! *first)
	{
		*first = tmp;
		*last = tmp;
	}
	else
	{
		ft_lstadd_back(last, tmp);
		*last = tmp;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp;
	t_list	*last;

	if (! lst)
		return (NULL);
	first = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (! tmp)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		lst_map_iter(&first, &last, tmp);
		lst = lst->next;
	}
	return (first);
}
