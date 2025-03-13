/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_action_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:42 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/13 10:17:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

// The value returned is
// 1 if the time required for the given action has already passed,
// and 0 if not.
int	check_action_status(t_sim_data *sim_data, int action, long start_timestamp)
{
	long	timelimit;
	long	current_timestamp;

	if (action == ACTION_EAT)
		timelimit = sim_data->eat_time;
	else if (action == ACTION_SLEEP)
		timelimit = sim_data->sleep_time;
	else
		return (1);
	current_timestamp = get_timestamp(sim_data);
	if (current_timestamp - start_timestamp >= timelimit)
		return (1);
	else
		return (0);
}
