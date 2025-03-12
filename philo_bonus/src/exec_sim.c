/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/12 20:26:30 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	_create_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		sim_data->philo_data[i].pid = fork();
		if (sim_data->philo_data[i].pid == -1)
		{
			stop_sim(sim_data, i);
			print_error(ERR_FORK);
			return (1);
		}
		else if (sim_data->philo_data[i].pid == 0)
			start_philo_routine(sim_data, philo_data + i);
		i++;
	}
	return (0);
}

int	_create_os(t_sim_data *sim_data, t_os_data *os_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		if (pthread_create(&os_data->philo_death_checker[i],
				NULL, start_philo_death_checker, sim_data->philo_data + i) != 0)
			return (stop_sim(sim_data, sim_data->philo_num),
				print_error(ERR_PTHREAD_CREATE), 1);
		pthread_detach(os_data->philo_death_checker[i]);
		i++;
	}
	if (sim_data->eat_limit != 0)
	{
		if (pthread_create(
				&os_data->philo_count_reached_eat_limit_checker, NULL,
				start_philo_count_reached_eat_limit_checker, sim_data) != 0)
			return (stop_sim(sim_data, sim_data->philo_num),
				print_error(ERR_PTHREAD_CREATE), 1);
		pthread_detach(os_data->philo_count_reached_eat_limit_checker);
	}
	if (pthread_create(&os_data->fork_server,
			NULL, start_fork_server, sim_data) != 0)
		return (stop_sim(sim_data, sim_data->philo_num),
			print_error(ERR_PTHREAD_CREATE), 1);
	pthread_detach(os_data->fork_server);
	if (pthread_create(&os_data->stop_flag_checker,
			NULL, start_stop_flag_checker, sim_data) != 0)
		return (stop_sim(sim_data, sim_data->philo_num),
			print_error(ERR_PTHREAD_CREATE), 1);
	return (0);
}

void	_start_sim(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	sim_data->start_time = get_current_time();
	while (i < sim_data->philo_num)
	{
		sem_post(philo_data[i].start_flag);
		i++;
	}
	i = 0;
	while (i < sim_data->philo_num + 3)
	{
		sem_post(sim_data->os_data.start_flag);
		i++;
	}
}

void	_wait_sim_stop(t_sim_data *sim_data)
{
	pthread_join(sim_data->os_data.stop_flag_checker, NULL);
}

int	exec_sim(t_sim_data *sim_data)
{
	if (_create_philos(sim_data, sim_data->philo_data) != 0)
		return (1);
	if (_create_os(sim_data, &sim_data->os_data) != 0)
		return (1);
	_start_sim(sim_data, sim_data->philo_data);
	_wait_sim_stop(sim_data);
	return (0);
}
