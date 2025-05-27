/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:53:32 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:20:07 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_all_ate(t_data *data)
{
	int	i;
	int	done;

	if (data->args.nbr_meal == 0)
		return (0);
	i = -1;
	while (++i < data->args.nbr_p)
	{
		pthread_mutex_lock(&data->philos[i].meals_m);
		done = data->philos[i].meals_eaten >= data->args.nbr_meal;
		pthread_mutex_unlock(&data->philos[i].meals_m);
		if (!done)
			return (0);
	}
	return (1);
}

static int	ft_check_death(t_data *data, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->meals_m);
	if (data->args.nbr_meal > 0 && philo->meals_eaten >= data->args.nbr_meal)
	{
		pthread_mutex_unlock(&philo->meals_m);
		return (0);
	}
	time = ft_get_timestamp(data) - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meals_m);
	if (time >= data->args.t_to_die)
	{
		pthread_mutex_lock(&data->dead_m);
		if (!data->dead)
			data->dead = 1;
		pthread_mutex_unlock(&data->dead_m);
		pthread_mutex_lock(&data->print_m);
		ft_print_state(philo, "died", DIED);
		pthread_mutex_unlock(&data->print_m);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		if (ft_all_ate(data))
		{
			pthread_mutex_lock(&data->dead_m);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_m);
			return (NULL);
		}
		if (ft_is_dead(data))
			return (NULL);
		i = -1;
		while (++i < data->args.nbr_p)
			if (ft_check_death(data, &data->philos[i]))
				return (NULL);
		usleep(100);
	}
	return (NULL);
}
