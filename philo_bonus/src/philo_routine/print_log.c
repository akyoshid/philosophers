/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:01:23 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/14 06:55:08 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

char	*_get_log_message(int action)
{
	char	*mes;

	mes = "";
	if (action == ACTION_TAKE_FORK)
		mes = "has taken a fork";
	else if (action == ACTION_EAT)
		mes = "is eating";
	else if (action == ACTION_SLEEP)
		mes = "is sleeping";
	else if (action == ACTION_THINK)
		mes = "is thinking";
	return (mes);
}

void	_check_alive(
	t_sim_data *sim_data, t_philo_data *philo_data, long timestamp)
{
	if (timestamp - philo_data->last_eat_timestamp.t >= sim_data->die_time)
	{
		printf("%ld %d died\n", timestamp / 1000, philo_data->philo_id);
		set_stop_flag(sim_data);
	}
}

// Store the output timestamp in *timestamp_p
void	print_log(t_sim_data *sim_data,
	t_philo_data *philo_data, int action, long *timestamp_p)
{
	char	*mes;
	long	timestamp;

	mes = _get_log_message(action);
	sem_wait(sim_data->print_flag);
	timestamp = get_timestamp(sim_data);
	sem_wait(philo_data->last_eat_timestamp.s);
	if (action == ACTION_EAT)
		philo_data->last_eat_timestamp.t = timestamp;
	_check_alive(sim_data, philo_data, timestamp);
	sem_post(philo_data->last_eat_timestamp.s);
	printf("%ld %d %s\n", timestamp / 1000, philo_data->philo_id, mes);
	sem_post(sim_data->print_flag);
	if (timestamp_p != NULL)
		*timestamp_p = timestamp;
}
