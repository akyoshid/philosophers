/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 05:30:50 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	sem_wait(philo_data->start_flag);
	while (1)
	{
		if (philo_think(sim_data, philo_data) == STATUS_STOP)
			break ;
		if (philo_eat(sim_data, philo_data) == STATUS_STOP)
			break ;
		if (philo_sleep(sim_data, philo_data) == STATUS_STOP)
			break ;
	}
}
