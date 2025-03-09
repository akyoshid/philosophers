/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:45:12 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 10:19:56 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	kill_philos(t_sim_data *sim_data, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		kill(sim_data->philo_data[i].pid, SIGTERM);
		i++;
	}
}

int	waitpid_philos(t_sim_data *sim_data, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		waitpid(sim_data->philo_data[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

void	start_sim(t_sim_data *sim_data)
{
	sem_wait(sim_data->super_flag.s);
	sim_data->super_flag.start_flag = true;
	sim_data->start_time = get_current_time();
	sem_post(&sim_data->super_flag.s);
}

void	wait_sim(t_sim_data *sim_data)
{
	wait_pid(-1, NULL, 0);
	kill_philos(sim_data, sim_data->philo_num);
	waitpid_philos(sim_data, sim_data->philo_num);
	kill(sim_data->waiter_pid, SIGTERM);
	waitpid(sim_data->waiter_pid, NULL, 0);
}
