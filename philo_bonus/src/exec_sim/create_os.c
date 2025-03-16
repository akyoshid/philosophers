/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_os.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:42:29 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/16 08:21:38 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

int	_create_philo_count_reached_eat_limit_checker(
	t_sim_data *sim_data, t_os_data *os_data)
{
	if (sim_data->eat_limit != 0)
	{
		if (pthread_create(
				&os_data->philo_count_reached_eat_limit_checker, NULL,
				start_philo_count_reached_eat_limit_checker, sim_data) != 0)
		{
			close_semaphore(sim_data, sim_data->philo_num);
			print_error(ERR_PTHREAD_CREATE);
			return (1);
		}
		pthread_detach(os_data->philo_count_reached_eat_limit_checker);
	}
	return (0);
}

int	_create_fork_server(t_sim_data *sim_data, t_os_data *os_data)
{
	if (pthread_create(&os_data->fork_server,
			NULL, start_fork_server, sim_data) != 0)
	{
		close_semaphore(sim_data, sim_data->philo_num);
		print_error(ERR_PTHREAD_CREATE);
		return (1);
	}
	pthread_detach(os_data->fork_server);
	return (0);
}

int	_create_stop_flag_checker(t_sim_data *sim_data, t_os_data *os_data)
{
	if (pthread_create(&os_data->stop_flag_checker,
			NULL, start_stop_flag_checker, sim_data) != 0)
	{
		close_semaphore(sim_data, sim_data->philo_num);
		print_error(ERR_PTHREAD_CREATE);
		return (1);
	}
	pthread_detach(os_data->stop_flag_checker);
	return (0);
}

int	_create_error_flag_checker(t_sim_data *sim_data, t_os_data *os_data)
{
	if (pthread_create(&os_data->error_flag_checker,
			NULL, start_error_flag_checker, sim_data) != 0)
	{
		close_semaphore(sim_data, sim_data->philo_num);
		print_error(ERR_PTHREAD_CREATE);
		return (1);
	}
	pthread_detach(os_data->error_flag_checker);
	return (0);
}

int	create_os(t_sim_data *sim_data, t_os_data *os_data)
{
	if (_create_philo_count_reached_eat_limit_checker(sim_data, os_data) != 0)
		return (1);
	if (_create_fork_server(sim_data, os_data) != 0)
		return (1);
	if (_create_stop_flag_checker(sim_data, os_data) != 0)
		return (1);
	if (_create_error_flag_checker(sim_data, os_data) != 0)
		return (1);
	return (0);
}
