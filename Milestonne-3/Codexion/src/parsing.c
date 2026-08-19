/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:53 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 16:54:44 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_valid_number(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	parse_one_number(char *str, int *out, int min_allowed, char *param_name)
{
	int	res;

	if (!is_valid_number(str))
	{
		fprintf(stderr,
			"Error: %s must be a valid non-negative integer\n", param_name);
		return (0);
	}
	res = atoi(str);
	if (res < min_allowed)
	{
		fprintf(stderr,
			"Error: %s must be >= %d (got %d)\n", param_name,
			min_allowed, res);
		return (0);
	}
	*out = res;
	return (1);
}

static int	parse_required(char **av, t_settings *s)
{
	int	i;

	i = 1;
	if (!parse_one_number(av[i++], &s->num_coders, 1, "number_of_coders"))
		return (0);
	if (!parse_one_number(av[i++], &s->time_to_burnout, 0, "time_to_burnout"))
		return (0);
	if (!parse_one_number(av[i++], &s->time_to_compile, 0, "time_to_compile"))
		return (0);
	if (!parse_one_number(av[i++], &s->time_to_debug, 0, "time_to_debug"))
		return (0);
	return (i);
}

static int	parse_optional(char **av, t_settings *s, int i)
{
	if (!parse_one_number(av[i++], &s->time_to_refactor, 0, "time_to_refactor"))
		return (0);
	if (!parse_one_number(av[i++], &s->num_compiles_required, 0,
			"number_of_compiles_required"))
		return (0);
	if (!parse_one_number(av[i++], &s->dongle_cooldown, 0, "dongle_cooldown"))
		return (0);
	if (strcmp(av[8], "fifo") == 0 || strcmp(av[8], "edf") == 0)
		s->scheduler = av[8];
	else
	{
		fprintf(stderr, "Error: scheduler must be 'fifo' or 'edf'\n");
		return (0);
	}
	return (1);
}

int	parse_arguments(int ac, char **av, t_settings *settings)
{
	int	i;

	(void)ac;
	i = parse_required(av, settings);
	if (!i)
		return (0);
	return (parse_optional(av, settings, i));
}
