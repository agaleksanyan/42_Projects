/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:29:49 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/14 20:30:53 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list args;
    int     i;
    int     count;

    i = 0;
    count = 0;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')
                count += ft_printchar(va_arg(args, int));
            else if (format[i] == 's')
                count += ft_printstr(va_arg(args, char *));
            else if (format[i] == 'd' || format[i] == 'i')
                count += ft_printnbr(va_arg(args, int));
            else if (format[i] == 'u')
                count += ft_print_unsigned(va_arg(args, unsigned int));
            else if (format[i] == 'x' || format[i] == 'X')
                count += ft_print_hex(va_arg(args, unsigned int), format[i]);
            else if (format[i] == 'p')
                count += ft_print_ptr(va_arg(args, void *));
            else if (format[i] == '%')
                count += ft_printchar('%');
            i++;
        }
        else
        {
            count += ft_printchar(format[i]);
            i++;
        }
    }
    va_end(args);
    return (count);
}