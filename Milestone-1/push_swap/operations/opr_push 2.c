/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opr_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:07 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/22 20:58:46 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_program *p)
{
	push_nodes(&(p->b), &(p->a));
	p->stats.pa++;
	if (!p->flags.checker_mode)
		write(1, "pa\n", 3);
}

void	pb(t_program *p)
{
	push_nodes(&(p->a), &(p->b));
	p->stats.pb++;
	if (!p->flags.checker_mode)
		write(1, "pb\n", 3);
}
