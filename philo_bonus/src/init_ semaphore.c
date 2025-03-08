/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:59:50 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/08 17:34:51 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_semaphore(t_sim_data *sim_data)
{
	sim_data->super_flag.start_flag = false;
	sim_data->super_flag.stop_flag = false;
	sim_data->super_flag.philo_count_reached_eat_limit = 0;
	sim_data->super_flag.s = sem_open("super_flag", O_CREAT | O_EXCL, 0666, 1);
	if (sim_data->super_flag.s == SEM_FAILED)
	{
		print_error(ERR_SEM_OPEN);
		return (1);
	}
	sem_unlink("super_flag");
	sim_data->fork.s = sem_open(
			"fork", O_CREAT | O_EXCL, 0666, sim_data->philo_num);
	if (sim_data->fork.s == SEM_FAILED)
	{
		sem_close(sim_data->super_flag.s);
		print_error(ERR_SEM_OPEN);
		return (1);
	}
	sem_unlink("fork");
	return (0);
}
