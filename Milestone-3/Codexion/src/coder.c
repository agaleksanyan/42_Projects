/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:33 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:28:34 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->arbiter_mutex);
	stopped = sim->stop_flag;
	pthread_mutex_unlock(&sim->arbiter_mutex);
	return (stopped);
}

static void	sleep_interruptible(t_sim *sim, int duration_ms)
{
	long	end_time;

	end_time = get_time_ms() + duration_ms;
	while (!is_stopped(sim) && get_time_ms() < end_time)
		usleep(500);
}

static void	update_compile_count(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->arbiter_mutex);
	coder->compiles_done++;
	if (coder->compiles_done == sim->settings.num_compiles_required)
	{
		sim->full_coders++;
		if (sim->full_coders == sim->settings.num_coders)
		{
			sim->stop_flag = 1;
			pthread_cond_broadcast(&sim->arbiter_cond);
		}
	}
	pthread_mutex_unlock(&sim->arbiter_mutex);
}

static void	start_compile(t_coder *coder)
{
	log_message(coder->sim, coder->id, "is compiling");
}

void	*coder_thread(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	if (coder->id % 2 == 0)
		usleep(500);
	while (!is_stopped(sim))
	{
		if (!take_two_dongles(coder))
			break ;
		start_compile(coder);
		sleep_interruptible(sim, sim->settings.time_to_compile);
		release_two_dongles(coder);
		update_compile_count(coder);
		if (is_stopped(sim))
			break ;
		log_message(sim, coder->id, "is debugging");
		sleep_interruptible(sim, sim->settings.time_to_debug);
		if (is_stopped(sim))
			break ;
		log_message(sim, coder->id, "is refactoring");
		sleep_interruptible(sim, sim->settings.time_to_refactor);
	}
	return (NULL);
}
