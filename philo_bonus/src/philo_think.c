/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:01:20 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:25:20 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

// A philosopher continues thinking until they acquire two forks.
// While thinking, a philosopher may die of starvation.
// If, within _take_fork(), another thread has already locked the mutex,
// 	causing pthread_mutex_lock() to block,
// 	the philosopher will be stuck in a blocked state.
// This means that even if the starvation timeout is reached,
// 	the philosopher cannot proceed to the dying process
// 	because they remain blocked.
// Ideally, pthread_mutex_trylock() should be used
// 	so that if another thread has already locked the mutex,
// 	the function returns immediately without entering a blocking state.
// This way,
// 	the philosopher would still be able to die properly when the time comes.
// However, pthread_mutex_trylock() is not among the allowed functions
// 	specified in the subject, making such a clean solution impossible.
// To work around this, I set the think_time in such a way that
// 	the maximum interval between meals across all philosophers is minimized,
// 	ensuring that all philosophers maintain a consistent eating cycle.
// Using this think_time, each philosopher can predict
// 	when they will be able to acquire both forks and eat.
// Until that time, they do not attempt to lock the fork mutexes
// 	and instead perform a busy wait
// 	while periodically checking their alive status with check_alive().

int	philo_think(t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (print_log(philo_data, ACTION_THINK, &start_timestamp) == STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_action_status(
				philo_data, start_timestamp, philo_data->sim_data->think_time);
	}
	return (status);
}

int	philo_first_think(t_philo_data *philo_data)
{
	int		status;
	long	start_timestamp;

	status = STATUS_CONTINUE;
	if (print_log(philo_data, ACTION_THINK, &start_timestamp) == STATUS_STOP)
		status = STATUS_STOP;
	while (status == STATUS_CONTINUE)
	{
		usleep(100);
		status = check_action_status(
				philo_data, start_timestamp, philo_data->first_think_time);
	}
	return (status);
}
