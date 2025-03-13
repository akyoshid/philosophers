/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:45:37 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 10:32:23 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	philo_sleep(t_sim_data *sim_data, t_philo_data *philo_data)
{
	long	start_timestamp;

	print_log(sim_data, philo_data, ACTION_SLEEP, &start_timestamp);
	while (1)
	{
		usleep(500);
		if (check_action_status(sim_data, ACTION_SLEEP, start_timestamp) == 1)
			break ;
	}
}
