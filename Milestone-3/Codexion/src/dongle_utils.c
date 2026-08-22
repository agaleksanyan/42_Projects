/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 22:57:09 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 22:58:58 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	can_take_two(t_coder *coder, long now)
{
	if (coder->left == coder->right)
		return (0);
	if (!scheduler_top_is(coder->left, coder->id))
		return (0);
	if (!scheduler_top_is(coder->right, coder->id))
		return (0);
	if (!dongle_ready(coder->left, &coder->sim->settings, now))
		return (0);
	return (dongle_ready(coder->right, &coder->sim->settings, now));
}

int	dongle_ready(t_dongle *dongle, t_settings *settings, long now)
{
	if (!dongle->is_available)
		return (0);
	return (now - dongle->last_release_time >= settings->dongle_cooldown);
}

int	push_request(t_coder *coder, t_request request)
{
	if (!scheduler_push(coder->sim, coder->left, request))
		return (0);
	if (!scheduler_push(coder->sim, coder->right, request))
	{
		scheduler_remove(coder->sim, coder->left, coder->id);
		return (0);
	}
	return (1);
}
