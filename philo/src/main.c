/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:30:47 by akyoshid          #+#    #+#             */
/*   Updated: 2025/02/21 05:56:55 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	int		rv;
	t_data	data;

	rv = proc_data(argc, argv, &data);
	if (rv != 0)
		return (rv);
	printf("data.philo_num: %d\n", data.philo_num);
	printf("data.die_time: %d\n", data.die_time);
	printf("data.eat_time: %d\n", data.eat_time);
	printf("data.sleep_time: %d\n", data.sleep_time);
	printf("data.eat_limit: %d\n", data.eat_limit);
	return (PHILO_SUCCESS);
}
