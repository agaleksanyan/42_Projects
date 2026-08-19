/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:01:18 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/14 20:34:35 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printnbr(int n)
{
    long    nb;
    int     count;

    nb = n;
    count = 0;
    if (nb < 0)
    {
        ft_putchar_fd('-', 1);
        count++;
        nb = -nb;
    }
    if (nb >= 10)
        count += ft_printnbr(nb / 10);
    ft_putchar_fd((nb % 10) + '0', 1);
    count++;
    return (count);
}