/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eat_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:11:05 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 10:25:37 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	check_eat_count(t_sim_data *sim_data, t_philo_data *philo_data)
{
	philo_data->eat_count++;
	if (sim_data->eat_limit == philo_data->eat_count)
	{
		sem_wait(sim_data->print_flag);
		sem_post(sim_data->philo_count_reached_eat_limit);
	}
}
