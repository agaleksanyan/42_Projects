/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:40 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 17:30:55 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	free_dongle_heaps(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(sim->dongles[i].heap);
		i++;
	}
	free(sim->dongles);
	sim->dongles = NULL;
}

static int	init_one_dongle(t_sim *sim, int i)
{
	sim->dongles[i].id = i;
	sim->dongles[i].is_available = 1;
	sim->dongles[i].last_release_time = 0;
	sim->dongles[i].heap_size = 0;
	sim->dongles[i].heap_capacity = sim->settings.num_coders;
	sim->dongles[i].heap = malloc(sizeof(t_request)
			* sim->settings.num_coders);
	if (!sim->dongles[i].heap)
		return (0);
	return (1);
}

int	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->settings.num_coders);
	if (!sim->dongles)
		return (0);
	i = 0;
	while (i < sim->settings.num_coders)
	{
		if (!init_one_dongle(sim, i))
		{
			free_dongle_heaps(sim, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_coders(t_sim *sim)
{
	int	i;

	sim->coders = malloc(sizeof(t_coder) * sim->settings.num_coders);
	if (!sim->coders)
		return (0);
	i = 0;
	while (i < sim->settings.num_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].left = &sim->dongles[i];
		sim->coders[i].right = &sim->dongles[(i + 1)
			% sim->settings.num_coders];
		sim->coders[i].last_compile_start = 0;
		sim->coders[i].compiles_done = 0;
		sim->coders[i].sim = sim;
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim)
{
	int	i;

	sim->coders = NULL;
	sim->dongles = NULL;
	sim->threads = NULL;
	sim->full_coders = 0;
	if (!init_dongles(sim))
		return (0);
	if (!init_coders(sim))
		return (cleanup_sim_init(sim, 1), 0);
	sim->threads = malloc(sizeof(pthread_t) * sim->settings.num_coders);
	if (!sim->threads)
		return (cleanup_sim_init(sim, 2), 0);
	if (pthread_mutex_init(&sim->log_mutex, NULL))
		return (cleanup_sim_init(sim, 3), 0);
	if (pthread_mutex_init(&sim->arbiter_mutex, NULL))
		return (cleanup_sim_init(sim, 4), 0);
	if (pthread_cond_init(&sim->arbiter_cond, NULL))
		return (cleanup_sim_init(sim, 5), 0);
	sim->sim_start_time = get_time_ms();
	sim->stop_flag = 0;
	i = 0;
	while (i < sim->settings.num_coders)
		sim->coders[i++].last_compile_start = sim->sim_start_time;
	return (1);
}
