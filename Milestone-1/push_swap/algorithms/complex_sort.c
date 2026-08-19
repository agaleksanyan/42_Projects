/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:12:42 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/23 18:26:28 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	complex_sort(t_program *p)
{
	int	size;
	int	bits;
	int	i;

	size = stack_size(p->a);
	if (size <= 5)
	{
		sort_5(p);
		return ;
	}
	prepare_index(p, &bits);
	i = 0;
	while (i < bits)
	{
		radix_pass(p, size, i);
		i++;
	}
}
