/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:51:53 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/23 06:40:12 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_error(int error_code)
{
	if (error_code == ERR_ARGC)
	{
		ft_dprintf(2,
			"philo: invalid number of arguments\n"
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	else if (error_code == ERR_PTHREAD_CREATE)
		ft_dprintf(2, "philo: pthread_create faild\n");
}
