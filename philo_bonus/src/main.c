/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:47 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/12 14:45:18 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_sim_data	sim_data;

	if (init_sim_data(argc, argv, &sim_data) != 0)
		return (PHILO_SYNTAX_ERROR);
	if (init_semaphore(&sim_data) != 0)
		return (PHILO_GENERAL_ERROR);
	if (init_philo_data(&sim_data, sim_data.philo_data) != 0)
		return (PHILO_GENERAL_ERROR);
	if (exec_sim(&sim_data) != 0)
		return (PHILO_GENERAL_ERROR);
	return (PHILO_SUCCESS);
}
