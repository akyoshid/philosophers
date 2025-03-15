/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_os_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:23:56 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/15 20:47:27 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	*start_fork_server(void *arg)
{
	t_sim_data		*sim_data;
	t_philo_data	*philo_data;
	int				i;

	sim_data = (t_sim_data *)arg;
	philo_data = sim_data->philo_data;
	i = 0;
	while (1)
	{
		sem_wait(sim_data->pair_of_forks);
		sem_post(philo_data[i].eat_flag);
		i++;
		if (i == sim_data->philo_num)
			i = 0;
	}
	return (NULL);
}

void	*start_philo_count_reached_eat_limit_checker(void *arg)
{
	t_sim_data	*sim_data;
	int			i;

	sim_data = (t_sim_data *)arg;
	i = 0;
	while (1)
	{
		sem_wait(sim_data->philo_count_reached_eat_limit);
		i++;
		if (i == sim_data->philo_num)
			break ;
		else
			sem_post(sim_data->print_flag);
	}
	set_stop_flag(sim_data);
	return (NULL);
}

void	*start_stop_flag_checker(void *arg)
{
	t_sim_data	*sim_data;

	sim_data = (t_sim_data *)arg;
	sem_wait(sim_data->stop_flag);
	stop_sim(sim_data, sim_data->philo_num);
	exit(PHILO_SUCCESS);
}
