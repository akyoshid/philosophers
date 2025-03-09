/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:01:20 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 20:17:07 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	_check_think_status(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		status;

	if (check_alive(sim_data, philo_data, false, 0) == STATUS_STOP)
		status = STATUS_STOP;
	else
	{
		sem_wait(philo_data->eat_flag.s);
		if (philo_data->eat_flag.f == true)
			status = STATUS_SUCCESS;
		else
			status = STATUS_CONTINUE;
		sem_post(philo_data->eat_flag.s);
	}
	return (status);
}

int	philo_think(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (print_log(sim_data, philo_data, ACTION_THINK, &start_timestamp)
		== STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = _check_think_status(sim_data, philo_data);
	}
	return (status);
}
