/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_action_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 11:24:18 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check_action_status(t_sim_data *sim_data,
		t_philo_data *philo_data, long start_timestamp, long timelimit)
{
	long	current_timestamp;
	int		status;

	sem_wait(sim_data->super_flag.s);
	current_timestamp = get_timestamp(sim_data);
	if (check_alive(sim_data, philo_data, true, current_timestamp)
		== STATUS_STOP)
		status = STATUS_STOP;
	else if (current_timestamp - start_timestamp >= timelimit)
		status = STATUS_SUCCESS;
	else
		status = STATUS_CONTINUE;
	sem_post(sim_data->super_flag.s);
	return (status);
}
