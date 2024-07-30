/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:25:45 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:25 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_philos(t_data *data)
{
	data->start = get_time();
	if (data->number_of_philos == 1)
		ft_thread(CREATE, ft_one_dinner, data->philo, 0);
	else
		return (1);
	return (0);
}

void	*ft_one_dinner(void *aux)
{
	t_philo	*philo;

	philo = (t_philo *)aux;
	ft_mutex(philo->data, LOCK, &philo->r_fork->fork);
	ft_write(philo, R_FORK);
	ft_mutex(philo->data, UNLOCK, &philo->r_fork->fork);
	ft_sleep(philo->data->time_of_death);
	ft_write(philo, DIED);
	return (NULL);
}
