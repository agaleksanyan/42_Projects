/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:45:09 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/23 16:26:27 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	choose_sort(t_program *p, double disorder)
{
	if (p->flags.simple && !p->flags.medium && !p->flags.complex
		&& !p->flags.adaptive)
		simple_sort(p);
	else if (!p->flags.simple && p->flags.medium && !p->flags.complex
		&& !p->flags.adaptive)
		medium_sort(p);
	else if (!p->flags.simple && !p->flags.medium && p->flags.complex
		&& !p->flags.adaptive)
		complex_sort(p);
	else
		adaptive_sort(p, disorder);
}

static int	handle_sorted(t_program *p)
{
	if (is_sorted(p->a))
	{
		if (!p->flags.bench_mode)
			free_stack(&p->a);
		else
			print_bench(p, 0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	p;
	double		disorder;

	ft_bzero(&p, sizeof(p));
	parse_flags(argc, argv, &p);
	parse_arguments(argc, argv, &p, p.flags.start);
	disorder = compute_disorder(p.a);
	if (handle_sorted(&p))
		return (0);
	choose_sort(&p, disorder);
	if (p.flags.bench_mode)
		print_bench(&p, disorder);
	free_stack(&p.a);
	return (0);
}
