/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:01:23 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 22:18:40 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

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

// Store the output timestamp in *timestamp_p
int	print_log(t_sim_data *sim_data,
		t_philo_data *philo_data, int action, long *timestamp_p)
{
	char	*mes;
	long	timestamp;

	mes = _get_log_message(action);
	sem_wait(sim_data->super_flag.s);
	timestamp = get_timestamp(sim_data);
	if (action == ACTION_EAT)
		philo_data->last_eat_timestamp = timestamp;
	if (check_alive(sim_data, philo_data, true, timestamp) == STATUS_STOP)
		return (sem_post(sim_data->super_flag.s), STATUS_STOP);
	else
		printf("%ld %d %s\n", timestamp / 1000, philo_data->philo_id, mes);
	sem_post(sim_data->super_flag.s);
	if (timestamp_p != NULL)
		*timestamp_p = timestamp;
	return (STATUS_SUCCESS);
}
