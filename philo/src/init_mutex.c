/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:59:50 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/25 23:29:38 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_mutex(t_sim_data *sim_data)
{
	int	i;

	sim_data->super_flag.stop_flag = false;
	sim_data->super_flag.philo_count_reached_eat_limit = 0;
	if (pthread_mutex_init(&sim_data->super_flag.m, NULL) != 0)
	{
		print_error(ERR_PTHREAD_MUTEX_INIT);
		return (1);
	}
	i = 0;
	while (i < sim_data->philo_num)
	{
		sim_data->fork[i].last_user_num = 0;
		if (pthread_mutex_init(&sim_data->fork[i].m, NULL) != 0)
		{
			clean_up_mutex(sim_data, i);
			print_error(ERR_PTHREAD_MUTEX_INIT);
			return (1);
		}
		i++;
	}
	return (0);
}
