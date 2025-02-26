/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/26 20:39:05 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	_set_first_think_time(
	t_philo_data *philo_data, t_sim_data *sim_data, int i)
{
	if (sim_data->philo_num % 2 == 0)
	{
		if (i % 2 == 0)
			philo_data[i].first_think_time = 0;
		else
			philo_data[i].first_think_time = sim_data->eat_time;
	}
	else
	{
		if (i % 2 == 0)
			philo_data[i].first_think_time
				= sim_data->eat_time * (i / 2) / (sim_data->philo_num / 2);
		else
			philo_data[i].first_think_time
				= sim_data->eat_time * ((i + 1) / 2)
					/ (sim_data->philo_num / 2) + sim_data->eat_time;
	}
}

void	_init_philo_data(t_philo_data *philo_data, t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		philo_data[i].philo_id = i + 1;
		philo_data[i].sim_data = sim_data;
		if (i == sim_data->philo_num - 1)
		{
			philo_data[i].first_fork = sim_data->fork + 0;
			philo_data[i].second_fork = sim_data->fork + i;
		}
		else
		{
			philo_data[i].first_fork = sim_data->fork + i;
			philo_data[i].second_fork = sim_data->fork + i + 1;
		}
		_set_first_think_time(philo_data, sim_data, i);
		philo_data[i].last_eat_timestamp = 0;
		philo_data[i].eat_count = 0;
		i++;
	}
}

int	_create_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		if (pthread_create(&philo_data[i].thread_id, NULL,
				start_philo_routine, philo_data + i) != 0)
		{
			sim_data->super_flag.stop_flag = true;
			i--;
			while (i >= 0)
			{
				pthread_join(philo_data[i].thread_id, NULL);
				i--;
			}
			clean_up_mutex(sim_data, sim_data->philo_num);
			print_error(ERR_PTHREAD_CREATE);
			return (1);
		}
		i++;
	}
	return (0);
}

int	_wait_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		pthread_join(philo_data[i].thread_id, NULL);
		i++;
	}
	return (0);
}

int	exec_sim(t_sim_data *sim_data)
{
	t_philo_data	philo_data[200];

	_init_philo_data(philo_data, sim_data);
	if (_create_philos(sim_data, philo_data) != 0)
		return (1);
	sim_data->start_time = get_current_time();
	_wait_philos(sim_data, philo_data);
	return (0);
}
