/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 07:45:16 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:24:45 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
	return (current_time);
}

long	get_timestamp(t_sim_data *sim_data)
{
	long	current_time;

	current_time = get_current_time();
	return (current_time - sim_data->start_time);
}
