/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/25 22:08:57 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "ft_printf.h"

# define PHILO_NUM_LIMIT 200

enum e_exit_status
{
	PHILO_SUCCESS,
	PHILO_GENERAL_ERROR,
	PHILO_SYNTAX_ERROR,
};

enum e_error_code
{
	ERR_ARGC,
	ERR_PTHREAD_CREATE,
	ERR_PTHREAD_MUTEX_INIT,
};

enum e_sim_data_field_num
{
	PHILO_NUM,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	EAT_LIMIT,
};

enum e_action
{
	ACTION_TAKE_FORK,
	ACTION_EAT,
	ACTION_SLEEP,
	ACTION_THINK,
};

enum e_status
{
	STATUS_SUCCESS,
	STATUS_STOP,
	STATUS_FAILURE,
	STATUS_CONTINUE,
};

typedef struct s_super_flag
{
	bool			stop_flag;
	pthread_mutex_t	m;
}					t_super_flag;

typedef struct s_fork
{
	int				last_user_num;
	pthread_mutex_t	m;
}					t_fork;

typedef struct s_sim_data
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_limit;
	t_super_flag	super_flag;
	t_fork			fork[PHILO_NUM_LIMIT];
	long			start_time;
}					t_sim_data;

typedef struct s_philo_data
{
	int			philo_id;
	t_sim_data	*sim_data;
	t_fork		*first_fork;
	t_fork		*second_fork;
	int			first_think_time;
	long		last_eat_timestamp;
	pthread_t	thread_id;
}				t_philo_data;

// check_action_status.c
int		check_action_status(
			t_philo_data *philo_data, long start_timestamp, int timelimit);
// check_alive.c
int		check_alive(
			t_philo_data *philo_data, bool have_super_flag, long timestamp);
// clean_up_mutex.c
void	clean_up_mutex(t_sim_data *sim_data, int fork_count);
// exec_sim.c
int		exec_sim(t_sim_data *sim_data);
// get_current_time_ms.c
long	get_current_time_ms(void);
long	get_timestamp(t_sim_data *sim_data);
// init_mutex.c
int		init_mutex(t_sim_data *sim_data);
// init_sim_data.c
int		init_sim_data(int argc, char *argv[], t_sim_data *sim_data);
// philo_atoi.c
int		philo_atoi(char const *str);
// philo_eat.c
int		philo_eat(t_philo_data *philo_data);
// philo_sleep.c
int		philo_sleep(t_philo_data *philo_data);
// print_error.c
void	print_error(int error_code);
// print_log.c
int		print_log(t_philo_data *philo_data, int action, long *timestamp_p);
// start_philo_routine.c
void	*start_philo_routine(void *arg);

#endif
