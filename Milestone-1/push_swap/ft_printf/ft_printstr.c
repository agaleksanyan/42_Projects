/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:55:32 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:30:29 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *s)
{
	int	len;

	if (!s)
	{
		ft_putstr_fd("(null)", 2);
		return (6);
	}
	len = ft_strlen(s);
	ft_putstr_fd(s, 2);
	return (len);
}
