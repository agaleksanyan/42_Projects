/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:45 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 22:40:44 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_usage(char *program_name, int got)
{
	fprintf(stderr, "Error: expected 8 arguments, got %d\n", got);
	fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
		"time_to_compile time_to_debug time_to_refactor "
		"number_of_compiles_required dongle_cooldown scheduler\n",
		program_name);
}

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac != 9)
		return (print_usage(av[0], ac - 1), 1);
	if (!parse_arguments(ac, av, &sim.settings))
		return (1);
	if (!init_sim(&sim))
		return (1);
	if (run_simulation(&sim))
	{
		cleanup(&sim);
		return (1);
	}
	cleanup(&sim);
	return (0);
}
