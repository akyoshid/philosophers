/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:41:33 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 05:41:58 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

int	create_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		sim_data->philo_data[i].pid = fork();
		if (sim_data->philo_data[i].pid == -1)
		{
			stop_sim(sim_data, i);
			print_error(ERR_FORK);
			return (1);
		}
		else if (sim_data->philo_data[i].pid == 0)
			start_philo_routine(sim_data, philo_data + i);
		i++;
	}
	return (0);
}
