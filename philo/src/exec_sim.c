/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/23 07:45:24 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo_data(t_philo_data *philo_data, t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		philo_data[i].philo_id = i + 1;
		philo_data[i].sim_data = sim_data;
		if (sim_data->philo_num % 2 == 0)
		{
			if (i % 2 == 0)
				philo_data[i].first_think_time = 0;
			else
				philo_data[i].first_think_time = sim_data->eat_time;
		}
		else
		{
			if (i == sim_data->philo_num - 1)
				philo_data[i].first_think_time = sim_data->eat_time * 2;
			else if (i % 2 == 0)
				philo_data[i].first_think_time = 0;
			else
				philo_data[i].first_think_time = sim_data->eat_time;
		}
		i++;
	}
}

int	create_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		if (pthread_create(&philo_data[i].thread_id, NULL,
				start_philo_routine, philo_data + i) != 0)
		{
			// stop_flag
			i--;
			while (i >= 0)
			{
				pthread_join(philo_data[i].thread_id, NULL);
				i--;
			}
			// clean_up_mutex
			print_error(ERR_PTHREAD_CREATE);
			return (1);
		}
		i++;
	}
	return (0);
}

void	start_sim(t_sim_data *sim_data)
{
	sim_data->start_time = get_current_time_ms();
}

int	wait_philos(t_sim_data *sim_data, t_philo_data *philo_data)
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

	init_philo_data(philo_data, sim_data);
	if (create_philos(sim_data, philo_data) != 0)
		return (1);
	start_sim(sim_data);
	if (wait_philos(sim_data, philo_data) != 0)
		return (1);
	return (0);
}
