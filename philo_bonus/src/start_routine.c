/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 10:23:48 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	_check_start_flag(t_sim_data *sim_data)
{
	while (1)
	{
		usleep(100);
		sem_wait(&sim_data->super_flag.s);
		if (sim_data->super_flag.start_flag == true)
		{
			sem_post(&sim_data->super_flag.s);
			break ;
		}
		sem_post(&sim_data->super_flag.s);
	}
}

void	_philo_routine(t_philo_data *philo_data)
{
	while (1)
	{
		if (philo_eat(philo_data) == STATUS_STOP)
			break ;
		if (philo_sleep(philo_data) == STATUS_STOP)
			break ;
		if (philo_think(philo_data) == STATUS_STOP)
			break ;
	}
}

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	_check_start_flag(sim_data);
	if (sim_data->philo_num == 1)
		solo_philo_think_and_die(philo_data);
	else
		_philo_routine(philo_data);
}

void	start_waiter_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;
	int		prev_i;

	_check_start_flag(sim_data);
	i = 0;
	prev_i = sim_data->philo_num - 1;
	while (1)
	{
		while (1)
		{
			usleep(100);
			sem_wait(philo_data[prev_i].eat_flag.s);
			if (philo_data[prev_i].eat_flag.f == false)
				break ;
			sem_post(philo_data[prev_i].eat_flag.s);
		}
		sem_post(philo_data[prev_i].eat_flag.s);
		sem_wait(philo_data[i].eat_flag.s);
		philo_data[i].eat_flag.f == true;
		sem_post(philo_data[i].eat_flag.s);
		prev_i = i;
		i++;
		if (i == sim_data->philo_num)
			i = 0;
	}
}
