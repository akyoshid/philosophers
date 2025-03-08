/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/08 21:08:37 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	_philo_routine(t_philo_data *philo_data)
{
	while (1)
	{
		if (philo_eat(philo_data) == STATUS_STOP)
			break ;
		if (philo_sleep(philo_data) == STATUS_STOP)
			break ;
		if (philo_think(philo_data) == STATUS_STOP)
			break ;
	}
}

int	_check_start_flag(t_sim_data *sim_data)
{
	int	status;

	sem_wait(&sim_data->super_flag.s);
	if (sim_data->super_flag.start_flag == true)
		status = STATUS_SUCCESS;
	else
		status = STATUS_CONTINUE;
	sem_post(&sim_data->super_flag.s);
	return (status);
}

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	status;

	status = STATUS_CONTINUE;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = _check_start_flag(sim_data);
	}
	if (sim_data->philo_num == 1)
		solo_philo_take_fork_and_die(philo_data);
	else
		_philo_routine(philo_data);
	return (NULL);
}
