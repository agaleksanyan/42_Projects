/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:20:50 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:20:51 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	v;

	v = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == v)
			return ((char *)&s[i]);
		i++;
	}
	if (v == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
