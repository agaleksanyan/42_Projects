/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:04:46 by agaleksa          #+#    #+#             */
/*   Updated: 2026/03/21 16:33:23 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(char *str, t_program *p)
{
	int	i;

	(void)p;
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '0' && str[i + 1])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_safe(const char *str, t_program *p)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (!str || !*str)
		error_exit(p);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		error_exit(p);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			error_exit(p);
		num = num * 10 + (*str - '0');
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			error_exit(p);
		str++;
	}
	return ((int)(num * sign));
}

int	has_duplicates(t_node *a)
{
	t_node	*current;
	t_node	*compare;

	current = a;
	while (current)
	{
		compare = current->next;
		while (compare)
		{
			if (current->value == compare->value)
				return (1);
			compare = compare->next;
		}
		current = current->next;
	}
	return (0);
}
