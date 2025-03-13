/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:47:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 10:29:37 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	_put_forks(t_sim_data *sim_data)
{
	sem_post(sim_data->fork);
	sem_post(sim_data->fork);
	sem_post(sim_data->pair_of_forks);
}

void	_take_forks(t_sim_data *sim_data, t_philo_data *philo_data)
{
	sem_wait(sim_data->fork);
	print_log(sim_data, philo_data, ACTION_TAKE_FORK, NULL);
	sem_wait(sim_data->fork);
	print_log(sim_data, philo_data, ACTION_TAKE_FORK, NULL);
}

void	philo_eat(t_sim_data *sim_data, t_philo_data *philo_data)
{
	long	start_timestamp;

	_take_forks(sim_data, philo_data);
	print_log(sim_data, philo_data, ACTION_EAT, &start_timestamp);
	while (1)
	{
		usleep(500);
		if (check_action_status(sim_data, ACTION_EAT, start_timestamp) == 1)
			break ;
	}
	_put_forks(sim_data);
	if (sim_data->eat_limit != 0)
		check_eat_count(sim_data, philo_data);
}
