/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 06:53:29 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/15 21:20:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

char	*_set_sem_name(char *sem_name, int i, int init_sem_status)
{
	int		last_i;
	int		philo_id;

	philo_id = i + 1;
	if (init_sem_status == INIT_PHILO_SEM_START_DEATH_CHECKER_FLAG)
	{
		ft_strncpy(sem_name, "death_checker_", 18);
		last_i = 14;
	}
	else if (init_sem_status == INIT_PHILO_SEM_EAT_FLAG)
	{
		ft_strncpy(sem_name, "eat_flag_", 18);
		last_i = 9;
	}
	else
	{
		ft_strncpy(sem_name, "last_eat_", 18);
		last_i = 9;
	}
	sem_name[last_i] = (philo_id % 1000) / 100 + '0';
	sem_name[last_i + 1] = (philo_id % 100) / 10 + '0';
	sem_name[last_i + 2] = philo_id % 10 + '0';
	return (sem_name);
}

sem_t	*_open_philo_sem(int i, int init_sem_status)
{
	char	sem_name[18];
	sem_t	*temp_sem_addr;

	if (init_sem_status == INIT_PHILO_SEM_START_DEATH_CHECKER_FLAG)
		temp_sem_addr = sem_open(_set_sem_name(sem_name, i, init_sem_status),
				O_CREAT | O_EXCL, 0666, 0);
	else if (init_sem_status == INIT_PHILO_SEM_EAT_FLAG)
		temp_sem_addr = sem_open(_set_sem_name(sem_name, i, init_sem_status),
				O_CREAT | O_EXCL, 0666, 0);
	else
		temp_sem_addr = sem_open(_set_sem_name(sem_name, i, init_sem_status),
				O_CREAT | O_EXCL, 0666, 1);
	if (temp_sem_addr != SEM_FAILED)
		sem_unlink(sem_name);
	return (temp_sem_addr);
}

void	_init_philo_sem_error(t_sim_data *sim_data, int i, int init_sem_status)
{
	t_philo_data	*philo_data;

	philo_data = sim_data->philo_data;
	if (init_sem_status >= INIT_PHILO_SEM_LAST_EAT_TIMESTAMP)
		sem_close(philo_data[i].eat_flag);
	if (init_sem_status >= INIT_PHILO_SEM_EAT_FLAG)
		sem_close(philo_data[i].start_death_checker_flag);
	close_semaphore(sim_data, i),
	print_error(ERR_SEM_OPEN);
}

void	_save_philo_sem_addr(
	t_sim_data *sim_data, int i, int init_sem_status, sem_t *sem_addr)
{
	t_philo_data	*philo_data;

	philo_data = sim_data->philo_data;
	if (init_sem_status == INIT_PHILO_SEM_START_DEATH_CHECKER_FLAG)
		philo_data[i].start_death_checker_flag = sem_addr;
	else if (init_sem_status == INIT_PHILO_SEM_EAT_FLAG)
		philo_data[i].eat_flag = sem_addr;
	else
		philo_data[i].last_eat_timestamp.s = sem_addr;
}

int	init_philo_data(t_sim_data *sim_data, t_philo_data *philo_data)
{
	int		i;
	int		init_sem_status;
	sem_t	*temp_sem_addr;

	i = 0;
	while (i < sim_data->philo_num)
	{
		philo_data[i].philo_id = i + 1;
		philo_data[i].eat_count = 0;
		philo_data[i].sim_data = sim_data;
		philo_data[i].last_eat_timestamp.t = 0;
		init_sem_status = INIT_PHILO_SEM_START_DEATH_CHECKER_FLAG;
		while (init_sem_status <= INIT_PHILO_SEM_LAST_EAT_TIMESTAMP)
		{
			temp_sem_addr = _open_philo_sem(i, init_sem_status);
			if (temp_sem_addr == SEM_FAILED)
				return (_init_philo_sem_error(sim_data, i, init_sem_status), 1);
			_save_philo_sem_addr(sim_data, i, init_sem_status, temp_sem_addr);
			init_sem_status++;
		}
		i++;
	}
	return (0);
}
