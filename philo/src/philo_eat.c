/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:47:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/26 11:08:56 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	_put_fork(t_fork *fork)
{
	pthread_mutex_unlock(&fork->m);
}

int	_take_fork(t_fork *fork, t_philo_data *philo_data)
{
	pthread_mutex_lock(&fork->m);
	if (fork->last_user_num == philo_data->philo_id)
		return (pthread_mutex_unlock(&fork->m), STATUS_FAILURE);
	else
	{
		fork->last_user_num = philo_data->philo_id;
		if (print_log(philo_data, ACTION_TAKE_FORK, NULL) == STATUS_STOP)
			return (pthread_mutex_unlock(&fork->m), STATUS_STOP);
		return (STATUS_SUCCESS);
	}
}

int	_take_forks(t_philo_data *philo_data)
{
	int	status;

	while (1)
	{
		status = _take_fork(philo_data->first_fork, philo_data);
		if (status == STATUS_SUCCESS)
			break ;
		else if (status == STATUS_FAILURE)
			usleep(100);
		if (status == STATUS_STOP
			|| check_alive(philo_data, false, 0) == STATUS_STOP)
			return (STATUS_STOP);
	}
	while (1)
	{
		status = _take_fork(philo_data->second_fork, philo_data);
		if (status == STATUS_SUCCESS)
			break ;
		else if (status == STATUS_FAILURE)
			usleep(100);
		if (status == STATUS_STOP
			|| check_alive(philo_data, false, 0) == STATUS_STOP)
			return (_put_fork(philo_data->first_fork), STATUS_STOP);
	}
	return (STATUS_SUCCESS);
}

int	_check_eat_count(t_philo_data *philo_data, t_sim_data *sim_data)
{
	int	status;

	status = STATUS_SUCCESS;
	philo_data->eat_count++;
	if (sim_data->eat_limit == philo_data->eat_count)
	{
		pthread_mutex_lock(&sim_data->super_flag.m);
		sim_data->super_flag.philo_count_reached_eat_limit++;
		if (sim_data->super_flag.philo_count_reached_eat_limit
			== sim_data->philo_num)
		{
			sim_data->super_flag.stop_flag = true;
			status = STATUS_STOP;
		}
		pthread_mutex_unlock(&philo_data->sim_data->super_flag.m);
	}
	return (status);
}

int	philo_eat(t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (_take_forks(philo_data) == STATUS_STOP)
		return (STATUS_STOP);
	if (print_log(philo_data, ACTION_EAT, &start_timestamp) == STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_action_status(
				philo_data, start_timestamp, philo_data->sim_data->eat_time);
	}
	_put_fork(philo_data->second_fork);
	_put_fork(philo_data->first_fork);
	if (status == STATUS_SUCCESS && philo_data->sim_data->eat_limit != 0)
		status = _check_eat_count(philo_data, philo_data->sim_data);
	return (status);
}
