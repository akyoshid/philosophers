/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:00:17 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/12 14:44:25 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clean_up_semaphore(t_sim_data *sim_data, int philo_num_opened_sem)
{
	int	i;

	sem_close(sim_data->stop_flag);
	sem_close(sim_data->philo_count_reached_eat_limit);
	sem_close(sim_data->print_flag);
	sem_close(sim_data->fork);
	sem_close(sim_data->pair_of_forks);
	sem_close(sim_data->os_data.start_flag);
	i = 0;
	while (i < philo_num_opened_sem)
	{
		sem_close(sim_data->philo_data[i].start_flag);
		sem_close(sim_data->philo_data[i].eat_flag);
		i++;
	}
}
