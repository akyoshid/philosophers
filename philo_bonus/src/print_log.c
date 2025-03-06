/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:01:23 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/27 11:18:21 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
int	print_log(t_philo_data *philo_data, int action, long *timestamp_p)
{
	char	*mes;
	long	timestamp;

	mes = _get_log_message(action);
	pthread_mutex_lock(&philo_data->sim_data->super_flag.m);
	timestamp = get_timestamp(philo_data->sim_data);
	if (action == ACTION_EAT)
		philo_data->last_eat_timestamp = timestamp;
	if (check_alive(philo_data, true, timestamp) == STATUS_STOP)
		return (pthread_mutex_unlock(&philo_data->sim_data->super_flag.m),
			STATUS_STOP);
	else
		printf("%ld %d %s\n", timestamp / 1000, philo_data->philo_id, mes);
	pthread_mutex_unlock(&philo_data->sim_data->super_flag.m);
	if (timestamp_p != NULL)
		*timestamp_p = timestamp;
	return (STATUS_SUCCESS);
}
