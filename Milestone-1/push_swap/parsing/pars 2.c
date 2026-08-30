/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 16:11:12 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/22 16:13:55 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(t_program *p)
{
	if (p)
	{
		if (p->a)
			free_stack(&p->a);
		if (p->b)
			free_stack(&p->b);
	}
	write(2, "Error\n", 6);
	exit(1);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	process_number(char *str, t_program *p)
{
	int	value;

	if (!is_valid_number(str, p))
		error_exit(p);
	value = ft_atoi_safe(str, p);
	add_back(&p->a, new_node(value));
}

static void	process_argument(char *arg, t_program *p)
{
	char	**nums;
	int		j;

	nums = ft_split(arg, ' ');
	if (!nums)
		error_exit(p);
	j = 0;
	while (nums[j])
	{
		if (is_flag(nums[j]))
		{
			handle_flag(nums[j], p);
			j++;
			continue ;
		}
		else
			process_number(nums[j], p);
		j++;
	}
	free_split(nums);
}

void	parse_arguments(int argc, char **argv, t_program *p, int start)
{
	int	i;

	i = start;
	while (i < argc)
	{
		if (is_flag(argv[i]))
		{
			i++;
			continue ;
		}
		else
			process_argument(argv[i], p);
		i++;
	}
	if (has_duplicates(p->a))
		error_exit(p);
}
