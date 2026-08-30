/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:09:51 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/23 16:02:20 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_chunk_size(int size)
{
	if (size <= 100)
		return (11);
	return (23);
}

static void	move_max_to_top(t_program *p, t_node *max)
{
	int	pos;
	int	size;

	pos = get_position(p->b, max->value);
	size = stack_size(p->b);
	if (pos <= size / 2)
		while (pos-- > 0)
			rb(p);
	else
		while (pos++ < size)
			rrb(p);
}

static void	push_chunks(t_program *p, int chunk)
{
	int	i;

	i = 0;
	while (p->a)
	{
		if (p->a->index <= i)
		{
			pb(p);
			rb(p);
			i++;
		}
		else if (p->a->index <= i + chunk)
		{
			pb(p);
			i++;
		}
		else
			ra(p);
	}
}

static void	push_back_sorted(t_program *p)
{
	t_node	*max;

	while (p->b)
	{
		max = find_max(p->b);
		move_max_to_top(p, max);
		pa(p);
	}
}

void	medium_sort(t_program *p)
{
	int	size;
	int	chunk;

	size = stack_size(p->a);
	if (size <= 5)
	{
		sort_5(p);
		return ;
	}
	index_stack(p->a);
	chunk = get_chunk_size(size);
	push_chunks(p, chunk);
	push_back_sorted(p);
}
