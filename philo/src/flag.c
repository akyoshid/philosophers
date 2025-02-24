/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:01:23 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/24 10:06:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	stop_sim(t_sim_data *sim_data)
{
	pthread_mutex_lock(&sim_data->flag.m);
	sim_data->flag.stop = true;
	pthread_mutex_unlock(&sim_data->flag.m);
}

int	check_flag(t_sim_data *sim_data)
{
	bool	result;

	pthread_mutex_lock(&sim_data->flag.m);
	result = sim_data->flag.stop;
	pthread_mutex_unlock(&sim_data->flag.m);
	return (result);
}
