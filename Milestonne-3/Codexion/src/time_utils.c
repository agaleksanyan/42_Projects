/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:30:49 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:30:50 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_elapsed_time(t_sim *sim)
{
	return (get_time_ms() - sim->sim_start_time);
}

void	fill_timeout_ms(struct timespec *timeout, int delay_ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	timeout->tv_sec = now.tv_sec + delay_ms / 1000;
	timeout->tv_nsec = (now.tv_usec * 1000)
		+ ((delay_ms % 1000) * 1000000);
	if (timeout->tv_nsec >= 1000000000)
	{
		timeout->tv_sec++;
		timeout->tv_nsec -= 1000000000;
	}
}
