/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:18:33 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/26 11:37:27 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->data->args.nbr_p == 1)
		return (ft_onephilo(philo));
	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		second = philo->right_fork;
		first = philo->left_fork;
	}
	pthread_mutex_lock(first);
	ft_print_state(philo, "has taken a fork", FORK);
	if (ft_is_dead(philo->data))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	ft_print_state(philo, "has taken a fork", FORK);
	return (0);
}

static void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_m);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_m);
	ft_print_state(philo, "is eating", EATING);
	ft_smart_sleep(philo->data->args.t_to_eat, philo->data);
	pthread_mutex_lock(&philo->meals_m);
	philo->last_meal_time = ft_get_timestamp(philo->data);
	pthread_mutex_unlock(&philo->meals_m);
	ft_drop_forks(philo);
}

static void	ft_sleep_and_think(t_philo *philo)
{
	ft_print_state(philo, "is sleeping", SLEEPING);
	ft_smart_sleep(philo->data->args.t_to_sleep, philo->data);
	ft_print_state(philo, "is thinking", THINKING);
	if (philo->data->args.t_to_die <= philo->data->args.t_to_eat
		+ philo->data->args.t_to_sleep && philo->data->args.nbr_p % 2 == 0)
		ft_smart_sleep(philo->data->args.t_to_eat / 2, philo->data);
	if (philo->data->args.nbr_p % 2 != 0)
		ft_smart_sleep(philo->data->args.t_to_eat, philo->data);
}

void	*ft_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_is_dead(philo->data))
	{
		if (ft_take_forks(philo))
			break ;
		ft_eat(philo);
		pthread_mutex_lock(&philo->meals_m);
		if (philo->data->args.nbr_meal > 0
			&& philo->meals_eaten >= philo->data->args.nbr_meal)
		{
			pthread_mutex_unlock(&philo->meals_m);
			break ;
		}
		pthread_mutex_unlock(&philo->meals_m);
		ft_sleep_and_think(philo);
	}
	return (NULL);
}
