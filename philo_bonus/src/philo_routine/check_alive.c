/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:29:12 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 05:30:21 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

int	check_alive(t_sim_data *sim_data,
		t_philo_data *philo_data, bool have_super_flag, long timestamp)
{
	int	status;

	if (have_super_flag == false)
	{
		sem_wait(sim_data->super_flag.s);
		timestamp = get_timestamp(sim_data);
	}
	if (sim_data->super_flag.stop_flag == true)
		status = STATUS_STOP;
	else if (timestamp - philo_data->last_eat_timestamp >= sim_data->die_time)
	{
		sim_data->super_flag.stop_flag = true;
		printf("%ld %d died\n", timestamp / 1000, philo_data->philo_id);
		status = STATUS_STOP;
	}
	else
		status = STATUS_SUCCESS;
	if (have_super_flag == false)
		sem_post(sim_data->super_flag.s);
	return (status);
}
