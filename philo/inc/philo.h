/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/23 07:55:52 by akyoshid         ###   ########.fr       */
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
}	t_error_code;

typedef enum e_sim_data_field_num
{
	PHILO_NUM,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	EAT_LIMIT,
}	t_sim_data_field_num;

typedef struct s_sim_data
{
	int		philo_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_limit;
	long	start_time;
}			t_sim_data;

typedef struct s_philo_data
{
	int			philo_id;
	t_sim_data	*sim_data;
	int			first_think_time;
	pthread_t	thread_id;
}				t_philo_data;

// init_sim_data.c
int		init_sim_data(int argc, char *argv[], t_sim_data *sim_data);
// exec_sim.c
int		exec_sim(t_sim_data *sim_data);
// get_current_time_ms.c
long	get_current_time_ms(void);
// philo_atoi.c
int		philo_atoi(char const *str);
// print_error.c
void	print_error(int error_code);
// start_philo_routine.c
void	*start_philo_routine(void *arg);

#endif
