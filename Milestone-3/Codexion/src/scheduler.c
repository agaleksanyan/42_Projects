/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:30:46 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:30:47 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	scheduler_push(t_sim *sim, t_dongle *dongle, t_request request)
{
	if (dongle->heap_size >= dongle->heap_capacity)
		return (0);
	dongle->heap[dongle->heap_size] = request;
	scheduler_heap_up(sim, dongle, dongle->heap_size);
	dongle->heap_size++;
	return (1);
}

void	scheduler_remove(t_sim *sim, t_dongle *dongle, int coder_id)
{
	int	i;

	i = 0;
	while (i < dongle->heap_size)
	{
		if (dongle->heap[i].coder_id == coder_id)
		{
			dongle->heap_size--;
			dongle->heap[i] = dongle->heap[dongle->heap_size];
			scheduler_heap_down(sim, dongle, i);
			scheduler_heap_up(sim, dongle, i);
			return ;
		}
		i++;
	}
}

int	scheduler_top_is(t_dongle *dongle, int coder_id)
{
	if (dongle->heap_size == 0)
		return (0);
	return (dongle->heap[0].coder_id == coder_id);
}
