/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:47 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/22 01:08:47 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	int		rv;
	t_sim_data	sim_data;

	rv = proc_args(argc, argv, &sim_data);
	if (rv != 0)
		return (rv);
	printf("sim_data.philo_num: %d\n", sim_data.philo_num);
	printf("sim_data.die_time: %d\n", sim_data.die_time);
	printf("sim_data.eat_time: %d\n", sim_data.eat_time);
	printf("sim_data.sleep_time: %d\n", sim_data.sleep_time);
	printf("sim_data.eat_limit: %d\n", sim_data.eat_limit);
	return (PHILO_SUCCESS);
}
