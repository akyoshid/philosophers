/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 06:53:29 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/11 07:17:35 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

char	*_get_sem_name(int philo_id, bool start_flag)
{
	char	sem_name[15];
	int		last_i;

	if (start_flag == true)
	{
		ft_strncpy(sem_name, "start_flag_", 15);
		last_i = 11;
	}
	else
	{
		ft_strncpy(sem_name, "eat_flag_", 15);
		last_i = 9;
	}
	sem_name[last_i] = (philo_id % 1000) / 100 + '0';
	sem_name[last_i + 1] = (philo_id % 100) / 10 + '0';
	sem_name[last_i + 2] = philo_id % 10 + '0';
	return (sem_name);
}

void	_set_philo_data(t_philo_data *philo_data, int i)
{
	philo_data[i].philo_id = i + 1;
	philo_data[i].last_eat_timestamp = 0;
	philo_data[i].eat_count = 0;
}

int	init_philo_data(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;
	char	*sem_name;

	i = 0;
	while (i < sim_data->philo_num)
	{
		_set_philo_data(philo_data, i);
		sem_name = _get_sem_name(philo_data[i].philo_id, true);
		philo_data[i].start_flag = sem_open(
				sem_name, O_CREAT | O_EXCL, 0666, 0);
		if (philo_data[i].start_flag == SEM_FAILED)
			return (clean_up_semaphore(sim_data, i),
				print_error(ERR_SEM_OPEN), 1);
		sem_unlink(sem_name);
		sem_name = _get_sem_name(philo_data[i].philo_id, false);
		philo_data[i].eat_flag = sem_open(sem_name, O_CREAT | O_EXCL, 0666, 0);
		if (philo_data[i].eat_flag == SEM_FAILED)
			return (sem_close(philo_data[i].start_flag),
				clean_up_semaphore(sim_data, i),
				print_error(ERR_SEM_OPEN), 1);
		sem_unlink(sem_name);
		i++;
	}
	return (0);
}

