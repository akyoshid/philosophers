/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/08 20:29:31 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

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
	ERR_SEM_OPEN,
	ERR_FORK,
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
	bool	start_flag;
	bool	stop_flag;
	int		philo_count_reached_eat_limit;
	sem_t	*s;
}			t_super_flag;

typedef struct s_fork
{
	sem_t	*s;
}			t_fork;

typedef struct s_timestamp
{
	long	timestamp;
	sem_t	*s;
}			t_timestamp;

typedef struct s_sim_data
{
	int				philo_num;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				eat_limit;
	t_super_flag	super_flag;
	t_fork			fork;
	t_philo_data	philo_data[PHILO_NUM_LIMIT];
	long			start_time;
}					t_sim_data;

typedef struct s_philo_data
{
	int			philo_id;
	t_timestamp	last_eat_timestamp;
	int			eat_count;
	pid_t		pid;
}				t_philo_data;

// before_start_sim_utils.c
int		check_super_flag(t_sim_data *sim_data);
void	start_sim(t_sim_data *sim_data);
// check_action_status.c
int		check_action_status(
			t_philo_data *philo_data, long start_timestamp, long timelimit);
// check_alive.c
int		check_alive(
			t_philo_data *philo_data, bool have_super_flag, long timestamp);
// check_eat_count.c
int		check_eat_count(t_philo_data *philo_data, t_sim_data *sim_data);
// clean_up_semaphore.c
void	clean_up_semaphore(t_sim_data *sim_data, int philo_count);
// exec_sim.c
int		exec_sim(t_sim_data *sim_data);
// ft_strncpy.c
char	*ft_strncpy(char *dest, char *src, unsigned int n);
// get_current_time.c
long	get_current_time(void);
long	get_timestamp(t_sim_data *sim_data);
// init_semaphore.c
int		init_semaphore(t_sim_data *sim_data);
// init_sim_data.c
int		init_sim_data(int argc, char *argv[], t_sim_data *sim_data);
// philo_atoi.c
int		philo_atoi(char const *str);
// philo_eat.c
int		philo_eat(t_philo_data *philo_data);
void	solo_philo_take_fork_and_die(t_philo_data *philo_data);
// philo_sleep.c
int		philo_sleep(t_philo_data *philo_data);
// philo_think.c
int		philo_think(t_philo_data *philo_data);
int		philo_first_think(t_philo_data *philo_data);
// print_error.c
void	print_error(int error_code);
// print_log.c
int		print_log(t_philo_data *philo_data, int action, long *timestamp_p);
// start_philo_routine.c
void	*start_philo_routine(void *arg);

#endif
