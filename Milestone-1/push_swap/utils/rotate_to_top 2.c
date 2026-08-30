/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_to_top.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 17:27:02 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:35:31 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_to_top(t_program *p, int pos)
{
	int	size;

	size = stack_size(p->a);
	if (pos <= size / 2)
	{
		while (pos--)
			ra(p);
	}
	else
	{
		pos = size - pos;
		while (pos--)
			rra(p);
	}
}
