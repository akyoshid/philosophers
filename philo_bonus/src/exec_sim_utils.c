/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:45:12 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/12 19:02:03 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	kill_philos(t_sim_data *sim_data, int philo_num_created)
{
	int	i;

	i = 0;
	while (i < philo_num_created)
	{
		kill(sim_data->philo_data[i].pid, SIGTERM);
		i++;
	}
}

int	waitpid_philos(t_sim_data *sim_data, int philo_num_created)
{
	int	i;

	i = 0;
	while (i < philo_num_created)
	{
		waitpid(sim_data->philo_data[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

void	stop_sim(t_sim_data *sim_data, int philo_num_created)
{
	kill_philos(sim_data, philo_num_created);
	waitpid_philos(sim_data, philo_num_created);
	clean_up_semaphore(sim_data, sim_data->philo_num);
}
