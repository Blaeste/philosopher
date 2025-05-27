/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:29:49 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:49:12 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_error_msg(const char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(2, "Error: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
	return (1);
}

int	ft_parse_args(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (ft_error_msg("wrong number of arguments"));
	if (!ft_is_number(av[1]) || !ft_is_number(av[2]) || !ft_is_number(av[3])
		|| !ft_is_number(av[4]) || (ac == 6 && !ft_is_number(av[5])))
		return (ft_error_msg("all arguments must be positive integers"));
	data->args.nbr_p = ft_atoi(av[1]);
	data->args.t_to_die = ft_atoi(av[2]);
	data->args.t_to_eat = ft_atoi(av[3]);
	data->args.t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->args.nbr_meal = ft_atoi(av[5]);
	else
		data->args.nbr_meal = 0;
	if (data->args.nbr_p < 1 || data->args.nbr_p > 200)
		return (ft_error_msg("philosophers must be between 1-200"));
	if (data->args.t_to_die < 60 || data->args.t_to_eat < 60
		|| data->args.t_to_sleep < 60)
		return (ft_error_msg("data time must be over 60 ms"));
	if (ac == 6 && data->args.nbr_meal < 1)
		return (ft_error_msg("number of meal must be >= 1"));
	return (0);
}

int	ft_init_data(t_data *data)
{
	int	i;

	data->args.start_time = ft_get_timestamp_now();
	data->dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args.nbr_p);
	data->philos = malloc(sizeof(t_philo) * data->args.nbr_p);
	if (!data->forks || !data->philos)
		return (ft_error_msg("malloc failed"));
	if (pthread_mutex_init(&data->print_m, NULL)
		|| pthread_mutex_init(&data->dead_m, NULL))
		return (ft_error_msg("mutex init failed"));
	i = -1;
	while (++i < data->args.nbr_p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meals_m, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->args.nbr_p];
		data->philos[i].data = data;
	}
	return (0);
}
