/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:59:50 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/14 04:17:27 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

char	*_get_sem_name(int init_sem_status)
{
	if (init_sem_status == INIT_SEM_PREPARE_FLAG)
		return ("prepare_flag");
	else if (init_sem_status == INIT_SEM_START_FLAG)
		return ("start_flag");
	else if (init_sem_status == INIT_SEM_STOP_FLAG)
		return ("stop_flag");
	else if (init_sem_status == INIT_SEM_PHILO_COUNT_REACHED_EAT_LIMIT)
		return ("philo_count_reached_eat_limit");
	else if (init_sem_status == INIT_SEM_PRINT_FLAG)
		return ("print_flag");
	else if (init_sem_status == INIT_SEM_FORK)
		return ("fork");
	else
		return ("pair_of_forks");
}

sem_t	*_wrapped_sem_open(t_sim_data *sim_data, int init_sem_status)
{
	if (init_sem_status == INIT_SEM_PREPARE_FLAG)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, 0));
	else if (init_sem_status == INIT_SEM_START_FLAG)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, 0));
	else if (init_sem_status == INIT_SEM_STOP_FLAG)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, 0));
	else if (init_sem_status == INIT_SEM_PHILO_COUNT_REACHED_EAT_LIMIT)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, 0));
	else if (init_sem_status == INIT_SEM_PRINT_FLAG)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, 1));
	else if (init_sem_status == INIT_SEM_FORK)
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, sim_data->philo_num));
	else
		return (sem_open(_get_sem_name(init_sem_status),
				O_CREAT | O_EXCL, 0666, sim_data->philo_num / 2));
}

void	_init_semaphore_error(t_sim_data *sim_data, int init_sem_status)
{
	if (init_sem_status >= INIT_SEM_PAIR_OF_FORKS)
		sem_close(sim_data->fork);
	if (init_sem_status >= INIT_SEM_FORK)
		sem_close(sim_data->print_flag);
	if (init_sem_status >= INIT_SEM_PRINT_FLAG)
		sem_close(sim_data->philo_count_reached_eat_limit);
	if (init_sem_status >= INIT_SEM_PHILO_COUNT_REACHED_EAT_LIMIT)
		sem_close(sim_data->stop_flag);
	if (init_sem_status >= INIT_SEM_STOP_FLAG)
		sem_close(sim_data->start_flag);
	if (init_sem_status >= INIT_SEM_START_FLAG)
		sem_close(sim_data->prepare_flag);
	print_error(ERR_SEM_OPEN);
}

void	_save_sem_addr(
	t_sim_data *sim_data, int init_sem_status, sem_t *sem_addr)
{
	if (init_sem_status == INIT_SEM_PREPARE_FLAG)
		sim_data->prepare_flag = sem_addr;
	else if (init_sem_status == INIT_SEM_START_FLAG)
		sim_data->start_flag = sem_addr;
	else if (init_sem_status == INIT_SEM_STOP_FLAG)
		sim_data->stop_flag = sem_addr;
	else if (init_sem_status == INIT_SEM_PHILO_COUNT_REACHED_EAT_LIMIT)
		sim_data->philo_count_reached_eat_limit = sem_addr;
	else if (init_sem_status == INIT_SEM_PRINT_FLAG)
		sim_data->print_flag = sem_addr;
	else if (init_sem_status == INIT_SEM_FORK)
		sim_data->fork = sem_addr;
	else
		sim_data->pair_of_forks = sem_addr;
}

int	init_semaphore(t_sim_data *sim_data)
{
	int		init_sem_status;
	sem_t	*temp_sem_addr;

	init_sem_status = INIT_SEM_PREPARE_FLAG;
	while (init_sem_status <= INIT_SEM_PAIR_OF_FORKS)
	{
		temp_sem_addr = _wrapped_sem_open(sim_data, init_sem_status);
		if (temp_sem_addr == SEM_FAILED)
			return (_init_semaphore_error(sim_data, init_sem_status), 1);
		_save_sem_addr(sim_data, init_sem_status, temp_sem_addr);
		sem_unlink(_get_sem_name(init_sem_status));
		init_sem_status++;
	}
	return (0);
}
