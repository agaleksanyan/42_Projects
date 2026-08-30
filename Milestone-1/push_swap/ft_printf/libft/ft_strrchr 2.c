/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:47 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/18 18:21:48 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	v;
	int		i;

	v = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == v)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
