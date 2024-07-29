/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:25:45 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 15:00:27 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_philos(t_data *data)
{
	data->start = get_time();
	if (data->number_of_philos == 1)
		pthread_create(&data->philo->thread, NULL, ft_one_dinner, \
		(void *)data->philo);
	else
		return (1);
	return (0);
}

void	*ft_one_dinner(void *aux)
{
	t_philo	*philo;

	philo = (t_philo *)aux;
	pthread_mutex_lock(&philo->r_fork->fork);
	ft_write(philo, R_FORK, 1);
	pthread_mutex_unlock(&philo->r_fork->fork);
	ft_sleep(philo->data->time_of_death);
	ft_write(philo, DIED, 1);
	return (NULL);
}
