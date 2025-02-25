/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:29:12 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/25 22:23:52 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_alive(t_philo_data *philo_data, bool have_super_flag, long timestamp)
{
	int	status;

	if (have_super_flag == false)
	{
		pthread_mutex_lock(&philo_data->sim_data->super_flag.m);
		timestamp = get_timestamp(philo_data->sim_data);
	}
	if (philo_data->sim_data->super_flag.stop_flag == true)
		status = STATUS_STOP;
	else if (timestamp - philo_data->last_eat_timestamp
		>= philo_data->sim_data->die_time)
	{
		philo_data->sim_data->super_flag.stop_flag = true;
		ft_printf("%d %d died\n", timestamp, philo_data->philo_id);
		status = STATUS_STOP;
	}
	else
		status = STATUS_SUCCESS;
	if (have_super_flag == false)
		pthread_mutex_unlock(&philo_data->sim_data->super_flag.m);
	return (status);
}
