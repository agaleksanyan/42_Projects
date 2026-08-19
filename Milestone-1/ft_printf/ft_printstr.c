/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:55:32 by agaleksa          #+#    #+#             */
/*   Updated: 2026/02/14 19:32:00 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printstr(char *s)
{
    int len;

    if (!s)
    {
        ft_putstr_fd("(null)", 1);
        return (6);
    }
    len = ft_strlen(s);
    ft_putstr_fd(s, 1);
    return(len);
}
