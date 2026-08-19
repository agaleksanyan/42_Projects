/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:51:28 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:34:23 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_min_to_b(t_program *p)
{
	t_node	*min;
	int		pos;

	min = find_min(p->a);
	pos = get_position(p->a, min->value);
	rotate_to_top(p, pos);
	pb(p);
}

void	sort_5(t_program *p)
{
	int	size;

	size = stack_size(p->a);
	if (size == 2)
		sort_2(p);
	else if (size == 3)
		sort_3(p);
	else if (size == 4)
	{
		push_min_to_b(p);
		sort_3(p);
		pa(p);
	}
	else if (size == 5)
	{
		push_min_to_b(p);
		push_min_to_b(p);
		sort_3(p);
		pa(p);
		pa(p);
	}
}
