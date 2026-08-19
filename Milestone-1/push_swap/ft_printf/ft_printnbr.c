/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:01:18 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:30:26 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		ft_putchar_fd('-', 2);
		count++;
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_printnbr(nb / 10);
	ft_putchar_fd((nb % 10) + '0', 2);
	count++;
	return (count);
}
