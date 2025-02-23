/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:47 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/23 07:43:59 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_sim_data	sim_data;

	if (init_sim_data(argc, argv, &sim_data) != 0)
		return (PHILO_SYNTAX_ERROR);
	// init_mutex
	if (exec_sim(&sim_data) != 0)
		return (PHILO_GENERAL_ERROR);
	// clean_up_mutex
	return (PHILO_SUCCESS);
}
