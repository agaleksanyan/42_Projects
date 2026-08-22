/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 22:36:50 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 22:43:53 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	stop_simulation(t_sim *sim)
{
	pthread_mutex_lock(&sim->arbiter_mutex);
	sim->stop_flag = 1;
	pthread_cond_broadcast(&sim->arbiter_cond);
	pthread_mutex_unlock(&sim->arbiter_mutex);
}

int	start_threads(t_sim *sim, int *created)
{
	int	i;

	i = 0;
	*created = 0;
	while (i < sim->settings.num_coders)
	{
		if (pthread_create(&sim->threads[i], NULL, coder_thread,
				&sim->coders[i]) != 0)
		{
			stop_simulation(sim);
			return (0);
		}
		(*created)++;
		i++;
	}
	if (pthread_create(&sim->monitor, NULL, monitor_thread, sim) != 0)
	{
		stop_simulation(sim);
		return (0);
	}
	return (1);
}

void	join_threads(t_sim *sim, int created, int has_monitor)
{
	int	i;

	i = 0;
	while (i < created)
		pthread_join(sim->threads[i++], NULL);
	if (has_monitor)
		pthread_join(sim->monitor, NULL);
}

int	run_simulation(t_sim *sim)
{
	int	created;
	int	has_monitor;

	if (sim->settings.num_compiles_required == 0)
		return (0);
	has_monitor = 0;
	if (!start_threads(sim, &created))
	{
		join_threads(sim, created, has_monitor);
		return (1);
	}
	has_monitor = 1;
	join_threads(sim, created, has_monitor);
	return (0);
}
