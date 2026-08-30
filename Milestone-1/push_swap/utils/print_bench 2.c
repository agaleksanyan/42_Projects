/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:05:32 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/22 16:41:48 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	total_operations(t_program *p)
{
	t_stats	*s;

	s = &p->stats;
	return (s->sa + s->sb + s->ss + s->pa + s->pb + s->ra + s->rb + s->rr
		+ s->rra + s->rrb + s->rrr);
}

static void	get_strategy_adaptive(double disorder, char **strategy,
		char **complexity)
{
	*strategy = "Adaptive";
	if (disorder < 0.2)
		*complexity = "O(n²)";
	else if (disorder < 0.5)
		*complexity = "O(n√n)";
	else
		*complexity = "O(n log n)";
}

void	get_strategy(t_program *p, double disorder, char **strategy,
		char **complexity)
{
	if (p->flags.simple && !p->flags.medium && !p->flags.complex
		&& !p->flags.adaptive)
	{
		*strategy = "Simple";
		*complexity = "O(n²)";
	}
	else if (p->flags.medium && !p->flags.simple && !p->flags.complex
		&& !p->flags.adaptive)
	{
		*strategy = "Medium";
		*complexity = "O(n√n)";
	}
	else if (p->flags.complex && !p->flags.simple && !p->flags.medium
		&& !p->flags.adaptive)
	{
		*strategy = "Complex";
		*complexity = "O(n log n)";
	}
	else
		get_strategy_adaptive(disorder, strategy, complexity);
}

static void	print_ops(t_program *p)
{
	t_stats	*s;

	s = &p->stats;
	ft_printf("[bench] total_ops: %d\n", total_operations(p));
	ft_printf("[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n", s->sa, s->sb,
		s->ss, s->pa, s->pb);
	ft_printf("[bench] ra: %d rb: %d rr: %d rra: %d rrb: %d rrr: %d\n", s->ra,
		s->rb, s->rr, s->rra, s->rrb, s->rrr);
}

void	print_bench(t_program *p, double disorder)
{
	char	*strategy;
	char	*complexity;
	int		whole;
	int		frac;

	get_strategy(p, disorder, &strategy, &complexity);
	disorder *= 100;
	whole = (int)disorder;
	frac = (int)((disorder - whole) * 100);
	ft_printf("[bench] disorder: %d.%d%%\n", whole, frac);
	ft_printf("[bench] strategy: %s / %s\n", strategy, complexity);
	print_ops(p);
}
