/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:00:17 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:24:37 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	clean_up_mutex(t_sim_data *sim_data, int fork_count)
{
	int	i;

	pthread_mutex_destroy(&sim_data->super_flag.m);
	i = 0;
	while (i < fork_count)
	{
		pthread_mutex_destroy(&sim_data->fork[i].m);
		i++;
	}
}
