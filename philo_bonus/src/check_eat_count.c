/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eat_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:11:05 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:24:34 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check_eat_count(t_philo_data *philo_data, t_sim_data *sim_data)
{
	int	status;

	status = STATUS_SUCCESS;
	philo_data->eat_count++;
	if (sim_data->eat_limit == philo_data->eat_count)
	{
		pthread_mutex_lock(&sim_data->super_flag.m);
		sim_data->super_flag.philo_count_reached_eat_limit++;
		if (sim_data->super_flag.philo_count_reached_eat_limit
			== sim_data->philo_num)
		{
			sim_data->super_flag.stop_flag = true;
			status = STATUS_STOP;
		}
		pthread_mutex_unlock(&philo_data->sim_data->super_flag.m);
	}
	return (status);
}
