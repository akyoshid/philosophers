/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/24 09:00:50 by akyoshid         ###   ########.fr       */
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

typedef enum e_exit_status
{
	PHILO_SUCCESS,
	PHILO_GENERAL_ERROR,
	PHILO_SYNTAX_ERROR,
}	t_exit_status;

typedef enum e_error_code
{
	ERR_ARGC,
	ERR_PTHREAD_CREATE,
	ERR_PTHREAD_MUTEX_INIT,
}	t_error_code;

typedef enum e_sim_data_field_num
{
	PHILO_NUM,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	EAT_LIMIT,
}	t_sim_data_field_num;

typedef struct s_flag
{
	bool			stop;
	pthread_mutex_t	m;
}					t_flag;

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
	t_flag			flag;
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
	pthread_t	thread_id;
}				t_philo_data;

// clean_up_mutex.c
void	clean_up_mutex(t_sim_data *sim_data, int fork_count);
// exec_sim.c
int		exec_sim(t_sim_data *sim_data);
// flag.c
void	stop_sim(t_sim_data *sim_data);
int		check_flag(t_sim_data *sim_data);
// get_current_time_ms.c
long	get_current_time_ms(void);
// init_mutex.c
int		init_mutex(t_sim_data *sim_data);
// init_sim_data.c
int		init_sim_data(int argc, char *argv[], t_sim_data *sim_data);
// philo_atoi.c
int		philo_atoi(char const *str);
// print_error.c
void	print_error(int error_code);
// start_philo_routine.c
void	*start_philo_routine(void *arg);

#endif
