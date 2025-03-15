/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:51:53 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/15 21:14:50 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

void	print_error(int error_code)
{
	if (error_code == ERR_ARGC)
	{
		printf(
			"philo_bonus: invalid number of arguments\n"
			"Usage: ./philo_bonus number_of_philosophers time_to_die time_to_"
			"eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	else if (error_code == ERR_PTHREAD_CREATE)
		printf("philo_bonus: pthread_create failed\n");
	else if (error_code == ERR_SEM_OPEN)
		printf("philo_bonus: sem_open failed\n");
	else if (error_code == ERR_FORK)
		printf("philo_bonus: fork failed\n");
	else if (error_code == ERR_ADJUST_START_TIME)
		printf("philo_bonus: _adjust_start_time failed\n");
}
