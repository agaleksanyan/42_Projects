/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:18:57 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:28:58 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*create_node(void *content, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*node;
	void	*new_content;

	new_content = f(content);
	if (!new_content)
		return (NULL);
	node = ft_lstnew(new_content);
	if (!node)
	{
		del(new_content);
		return (NULL);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = create_node(lst->content, f, del);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

void	*multiply_by_two(void *content)
{
	int	*new_int;

	new_int = malloc(sizeof(int));
	if (!new_int)
		return (NULL);
	*new_int = (*(int *)content) * 2;
	return (new_int);
}

void	del_int(void *content)
{
	free(content);
}
