/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_start_sim_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:26:44 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:24:16 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	check_super_flag(t_sim_data *sim_data)
{
	int	status;

	pthread_mutex_lock(&sim_data->super_flag.m);
	if (sim_data->super_flag.stop_flag == true)
		status = STATUS_STOP;
	else if (sim_data->super_flag.start_flag == true)
		status = STATUS_SUCCESS;
	else
		status = STATUS_CONTINUE;
	pthread_mutex_unlock(&sim_data->super_flag.m);
	return (status);
}

void	cancel_sim(t_sim_data *sim_data)
{
	pthread_mutex_lock(&sim_data->super_flag.m);
	sim_data->super_flag.stop_flag = true;
	pthread_mutex_unlock(&sim_data->super_flag.m);
}

void	start_sim(t_sim_data *sim_data)
{
	pthread_mutex_lock(&sim_data->super_flag.m);
	sim_data->super_flag.start_flag = true;
	sim_data->start_time = get_current_time();
	pthread_mutex_unlock(&sim_data->super_flag.m);
}
