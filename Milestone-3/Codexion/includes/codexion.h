/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleksa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 14:28:10 by agaleksa          #+#    #+#             */
/*   Updated: 2026/07/02 23:01:25 by agaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_settings
{
	int				num_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				num_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
}					t_settings;

typedef struct s_request
{
	int				coder_id;
	long			arrival_time;
	long			deadline;
}					t_request;

typedef struct s_dongle
{
	int				id;
	int				is_available;
	long			last_release_time;
	t_request		*heap;
	int				heap_size;
	int				heap_capacity;
}					t_dongle;

typedef struct s_coder
{
	int				id;
	t_dongle		*left;
	t_dongle		*right;
	long			last_compile_start;
	int				compiles_done;
	struct s_sim	*sim;
}					t_coder;

typedef struct s_sim
{
	t_settings		settings;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	arbiter_mutex;
	pthread_cond_t	arbiter_cond;
	long			sim_start_time;
	int				stop_flag;
	int				full_coders;
}					t_sim;

/* parsing.c */
int					is_valid_number(char *str);
int					parse_one_number(char *str, int *out, int min_allowed,
						char *param_name);
int					parse_arguments(int ac, char **av, t_settings *settings);

/* time_utils.c */
long				get_time_ms(void);
long				get_elapsed_time(t_sim *sim);
void				fill_timeout_ms(struct timespec *timeout, int delay_ms);

/* logging.c */
void				log_message(t_sim *sim, int coder_id, char *message);

/* dongle.c */
int					take_two_dongles(t_coder *coder);
void				release_two_dongles(t_coder *coder);

/* dongle_utils.c */
int					can_take_two(t_coder *coder, long now);
int					push_request(t_coder *coder, t_request request);
int					dongle_ready(t_dongle *dongle, t_settings *settings,
						long now);

/* scheduler.c */
int					scheduler_push(t_sim *sim, t_dongle *dongle,
						t_request request);
void				scheduler_remove(t_sim *sim, t_dongle *dongle,
						int coder_id);
int					scheduler_top_is(t_dongle *dongle, int coder_id);
void				scheduler_heap_up(t_sim *sim, t_dongle *dongle, int index);
void				scheduler_heap_down(t_sim *sim, t_dongle *dongle,
						int index);

/* coder.c */
void				*coder_thread(void *arg);

/* monitor.c */
void				*monitor_thread(void *arg);

/* init.c */
int					init_sim(t_sim *sim);
int					init_dongles(t_sim *sim);
int					init_coders(t_sim *sim);

/* cleanup.c */
void				cleanup(t_sim *sim);
void				cleanup_sim_init(t_sim *sim, int stage);

/* simulation.c */
void				stop_simulation(t_sim *sim);
int					start_threads(t_sim *sim, int *created);
void				join_threads(t_sim *sim, int created, int has_monitor);
int					run_simulation(t_sim *sim);

#endif
