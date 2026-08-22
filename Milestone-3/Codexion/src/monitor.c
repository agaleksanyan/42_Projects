/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:48 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:28:49 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_burnout(t_sim *sim, int *burned_id)
{
	int		i;
	long	now;

	i = 0;
	now = get_time_ms();
	while (i < sim->settings.num_coders)
	{
		if (now - sim->coders[i].last_compile_start
			>= sim->settings.time_to_burnout)
		{
			*burned_id = sim->coders[i].id;
			sim->stop_flag = 1;
			pthread_cond_broadcast(&sim->arbiter_cond);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_sim	*sim;
	int		burned_id;
	int		should_log;

	sim = (t_sim *)arg;
	while (1)
	{
		burned_id = 0;
		pthread_mutex_lock(&sim->arbiter_mutex);
		should_log = 0;
		if (!sim->stop_flag)
			should_log = check_burnout(sim, &burned_id);
		if (sim->stop_flag && !should_log)
		{
			pthread_mutex_unlock(&sim->arbiter_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&sim->arbiter_mutex);
		if (should_log)
		{
			log_message(sim, burned_id, "burned out");
			return (NULL);
		}
		usleep(1000);
	}
}
