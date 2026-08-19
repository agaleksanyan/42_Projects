/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opr_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:25 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/22 20:58:55 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_program *p)
{
	swap_nodes(&(p->a));
	p->stats.sa++;
	if (!p->flags.checker_mode)
		write(1, "sa\n", 3);
}

void	sb(t_program *p)
{
	swap_nodes(&(p->b));
	p->stats.sb++;
	if (!p->flags.checker_mode)
		write(1, "sb\n", 3);
}

void	ss(t_program *p)
{
	swap_nodes(&(p->a));
	swap_nodes(&(p->b));
	p->stats.ss++;
	if (!p->flags.checker_mode)
		write(1, "ss\n", 3);
}
