/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaghate <ssaghate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:15:48 by ssaghate          #+#    #+#             */
/*   Updated: 2026/03/23 18:29:39 by ssaghate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "bonus/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}					t_node;

typedef struct s_stats
{
	int				sa;
	int				sb;
	int				ss;
	int				pa;
	int				pb;
	int				ra;
	int				rb;
	int				rr;
	int				rra;
	int				rrb;
	int				rrr;
}					t_stats;

typedef struct s_flags
{
	int				bench_mode;
	int				checker_mode;
	int				simple;
	int				medium;
	int				complex;
	int				adaptive;
	int				start;
}					t_flags;

typedef struct s_program
{
	t_node			*a;
	t_node			*b;
	t_stats			stats;
	t_flags			flags;
}					t_program;

int					is_flag(char *arg);
void				parse_flags(int argc, char **argv, t_program *p);
void				parse_arguments(int argc, char **argv, t_program *p,
						int start);
int					is_valid_number(char *str, t_program *p);
int					has_duplicates(t_node *a);
void				free_split(char **arr);
int					is_sorted(t_node *a);
void				index_stack(t_node *a);
t_node				*find_min(t_node *stack);
t_node				*find_max(t_node *stack);
int					get_position(t_node *stack, int value);
void				rotate_to_top(t_program *p, int pos);
int					total_operations(t_program *p);
t_node				*new_node(int value);
void				add_back(t_node **stack, t_node *new);
int					stack_size(t_node *stack);
void				free_stack(t_node **stack);
int					ft_atoi_safe(const char *str, t_program *p);
void				swap_nodes(t_node **stack);
void				push_nodes(t_node **from, t_node **to);
void				rotate_nodes(t_node **stack);
void				rev_rotate_nodes(t_node **stack);
void				sa(t_program *p);
void				sb(t_program *p);
void				ss(t_program *p);
void				pa(t_program *p);
void				pb(t_program *p);
void				ra(t_program *p);
void				rb(t_program *p);
void				rr(t_program *p);
void				rra(t_program *p);
void				rrb(t_program *p);
void				rrr(t_program *p);
double				compute_disorder(t_node *a);
void				simple_sort(t_program *p);
void				sort_2(t_program *p);
void				sort_3(t_program *p);
void				sort_4(t_program *p);
void				sort_5(t_program *p);
void				medium_sort(t_program *p);
void				complex_sort(t_program *p);
void				adaptive_sort(t_program *p, double disorder);
void				prepare_index(t_program *p, int *bits);
void				radix_pass(t_program *p, int size, int bit);
void				error_exit(t_program *p);
void				print_bench(t_program *p, double disorder);
void				handle_flag(char *arg, t_program *p);

#endif