/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:43:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 06:46:44 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	start_philo_routine(t_sim_data *sim_data, t_philo_data *philo_data)
{
	sem_wait(philo_data->start_flag);
	while (1)
	{
		philo_think(sim_data, philo_data);
		philo_eat(sim_data, philo_data);
		philo_sleep(sim_data, philo_data);
	}
}
