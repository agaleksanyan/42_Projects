/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:31 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 17:30:46 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup(t_sim *sim)
{
	int	i;

	i = 0;
	while (sim->dongles && i < sim->settings.num_coders)
	{
		free(sim->dongles[i].heap);
		sim->dongles[i].heap = NULL;
		i++;
	}
	free(sim->coders);
	sim->coders = NULL;
	free(sim->dongles);
	sim->dongles = NULL;
	free(sim->threads);
	sim->threads = NULL;
	pthread_mutex_destroy(&sim->arbiter_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_cond_destroy(&sim->arbiter_cond);
}

void	cleanup_sim_init(t_sim *sim, int stage)
{
	int	i;

	if (stage >= 4)
		pthread_mutex_destroy(&sim->arbiter_mutex);
	if (stage >= 3)
		pthread_mutex_destroy(&sim->log_mutex);
	if (stage >= 2)
		free(sim->threads);
	if (stage >= 1)
		free(sim->coders);
	i = 0;
	while (sim->dongles && i < sim->settings.num_coders)
		free(sim->dongles[i++].heap);
	free(sim->dongles);
	sim->dongles = NULL;
	sim->coders = NULL;
	sim->threads = NULL;
}
