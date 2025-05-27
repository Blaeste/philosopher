/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:44:49 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/20 14:31:28 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_onephilo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_state(philo, "has taken a fork", FORK);
	while (!ft_is_dead(philo->data))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	ft_is_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_m);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_m);
	return (dead);
}

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->args.nbr_p)
			pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->dead_m);
	pthread_mutex_destroy(&data->print_m);
}

int	ft_clean_exit(t_data *data, int status)
{
	if (data)
	{
		ft_destroy_mutex(data);
		free(data->forks);
		free(data->philos);
	}
	return (status);
}
