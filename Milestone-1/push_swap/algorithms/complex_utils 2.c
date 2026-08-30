/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:13:03 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/23 18:13:43 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	int_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	key;

	i = 1;
	while (i < size)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}

int	get_max_bits(t_node *stack)
{
	int	max;
	int	bits;

	max = 0;
	bits = 0;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	assign_index(t_node *stack, int *sorted, int size)
{
	int	i;

	while (stack)
	{
		i = 0;
		while (i < size)
		{
			if (stack->value == sorted[i])
			{
				stack->index = i;
				break ;
			}
			i++;
		}
		stack = stack->next;
	}
}

void	prepare_index(t_program *p, int *bits)
{
	int		size;
	int		*arr;
	int		i;
	t_node	*tmp;

	size = stack_size(p->a);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		error_exit(p);
	tmp = p->a;
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp->value;
		tmp = tmp->next;
	}
	int_sort(arr, size);
	assign_index(p->a, arr, size);
	*bits = get_max_bits(p->a);
	free(arr);
}

void	radix_pass(t_program *p, int size, int bit)
{
	int	i;
	int	pushed;

	i = 0;
	pushed = 0;
	while (i < size)
	{
		if (((p->a->index >> bit) & 1) == 0)
		{
			pb(p);
			pushed++;
		}
		else
			ra(p);
		i++;
	}
	while (pushed--)
		pa(p);
}
