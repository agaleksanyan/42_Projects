/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:30:52 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:34:13 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	simple_sort(t_program *p)
{
	t_node	*min;
	int		pos;
	int		size;

	size = stack_size(p->a);
	if (size <= 5)
	{
		sort_5(p);
		return ;
	}
	else
	{
		while (p->a)
		{
			min = find_min(p->a);
			pos = get_position(p->a, min->value);
			rotate_to_top(p, pos);
			pb(p);
		}
	}
	while (p->b)
		pa(p);
}
