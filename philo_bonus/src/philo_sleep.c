/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:45:37 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 20:04:16 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	philo_sleep(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (print_log(sim_data, philo_data, ACTION_SLEEP, &start_timestamp)
		== STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_action_status(
				sim_data, philo_data, start_timestamp, sim_data->sleep_time);
	}
	return (status);
}
