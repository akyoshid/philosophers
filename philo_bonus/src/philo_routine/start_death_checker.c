/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_death_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:40:27 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/15 19:15:50 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	*start_death_checker(void *arg)
{
	t_philo_data	*philo_data;
	t_sim_data		*sim_data;
	long			timestamp;

	philo_data = (t_philo_data *)arg;
	sim_data = philo_data->sim_data;
	sem_wait(philo_data->start_death_checker_flag);
	while (1)
	{
		usleep(500);
		sem_wait(sim_data->print_flag);
		sem_wait(philo_data->last_eat_timestamp.s);
		timestamp = get_timestamp(sim_data);
		if (timestamp - philo_data->last_eat_timestamp.t >= sim_data->die_time)
		{
			printf("%ld %d died\n", timestamp / 1000, philo_data->philo_id);
			set_stop_flag(sim_data);
		}
		sem_post(philo_data->last_eat_timestamp.s);
		sem_post(sim_data->print_flag);
	}
	return (NULL);
}
