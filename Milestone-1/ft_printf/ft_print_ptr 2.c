/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:25:18 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/28 19:01:35 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_ul(unsigned long n)
{
	char			*digits;
	int				count;

	digits = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_print_hex_ul(n / 16);
	ft_putchar_fd(digits[n % 16], 1);
	count++;
	return (count);
}

int ft_putstr(char *s)
{
    int len = 0;

    if (!s)
        s = "(null)";
    while (s[len])
        write(1, &s[len++], 1);
    return len;
}

int ft_print_ptr(void *ptr)
{
    unsigned long   addres;
    int             count;
    
    count = 0;
    if (!ptr)
        return (ft_putstr_fd("(nil)", 1), 5);
    addres = (unsigned long)ptr;
    count += ft_putstr("0x");
    count += ft_print_hex_ul(addres);
    return (count);
}
