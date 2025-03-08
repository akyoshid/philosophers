/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:42:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/08 20:32:30 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	_init_philo_data(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;
	char	sem_name[13];

	ft_strncpy(sem_name, "last_eat_", 13);
	i = 0;
	while (i < sim_data->philo_num)
	{
		philo_data[i].philo_id = i + 1;
		philo_data[i].eat_count = 0;
		philo_data[i].last_eat_timestamp.timestamp = 0;
		sem_name[9] = ((i + 1) % 1000) / 100 + '0';
		sem_name[10] = ((i + 1) % 100) / 10 + '0';
		sem_name[11] = (i + 1) % 10 + '0';
		philo_data[i].last_eat_timestamp.s = sem_open(
				sem_name, O_CREAT | O_EXCL, 0666, 1);
		if (philo_data[i].last_eat_timestamp.s == SEM_FAILED)
		{
			clean_up_semaphore(sim_data, i);
			print_error(ERR_SEM_OPEN);
			return (1);
		}
		sem_unlink(sem_name);
		i++;
	}
	return (0);
}

void	_kill_philos(t_sim_data *sim_data, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		kill(sim_data->philo_data[i].pid, SIGTERM);
		i++;
	}
}

int	_waitpid_philos(t_sim_data *sim_data, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		waitpid(sim_data->philo_data[i].pid, NULL, 0);
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
			_kill_philos(sim_data, i);
			_waitpid_philos(sim_data, i);
			clean_up_semaphore(sim_data, i);
			print_error(ERR_FORK);
			return (1);
		}
		else if (sim_data->philo_data[i].pid == 0)
		{
			start_philo_routine(sim_data, philo_data[i]);
			exit(1);
		}
		i++;
	}
	return (0);
}

int	exec_sim(t_sim_data *sim_data)
{
	if (_init_philo_data(sim_data, sim_data->philo_data) != 0)
		return (1);
	if (_create_philos(sim_data, sim_data->philo_data) != 0)
		return (1);
	start_sim(sim_data);
	wait_pid(-1, NULL, 0);
	_kill_philos(sim_data, sim_data->philo_num);
	_waitpid_philos(sim_data, sim_data->philo_num);
	return (0);
}
