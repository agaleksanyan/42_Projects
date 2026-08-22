/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:37 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 22:58:35 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	handle_single_dongle(t_coder *coder)
{
	struct timespec	timeout;

	while (!coder->sim->stop_flag)
	{
		fill_timeout_ms(&timeout, 1);
		pthread_cond_timedwait(&coder->sim->arbiter_cond,
			&coder->sim->arbiter_mutex, &timeout);
	}
	pthread_mutex_unlock(&coder->sim->arbiter_mutex);
	return (0);
}

static int	register_request(t_coder *coder)
{
	t_request	request;

	request.coder_id = coder->id;
	request.arrival_time = get_time_ms();
	request.deadline = coder->last_compile_start
		+ coder->sim->settings.time_to_burnout;
	if (!push_request(coder, request))
	{
		coder->sim->stop_flag = 1;
		pthread_cond_broadcast(&coder->sim->arbiter_cond);
		pthread_mutex_unlock(&coder->sim->arbiter_mutex);
		return (0);
	}
	return (1);
}

static int	wait_for_dongles(t_coder *coder)
{
	struct timespec	timeout;

	while (!coder->sim->stop_flag && !can_take_two(coder, get_time_ms()))
	{
		fill_timeout_ms(&timeout, 1);
		pthread_cond_timedwait(&coder->sim->arbiter_cond,
			&coder->sim->arbiter_mutex, &timeout);
	}
	if (coder->sim->stop_flag)
	{
		scheduler_remove(coder->sim, coder->left, coder->id);
		scheduler_remove(coder->sim, coder->right, coder->id);
		pthread_mutex_unlock(&coder->sim->arbiter_mutex);
		return (0);
	}
	return (1);
}

int	take_two_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->arbiter_mutex);
	if (coder->left == coder->right)
		return (handle_single_dongle(coder));
	if (!register_request(coder))
		return (0);
	if (!wait_for_dongles(coder))
		return (0);
	scheduler_remove(coder->sim, coder->left, coder->id);
	scheduler_remove(coder->sim, coder->right, coder->id);
	coder->left->is_available = 0;
	coder->right->is_available = 0;
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->sim->arbiter_mutex);
	log_message(coder->sim, coder->id, "has taken a dongle");
	log_message(coder->sim, coder->id, "has taken a dongle");
	return (1);
}

void	release_two_dongles(t_coder *coder)
{
	long	now;

	pthread_mutex_lock(&coder->sim->arbiter_mutex);
	now = get_time_ms();
	coder->left->is_available = 1;
	coder->left->last_release_time = now;
	coder->right->is_available = 1;
	coder->right->last_release_time = now;
	pthread_cond_broadcast(&coder->sim->arbiter_cond);
	pthread_mutex_unlock(&coder->sim->arbiter_mutex);
}
