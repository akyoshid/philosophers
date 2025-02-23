/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:56:33 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/23 04:45:45 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_init_sim_error(int sim_data_field_num, int sim_data_value)
{
	char	*str;

	if (sim_data_field_num == PHILO_NUM)
		str = "number_of_philosophers";
	else if (sim_data_field_num == DIE_TIME)
		str = "time_to_die";
	else if (sim_data_field_num == EAT_TIME)
		str = "time_to_eat";
	else if (sim_data_field_num == SLEEP_TIME)
		str = "time_to_sleep";
	else if (sim_data_field_num == EAT_LIMIT)
		str = "number_of_times_each_philosopher_must_eat";
	if (sim_data_value == -2)
		ft_dprintf(2, "philo: %s: non-integer argument\n"
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", str);
	else
		ft_dprintf(2, "philo: %s: invaild argument\n"
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n", str);
	return (PHILO_SYNTAX_ERROR);
}

int	init_sim_data(int argc, char *argv[], t_sim_data *sim_data)
{
	if (argc < 5 || argc > 6)
		return (print_error(ERR_ARGC), PHILO_SYNTAX_ERROR);
	sim_data->philo_num = philo_atoi(argv[1]);
	if (sim_data->philo_num <= 0 || sim_data->philo_num > PHILO_NUM_LIMIT)
		return (print_init_sim_error(PHILO_NUM, sim_data->philo_num));
	sim_data->die_time = philo_atoi(argv[2]);
	if (sim_data->die_time <= 0)
		return (print_init_sim_error(DIE_TIME, sim_data->die_time));
	sim_data->eat_time = philo_atoi(argv[3]);
	if (sim_data->eat_time <= 0)
		return (print_init_sim_error(EAT_TIME, sim_data->eat_time));
	sim_data->sleep_time = philo_atoi(argv[4]);
	if (sim_data->sleep_time <= 0)
		return (print_init_sim_error(SLEEP_TIME, sim_data->sleep_time));
	if (argc == 6)
	{
		sim_data->eat_limit = philo_atoi(argv[5]);
		if (sim_data->eat_limit <= 0)
			return (print_init_sim_error(EAT_LIMIT, sim_data->eat_limit));
	}
	else
		sim_data->eat_limit = 0;
	sim_data->start_time = 0;
	return (0);
}
