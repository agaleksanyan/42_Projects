/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:43 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:28:44 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_message(t_sim *sim, int coder_id, char *message)
{
	int	stopped;

	pthread_mutex_lock(&sim->log_mutex);
	pthread_mutex_lock(&sim->arbiter_mutex);
	stopped = sim->stop_flag;
	pthread_mutex_unlock(&sim->arbiter_mutex);
	if (!stopped || strcmp(message, "burned out") == 0)
		printf("%ld %d %s\n", get_elapsed_time(sim), coder_id, message);
	pthread_mutex_unlock(&sim->log_mutex);
}
