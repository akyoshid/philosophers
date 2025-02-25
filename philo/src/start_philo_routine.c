/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/24 10:11:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// In `if (philo_data->sim_data->start_time != 0)`,
// there is no guarantee that stop_flag is false.
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
	return (NULL);
}
