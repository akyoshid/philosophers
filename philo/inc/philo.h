/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:26 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/21 05:58:26 by akyoshid         ###   ########.fr       */
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
}	t_error_code;

typedef enum e_data_field_num
{
	PHILO_NUM,
	DIE_TIME,
	EAT_TIME,
	SLEEP_TIME,
	EAT_LIMIT,
}	t_data_field_num;

typedef struct s_data
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	eat_limit;
}		t_data;

// philo_atoi.c
int		check_non_integer(char const *str);
int		philo_atoi(char const *str);
// print_error.c
void	print_error(int error_code);
// proc_data.c
int		print_data_error(int data_field_num, int data_value);
int		proc_data(int argc, char *argv[], t_data *data);

#endif
