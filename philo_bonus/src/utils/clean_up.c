/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:45:12 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/14 05:25:28 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

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

void	close_semaphore(t_sim_data *sim_data, int philo_num_opened_sem)
{
	int	i;

	sem_close(sim_data->prepare_flag);
	sem_close(sim_data->start_flag);
	sem_close(sim_data->stop_flag);
	sem_close(sim_data->philo_count_reached_eat_limit);
	sem_close(sim_data->print_flag);
	sem_close(sim_data->fork);
	sem_close(sim_data->pair_of_forks);
	i = 0;
	while (i < philo_num_opened_sem)
	{
		sem_close(sim_data->philo_data[i].start_death_checker_flag);
		sem_close(sim_data->philo_data[i].eat_flag);
		sem_close(sim_data->philo_data[i].last_eat_timestamp.s);
		i++;
	}
}

void	stop_sim(t_sim_data *sim_data, int philo_num_created)
{
	kill_philos(sim_data, philo_num_created);
	waitpid_philos(sim_data, philo_num_created);
	close_semaphore(sim_data, sim_data->philo_num);
}
