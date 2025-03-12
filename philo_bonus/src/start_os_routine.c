/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_os_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:23:56 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/12 20:37:29 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*start_philo_death_checker(void *arg)
{
	t_philo_data	*philo_data;
	t_sim_data		*sim_data;
	t_os_data		*os_data;
	long			timestamp;

	philo_data = (t_philo_data *)arg;
	sim_data = philo_data->sim_data;
	os_data = &sim_data->os_data;
	sem_wait(os_data->start_flag);
	while (1)
	{
		usleep(500);
		sem_wait(sim_data->print_flag);
		timestamp = get_timestamp(sim_data);
		if (timestamp - philo_data->last_eat_timestamp >= sim_data->die_time)
		{
			printf("%ld %d died\n", timestamp / 1000, philo_data->philo_id);
			sem_post(sim_data->stop_flag);
			while (1)
				;
		}
		sem_post(sim_data->print_flag);
	}
	return (NULL);
}

void	*start_fork_server(void *arg)
{
	t_sim_data		*sim_data;
	t_philo_data	*philo_data;
	t_os_data		*os_data;
	int				i;

	sim_data = (t_sim_data *)arg;
	philo_data = sim_data->philo_data;
	os_data = &sim_data->os_data;
	sem_wait(os_data->start_flag);
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
	t_os_data	*os_data;
	int			i;

	sim_data = (t_sim_data *)arg;
	os_data = &sim_data->os_data;
	sem_wait(os_data->start_flag);
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
	sem_post(sim_data->stop_flag);
	while (1)
		;
	return (NULL);
}

void	*start_stop_flag_checker(void *arg)
{
	t_sim_data	*sim_data;
	t_os_data	*os_data;

	sim_data = (t_sim_data *)arg;
	os_data = &sim_data->os_data;
	sem_wait(os_data->start_flag);
	sem_wait(sim_data->stop_flag);
	stop_sim(sim_data, sim_data->philo_num);
	return (NULL);
}
