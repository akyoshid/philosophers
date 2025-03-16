/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/16 08:24:44 by akyoshid         ###   ########.fr       */
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
# define WAITING_TIME_TO_START_SIM 100000

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
	ERR_ADJUST_START_TIME,
};

enum e_sim_data_field_num
{
	PHILO_NUM,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	EAT_LIMIT,
};

enum e_init_sem_status
{
	INIT_SEM_PREPARE_FLAG,
	INIT_SEM_ERROR_FLAG,
	INIT_SEM_START_FLAG,
	INIT_SEM_STOP_FLAG,
	INIT_SEM_PHILO_COUNT_REACHED_EAT_LIMIT,
	INIT_SEM_PRINT_FLAG,
	INIT_SEM_FORK,
	INIT_SEM_PAIR_OF_FORKS,
};

enum e_init_philo_sem_status
{
	INIT_PHILO_SEM_START_DEATH_CHECKER_FLAG,
	INIT_PHILO_SEM_EAT_FLAG,
	INIT_PHILO_SEM_LAST_EAT_TIMESTAMP,
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

typedef struct s_sim_data	t_sim_data;
typedef struct s_philo_data	t_philo_data;
typedef struct s_os_data	t_os_data;

typedef struct s_sem_timestamp
{
	long	t;
	sem_t	*s;
}			t_sem_timestamp;

struct s_philo_data
{
	int				philo_id;
	int				eat_count;
	t_sim_data		*sim_data;
	pid_t			pid;
	pthread_t		death_checker;
	sem_t			*start_death_checker_flag;
	sem_t			*eat_flag;
	t_sem_timestamp	last_eat_timestamp;
};

struct s_os_data
{
	pthread_t	error_flag_checker;
	pthread_t	stop_flag_checker;
	pthread_t	philo_count_reached_eat_limit_checker;
	pthread_t	fork_server;
};

struct s_sim_data
{
	int				philo_num;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				eat_limit;
	sem_t			*prepare_flag;
	sem_t			*error_flag;
	sem_t			*start_flag;
	sem_t			*stop_flag;
	sem_t			*philo_count_reached_eat_limit;
	sem_t			*print_flag;
	sem_t			*fork;
	sem_t			*pair_of_forks;
	t_philo_data	philo_data[PHILO_NUM_LIMIT];
	t_os_data		os_data;
	long			start_time;
};

// exec_sim/
// exec_sim/create_os.c
int		create_os(t_sim_data *sim_data, t_os_data *os_data);
// exec_sim/create_philo.c
int		create_philos(t_sim_data *sim_data, t_philo_data *philo_data);
// exec_sim/exec_sim.c
int		exec_sim(t_sim_data *sim_data);

// init/
// init/init_philo_data.c
int		init_philo_data(t_sim_data *sim_data, t_philo_data *philo_data);
// init/init_semaphore.c
int		init_semaphore(t_sim_data *sim_data);
// init/init_sim_data.c
int		init_sim_data(int argc, char *argv[], t_sim_data *sim_data);

// os_routine/
// os_routine/start_os_routine.c
void	*start_fork_server(void *arg);
void	*start_philo_count_reached_eat_limit_checker(void *arg);
void	*start_stop_flag_checker(void *arg);
void	*start_error_flag_checker(void *arg);

// philo_routine/
// philo_routine/check_action_status.c
int		check_action_status(
			t_sim_data *sim_data, int action, long start_timestamp);
// philo_routine/check_eat_count.c
void	check_eat_count(t_sim_data *sim_data, t_philo_data *philo_data);
// philo_routine/philo_eat.c
void	philo_eat(t_sim_data *sim_data, t_philo_data *philo_data);
// philo_routine/philo_sleep.c
void	philo_sleep(t_sim_data *sim_data, t_philo_data *philo_data);
// philo_routine/philo_think.c
void	philo_think(t_sim_data *sim_data, t_philo_data *philo_data);
// philo_routine/print_log.c
void	print_log(t_sim_data *sim_data,
			t_philo_data *philo_data, int action, long *timestamp_p);
// philo_routine/start_death_checker.c
void	*start_death_checker(void *arg);
// philo_routine/start_philo_routine.c
void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data);

// utils/
// utils/clean_up.c
void	kill_philos(t_sim_data *sim_data, int philo_count);
int		waitpid_philos(t_sim_data *sim_data, int philo_count);
void	close_semaphore(t_sim_data *sim_data, int philo_num_opened_sem);
void	stop_sim(t_sim_data *sim_data, int philo_num_created);
// utils/ft_strncpy.c
char	*ft_strncpy(char *dest, char *src, unsigned int n);
// utils/get_time.c
long	get_current_time(void);
long	get_timestamp(t_sim_data *sim_data);
// utils/philo_atoi.c
int		philo_atoi(char const *str);
// utils/print_error.c
void	print_error(int error_code);
// utils/set_flag.c
void	set_stop_flag(t_sim_data *sim_data);
void	set_error_flag(t_sim_data *sim_data);

#endif
