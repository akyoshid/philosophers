/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:01:20 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 08:42:02 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	philo_think(t_sim_data *sim_data, t_philo_data *philo_data)
{
	print_log(sim_data, philo_data, ACTION_THINK, NULL);
	sem_wait(philo_data->eat_flag);
}
