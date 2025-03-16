/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/16 08:31:07 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	_create_death_checker(t_sim_data *sim_data, t_philo_data *philo_data)
{
	if (pthread_create(&philo_data->death_checker,
			NULL, start_death_checker, philo_data) != 0)
	{
		sem_wait(sim_data->print_flag);
		print_error(ERR_PTHREAD_CREATE);
		set_error_flag(sim_data);
	}
	pthread_detach(philo_data->death_checker);
}

void	_adjust_start_time(t_sim_data *sim_data)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time - sim_data->start_time < 0
		|| current_time - sim_data->start_time > WAITING_TIME_TO_START_SIM)
	{
		sem_wait(sim_data->print_flag);
		print_error(ERR_ADJUST_START_TIME);
		set_error_flag(sim_data);
	}
	else
		sim_data->start_time += WAITING_TIME_TO_START_SIM;
	usleep(sim_data->start_time - current_time);
}

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	_create_death_checker(sim_data, philo_data);
	sem_post(sim_data->prepare_flag);
	sem_wait(sim_data->start_flag);
	_adjust_start_time(sim_data);
	sem_post(philo_data->start_death_checker_flag);
	while (1)
	{
		philo_think(sim_data, philo_data);
		philo_eat(sim_data, philo_data);
		philo_sleep(sim_data, philo_data);
	}
}
