/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:17:13 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/14 19:31:43 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_print_hex(unsigned int n, char   format)
{
    char    *digits;
    int     count;

    if (format == 'x')
        digits = "0123456789abcdef";
    if (format == 'X')
        digits = "0123456789ABCDEF";
    count = 0;
    if (n >= 16)
        count += ft_print_hex(n / 16, format);
    ft_putchar_fd(digits[n % 16], 1);
    count++;
    return (count);
}