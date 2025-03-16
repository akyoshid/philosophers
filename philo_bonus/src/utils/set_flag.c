/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:15:03 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/16 09:16:01 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo_bonus.h"

// Hold the print_flag before calling this function.
void	set_error_flag(t_sim_data *sim_data)
{
	sem_post(sim_data->error_flag);
	while (1)
		usleep(UINT_MAX);
}

// Hold the print_flag before calling this function.
void	set_stop_flag(t_sim_data *sim_data)
{
	sem_post(sim_data->stop_flag);
	while (1)
		usleep(UINT_MAX);
}
