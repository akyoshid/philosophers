/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/15 20:36:17 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	_start_sim(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		sem_wait(sim_data->prepare_flag);
		i++;
	}
	i = 0;
	while (i < sim_data->philo_num)
	{
		sem_post(sim_data->start_flag);
		i++;
	}
}

void	_wait_sim_stop(void)
{
	while (1)
		usleep(UINT_MAX);
}

int	exec_sim(t_sim_data *sim_data)
{
	if (create_os(sim_data, &sim_data->os_data) != 0)
		return (1);
	sim_data->start_time = get_current_time();
	if (create_philos(sim_data, sim_data->philo_data) != 0)
		return (1);
	_start_sim(sim_data);
	_wait_sim_stop();
	return (0);
}
