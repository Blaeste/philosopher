/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:44:20 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:34:16 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print_state(t_philo *philo, const char *msg, t_state state)
{
	long	timestamp;

	if (state == DIED)
	{
		timestamp = ft_get_timestamp(philo->data);
		printf(RED "%ld %d %s" RESET "\n", timestamp, philo->id, msg);
		return ;
	}
	pthread_mutex_lock(&philo->data->print_m);
	if (!ft_is_dead(philo->data))
	{
		timestamp = ft_get_timestamp(philo->data);
		if (state == FORK)
			printf(YELLOW);
		else if (state == EATING)
			printf(GREEN);
		else if (state == SLEEPING)
			printf(CYAN);
		else if (state == THINKING)
			printf(BLUE);
		printf("%ld %d %s" RESET "\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_m);
}
