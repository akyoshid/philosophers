/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/26 21:01:32 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*start_philo_routine(void *arg)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)arg;
	while (1)
	{
		usleep(100);
		if (philo_data->sim_data->super_flag.stop_flag == true)
			return (NULL);
		if (philo_data->sim_data->start_time != 0)
			break ;
	}
	if (philo_first_think(philo_data) == STATUS_STOP)
		return (NULL);
	while (1)
	{
		if (philo_eat(philo_data) == STATUS_STOP)
			break ;
		if (philo_sleep(philo_data) == STATUS_STOP)
			break ;
		if (philo_think(philo_data) == STATUS_STOP)
			break ;
	}
	return (NULL);
}
