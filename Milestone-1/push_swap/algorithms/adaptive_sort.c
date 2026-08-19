/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 22:24:47 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/21 17:15:55 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_sort(t_program *p, double disorder)
{
	if (disorder < 0.2)
		simple_sort(p);
	else if (disorder < 0.5)
		medium_sort(p);
	else
		complex_sort(p);
}
