/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/27 00:34:09 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	*start_philo_routine(void *arg)
{
	t_philo_data	*philo_data;
	int				status;

	philo_data = (t_philo_data *)arg;
	status = STATUS_CONTINUE;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_super_flag(philo_data->sim_data);
		if (status == STATUS_STOP)
			return (NULL);
		else if (status == STATUS_SUCCESS)
			break ;
	}
	if (philo_first_think(philo_data) == STATUS_STOP)
		return (NULL);
	if (philo_data->sim_data->philo_num == 1)
		solo_philo_take_fork_and_die(philo_data);
	else
		_philo_routine(philo_data);
	return (NULL);
}
