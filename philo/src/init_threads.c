/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:42:20 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:29:49 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_dinner(void *aux)
{
	t_philo	*philo;

	philo = (t_philo *) aux;
	if (!(philo->id % 2))
		ft_sleep(50);
	while (!get_mutex_int(philo->data, philo, 0) && !philo->full)
	{
		ft_less_line_mutex(philo, FORKS, 1);
		ft_write(philo, EAT);
		ft_monitor_mutex(philo->data, MEALS, philo, 0);
		ft_sleep(philo->data->time_to_eat);
		ft_less_line_mutex(philo, FORKS, 0);
		ft_write(philo, SLEEP);
		ft_sleep(philo->data->time_to_sleep);
		ft_write(philo, THINK);
	}
	return (NULL);
}

void	ft_init_thread(t_data *data, int i)
{
	t_philo	*aux;

	if (data->error)
		return ;
	data->start = get_time();
	aux = data->philo;
	while (!data->error && i < data->number_of_philos)
	{
		ft_thread(CREATE, ft_dinner, aux, 0);
		i++;
		aux = data->philo + i;
	}
	ft_thread(CREATE, ft_monitor, data, 1);
	i = 0;
	while (i < data->number_of_philos)
	{
		aux = data->philo + i;
		ft_thread(JOIN, NULL, aux, 0);
		i++;
	}
	ft_thread(JOIN, NULL, data, 1);
	ft_clean_mutex(data);
}
