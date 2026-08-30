/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_index_from_stack.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:10:14 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/19 15:26:53 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_max(t_node *b)
{
	t_node	*max;

	max = b;
	while (b)
	{
		if (b->index > max->index)
			max = b;
		b = b->next;
	}
	return (max);
}
