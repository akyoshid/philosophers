/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 11:08:29 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	_init_philo_data(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;
	char	sem_name[13];

	ft_strncpy(sem_name, "eat_flag_", 13);
	i = 0;
	while (i < sim_data->philo_num)
	{
		philo_data[i].philo_id = i + 1;
		philo_data[i].last_eat_timestamp = 0;
		philo_data[i].eat_count = 0;
		philo_data[i].eat_flag.f = false;
		sem_name[9] = ((i + 1) % 1000) / 100 + '0';
		sem_name[10] = ((i + 1) % 100) / 10 + '0';
		sem_name[11] = (i + 1) % 10 + '0';
		philo_data[i].eat_flag.s = sem_open(
				sem_name, O_CREAT | O_EXCL, 0666, 1);
		if (philo_data[i].eat_flag.s == SEM_FAILED)
		{
			clean_up_semaphore(sim_data, i);
			return (print_error(ERR_SEM_OPEN), 1);
		}
		sem_unlink(sem_name);
		i++;
	}
	return (0);
}

int	_create_philos(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int	i;

	i = 0;
	while (i < sim_data->philo_num)
	{
		sim_data->philo_data[i].pid = fork();
		if (sim_data->philo_data[i].pid == -1)
		{
			kill_philos(sim_data, i);
			waitpid_philos(sim_data, i);
			clean_up_semaphore(sim_data, i);
			print_error(ERR_FORK);
			return (1);
		}
		else if (sim_data->philo_data[i].pid == 0)
		{
			start_philo_routine(sim_data, philo_data + i);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	_create_waiter(t_sim_data *sim_data, t_philo_data *philo_data)
{
	sim_data->waiter_pid = fork();
	if (sim_data->waiter_pid == -1)
	{
		kill_philos(sim_data, sim_data->philo_num);
		waitpid_philos(sim_data, sim_data->philo_num);
		clean_up_semaphore(sim_data, sim_data->philo_num);
		print_error(ERR_FORK);
		return (1);
	}
	else if (sim_data->waiter_pid == 0)
		start_waiter_routine(sim_data, philo_data);
	return (0);
}

int	exec_sim(t_sim_data *sim_data)
{
	if (_init_philo_data(sim_data, sim_data->philo_data) != 0)
		return (1);
	if (_create_philos(sim_data, sim_data->philo_data) != 0)
		return (1);
	if (_create_waiter(sim_data, sim_data->philo_data) != 0)
		return (1);
	start_sim(sim_data);
	wait_sim(sim_data);
	return (0);
}
