/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:18:43 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:35 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//revisar leaks
void	*ft_monitor(void *aux)
{
	t_data	*data;
	t_philo	*philo;
	int		start;
	int		i;

	data = (t_data *) aux;
	while (!get_mutex_int(data, philo, 0))
	{
		i = -1;
		while (++i < data->number_of_philos && !get_mutex_int(data, philo, 0))
		{
			philo = data->philo + i;
			ft_monitor_mutex(data, MEALS, philo, 1);
			start = get_time() - data->start;
			if ((start - get_mutex_int(data, philo, 1)) > \
				data->time_of_death)
			{
				ft_write(philo, DIED);
				ft_monitor_mutex(data, DEATH, philo, 0);
			}
			if (data->full == data->number_of_philos)
				ft_monitor_mutex(data, DEATH, philo, 0);
		}
	}
	return (NULL);
}
