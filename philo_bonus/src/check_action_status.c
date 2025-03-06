/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_action_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/26 18:06:39 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_action_status(
	t_philo_data *philo_data, long start_timestamp, long timelimit)
{
	long	current_timestamp;
	int		status;

	pthread_mutex_lock(&philo_data->sim_data->super_flag.m);
	current_timestamp = get_timestamp(philo_data->sim_data);
	if (check_alive(philo_data, true, current_timestamp) == STATUS_STOP)
		status = STATUS_STOP;
	else if (current_timestamp - start_timestamp >= timelimit)
		status = STATUS_SUCCESS;
	else
		status = STATUS_CONTINUE;
	pthread_mutex_unlock(&philo_data->sim_data->super_flag.m);
	return (status);
}
