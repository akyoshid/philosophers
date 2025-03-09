/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:00:17 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/09 10:35:17 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clean_up_semaphore(t_sim_data *sim_data, int philo_count)
{
	int	i;

	sem_close(sim_data->super_flag.s);
	sem_close(sim_data->fork.s);
	i = 0;
	while (i < philo_count)
	{
		sem_close(sim_data->philo_data[i].eat_flag.s);
		i++;
	}
}
