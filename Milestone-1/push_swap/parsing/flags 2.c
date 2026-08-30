/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:37:03 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/22 16:47:49 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(char *arg)
{
	if (!ft_strcmp(arg, "--bench"))
		return (1);
	if (!ft_strcmp(arg, "--simple"))
		return (1);
	if (!ft_strcmp(arg, "--medium"))
		return (1);
	if (!ft_strcmp(arg, "--complex"))
		return (1);
	if (!ft_strcmp(arg, "--adaptive"))
		return (1);
	return (0);
}

static int	no_algo_selected(t_program *p)
{
	return (!p->flags.simple && !p->flags.medium && !p->flags.complex
		&& !p->flags.adaptive);
}

static int	no_bench_selected(t_program *p)
{
	return (!p->flags.bench_mode);
}

void	handle_flag(char *arg, t_program *p)
{
	if (!ft_strcmp(arg, "--bench") && no_bench_selected(p))
		p->flags.bench_mode = 1;
	else if (!ft_strcmp(arg, "--simple") && no_algo_selected(p))
		p->flags.simple = 1;
	else if (!ft_strcmp(arg, "--medium") && no_algo_selected(p))
		p->flags.medium = 1;
	else if (!ft_strcmp(arg, "--complex") && no_algo_selected(p))
		p->flags.complex = 1;
	else if (!ft_strcmp(arg, "--adaptive") && no_algo_selected(p))
		p->flags.adaptive = 1;
	else if (is_flag(arg))
		error_exit(p);
}

void	parse_flags(int argc, char **argv, t_program *p)
{
	int	i;

	p->flags.bench_mode = 0;
	p->flags.simple = 0;
	p->flags.medium = 0;
	p->flags.complex = 0;
	p->flags.adaptive = 0;
	p->flags.start = 1;
	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			handle_flag(argv[i], p);
		i++;
	}
}
