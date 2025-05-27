/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:50:21 by eschwart          #+#    #+#             */
/*   Updated: 2025/05/21 13:26:51 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint64_t	ft_get_timestamp_now(void)
{
	struct timeval	tv;
	uint64_t		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp);
}

uint64_t	ft_get_timestamp(t_data *data)
{
	struct timeval	tv;
	uint64_t		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp - data->args.start_time);
}

void	ft_smart_sleep(long ms, t_data *data)
{
	uint64_t	start;
	long		remain;

	start = ft_get_timestamp(data);
	remain = ms;
	while (remain > 0)
	{
		if (remain > 1002)
			usleep(998000);
		else if (remain > 5)
			usleep((remain - 2) * 1000);
		else
			usleep(50);
		remain = ms - (ft_get_timestamp(data) - start);
	}
}
