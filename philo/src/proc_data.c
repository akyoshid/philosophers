/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:56:33 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/21 05:57:13 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_data_error(int data_field_num, int data_value)
{
	char	*str;

	if (data_field_num == PHILO_NUM)
		str = "number_of_philosophers";
	else if (data_field_num == DIE_TIME)
		str = "time_to_die";
	else if (data_field_num == EAT_TIME)
		str = "time_to_eat";
	else if (data_field_num == SLEEP_TIME)
		str = "time_to_sleep";
	else if (data_field_num == EAT_LIMIT)
		str = "number_of_times_each_philosopher_must_eat";
	if (data_value == -2)
		ft_dprintf(2, "philo: %s: non-integer argument\n"
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", str);
	else
		ft_dprintf(2, "philo: %s: invaild argument\n"
		"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", str);
	return (PHILO_SYNTAX_ERROR);
}

int	proc_data(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		return (print_error(ERR_ARGC), PHILO_SYNTAX_ERROR);
	data->philo_num = philo_atoi(argv[1]);
	if (data->philo_num <= 0 || data->philo_num > PHILO_NUM_LIMIT)
		return (print_data_error(PHILO_NUM, data->philo_num));
	data->die_time = philo_atoi(argv[2]);
	if (data->die_time <= 0)
		return (print_data_error(DIE_TIME, data->die_time));
	data->eat_time = philo_atoi(argv[3]);
	if (data->eat_time <= 0)
		return (print_data_error(EAT_TIME, data->eat_time));
	data->sleep_time = philo_atoi(argv[4]);
	if (data->sleep_time <= 0)
		return (print_data_error(SLEEP_TIME, data->sleep_time));
	if (argc == 6)
	{
		data->eat_limit = philo_atoi(argv[5]);
		if (data->eat_limit <= 0)
			return (print_data_error(EAT_LIMIT, data->eat_limit));
	}
	else
		data->eat_limit = 0;
	return (0);
}
