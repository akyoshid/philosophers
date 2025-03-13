/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:47:48 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 05:30:28 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	_put_fork(t_sim_data *sim_data)
{
	sem_post(sim_data->fork.s);
}

int	_take_fork(t_sim_data *sim_data, t_philo_data *philo_data)
{
	sem_wait(sim_data->fork.s);
	if (print_log(sim_data, philo_data, ACTION_TAKE_FORK, NULL)
		== STATUS_STOP)
	{
		_put_fork(sim_data);
		return (STATUS_STOP);
	}
	return (STATUS_SUCCESS);
}

int	_take_forks(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	status;

	status = _take_fork(sim_data, philo_data);
	if (status == STATUS_STOP)
		return (STATUS_STOP);
	status = _take_fork(sim_data, philo_data);
	if (status == STATUS_STOP)
	{
		_put_fork(sim_data);
		return (STATUS_STOP);
	}
	return (STATUS_SUCCESS);
}

void	_clean_up_after_eat(t_sim_data *sim_data, t_philo_data *philo_data)
{
	_put_fork(sim_data);
	_put_fork(sim_data);
	sem_wait(sim_data->philo_count_eating.s);
	sem_wait(philo_data->eat_flag.s);
	sim_data->philo_count_eating.n--;
	philo_data->eat_flag.f = false;
	sem_post(philo_data->eat_flag.s);
	sem_post(sim_data->philo_count_eating.s);
}

int	philo_eat(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (_take_forks(sim_data, philo_data) == STATUS_STOP)
		return (STATUS_STOP);
	if (print_log(sim_data, philo_data, ACTION_EAT, &start_timestamp)
		== STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_action_status(
				sim_data, philo_data, start_timestamp, sim_data->eat_time);
	}
	_clean_up_after_eat(sim_data, philo_data);
	if (status == STATUS_SUCCESS && sim_data->eat_limit != 0)
		status = check_eat_count(sim_data, philo_data);
	return (status);
}
