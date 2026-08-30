/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:51:40 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:35:22 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_value(t_node *a, int min)
{
	t_node	*tmp;
	int		value;

	tmp = a;
	value = INT_MAX;
	while (tmp)
	{
		if (tmp->value < value && tmp->value > min)
			value = tmp->value;
		tmp = tmp->next;
	}
	return (value);
}

void	index_stack(t_node *a)
{
	int		index;
	int		min;
	t_node	*tmp;

	index = 0;
	min = INT_MIN;
	while (1)
	{
		tmp = a;
		min = get_min_value(a, min);
		if (min == INT_MAX)
			break ;
		while (tmp)
		{
			if (tmp->value == min)
			{
				tmp->index = index;
				break ;
			}
			tmp = tmp->next;
		}
		index++;
	}
}
