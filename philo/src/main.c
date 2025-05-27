/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:59:56 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/20 10:34:16 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_wait_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->args.nbr_p)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->monitor_id, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_parse_args(ac, av, &data))
		return (EXIT_FAILURE);
	if (ft_init_data(&data))
		return (ft_clean_exit(&data, EXIT_FAILURE));
	if (ft_launch_threads(&data))
		return (ft_clean_exit(&data, EXIT_FAILURE));
	ft_wait_threads(&data);
	return (ft_clean_exit(&data, EXIT_SUCCESS));
}
