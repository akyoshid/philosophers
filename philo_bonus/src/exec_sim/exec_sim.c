/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 05:43:14 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	_start_sim(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	sim_data->start_time = get_current_time();
	while (i < sim_data->philo_num)
	{
		sem_post(philo_data[i].start_flag);
		i++;
	}
	i = 0;
	while (i < sim_data->philo_num + 3)
	{
		sem_post(sim_data->os_data.start_flag);
		i++;
	}
}

void	_wait_sim_stop(t_sim_data *sim_data)
{
	pthread_join(sim_data->os_data.stop_flag_checker, NULL);
}

int	exec_sim(t_sim_data *sim_data)
{
	if (create_philos(sim_data, sim_data->philo_data) != 0)
		return (1);
	if (create_os(sim_data, &sim_data->os_data) != 0)
		return (1);
	_start_sim(sim_data, sim_data->philo_data);
	_wait_sim_stop(sim_data);
	return (0);
}
