/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:11:25 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/14 19:31:36 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_print_unsigned(unsigned int n)
{
    int count;
    
    count = 0;
    if (n >= 10)
        count += ft_print_unsigned(n / 10);
    ft_putchar_fd((n % 10) + '0', 1);
    count++;
    return(count);
}