/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:30:44 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 14:30:45 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	request_before(t_sim *sim, t_request a, t_request b)
{
	if (strcmp(sim->settings.scheduler, "edf") == 0)
	{
		if (a.deadline != b.deadline)
			return (a.deadline < b.deadline);
	}
	if (a.arrival_time != b.arrival_time)
		return (a.arrival_time < b.arrival_time);
	return (a.coder_id < b.coder_id);
}

static void	swap_requests(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	scheduler_heap_up(t_sim *sim, t_dongle *dongle, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!request_before(sim, dongle->heap[index], dongle->heap[parent]))
			return ;
		swap_requests(&dongle->heap[index], &dongle->heap[parent]);
		index = parent;
	}
}

void	scheduler_heap_down(t_sim *sim, t_dongle *dongle, int index)
{
	int	left;
	int	right;
	int	best;

	while (1)
	{
		left = index * 2 + 1;
		right = left + 1;
		best = index;
		if (left < dongle->heap_size
			&& request_before(sim, dongle->heap[left], dongle->heap[best]))
			best = left;
		if (right < dongle->heap_size
			&& request_before(sim, dongle->heap[right], dongle->heap[best]))
			best = right;
		if (best == index)
			return ;
		swap_requests(&dongle->heap[index], &dongle->heap[best]);
		index = best;
	}
}
