/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:00:17 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/10 02:32:17 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clean_up_semaphore(t_sim_data *sim_data, int philo_count)
{
	int	i;

	sem_close(sim_data->start_flag);
	sem_close(sim_data->stop_flag);
	sem_close(sim_data->philo_count_reached_eat_limit);
	sem_close(sim_data->print_flag);
	sem_close(sim_data->fork);
	sem_close(sim_data->pair_of_forks);
	i = 0;
	while (i < philo_count)
	{
		sem_close(sim_data->philo_data[i].eat_flag);
		i++;
	}
}
