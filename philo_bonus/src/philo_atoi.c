/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:51:09 by akyoshid          #+#    #+#             */
/*   Updated: 2025/03/07 07:25:09 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// === DESCRIPTION ===
// Convert a string of digits into a positive integer value. 
// If it contains non-numeric characters, return -2.
// If it was a negative number or bigger than INT_MAX, return -1.

#include "../inc/philo_bonus.h"

int	_check_non_integer(char const *str)
{
	if (*str == '-')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	return (0);
}

int	philo_atoi(char const *str)
{
	int	num;

	if (_check_non_integer(str) != 0)
		return (-2);
	if (*str == '-')
		return (-1);
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (num > INT_MAX / 10 || (num == INT_MAX / 10 && *str >= '8'))
			return (-1);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}
