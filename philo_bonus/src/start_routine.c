/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 21:19:47 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	_check_start_flag(t_sim_data *sim_data)
{
	while (1)
	{
		usleep(100);
		sem_wait(sim_data->super_flag.s);
		if (sim_data->super_flag.start_flag == true)
		{
			sem_post(sim_data->super_flag.s);
			break ;
		}
		sem_post(sim_data->super_flag.s);
	}
}

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	_check_start_flag(sim_data);
	while (1)
	{
		if (philo_think(sim_data, philo_data) == STATUS_STOP)
			break ;
		if (philo_eat(sim_data, philo_data) == STATUS_STOP)
			break ;
		if (philo_sleep(sim_data, philo_data) == STATUS_STOP)
			break ;
	}
}

void	start_waiter_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;

	_check_start_flag(sim_data);
	i = 0;
	while (1)
	{
		while (1)
		{
			usleep(100);
			sem_wait(sim_data->philo_count_eating.s);
			if (sim_data->philo_count_eating.n < sim_data->philo_num / 2)
				break ;
			sem_post(sim_data->philo_count_eating.s);
		}
		sem_wait(philo_data[i].eat_flag.s);
		sim_data->philo_count_eating.n++;
		philo_data[i].eat_flag.f = true;
		sem_post(philo_data[i].eat_flag.s);
		sem_post(sim_data->philo_count_eating.s);
		i++;
		if (i == sim_data->philo_num)
			i = 0;
	}
}
