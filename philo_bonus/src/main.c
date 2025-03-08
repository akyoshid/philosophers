/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:47 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:25:05 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_sim_data	sim_data;

	if (init_sim_data(argc, argv, &sim_data) != 0)
		return (PHILO_SYNTAX_ERROR);
	if (init_mutex(&sim_data) != 0)
		return (PHILO_GENERAL_ERROR);
	if (exec_sim(&sim_data) != 0)
		return (PHILO_GENERAL_ERROR);
	clean_up_mutex(&sim_data, sim_data.philo_num);
	return (PHILO_SUCCESS);
}
