/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/25 21:47:46 by akyoshid         ###   ########.fr       */
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
	usleep(philo_data->first_think_time * 1000);
	if (philo_eat(philo_data) != STATUS_SUCCESS)
		printf("🔥");
	return (NULL);
}
