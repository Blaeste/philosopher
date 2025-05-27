/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:08:31 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:41:58 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_create_philos_threads(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->args.nbr_p)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&ft_life_cycle, &data->philos[i]))
			return (ft_error_msg("thread create"));
	}
	return (0);
}

int	ft_launch_threads(t_data *data)
{
	if (ft_create_philos_threads(data))
		return (ft_error_msg("philos create"));
	if (pthread_create(&data->monitor_id, NULL, &ft_monitor, data))
		return (ft_error_msg("monitor create"));
	return (0);
}
