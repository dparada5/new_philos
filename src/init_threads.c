/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:42:20 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 13:14:24 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_sleep(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(10);
}

void	*ft_dinner(void *aux)
{
	t_philo	*philo;

	philo = (t_philo *) aux;
	if (!(philo->id % 2))
		ft_sleep(50);
	while (!get_mutex_int(philo->data, philo, 0) && !philo->full)
	{
		ft_less_line_mutex(philo, FORKS, 1);
		ft_write(philo, EAT, 1);
		ft_monitor_mutex(philo->data, MEALS, philo, 0);
		ft_sleep(philo->data->time_to_eat);
		ft_less_line_mutex(philo, FORKS, 0);
		ft_write(philo, SLEEP, 1);
		ft_sleep(philo->data->time_to_sleep);
		ft_write(philo, THINK, 1);
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
	while (i < data->number_of_philos)
	{
		pthread_create(&aux->thread, NULL, ft_dinner, (void *)aux);
		i++;
		aux = data->philo + i;
	}
	pthread_create(&data->monitor, NULL, ft_monitor, (void *) data);
	i = 0;
	while (i < data->number_of_philos)
	{
		aux = data->philo + i;
		pthread_join(aux->thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		aux = data->philo + i;
		// pthread_join(aux->thread, NULL);
		ft_mutex(data, DESTROY, &aux->r_fork->fork, 0);
		i++;
	}
	ft_mutex(data, DESTROY, &data->meal_lock, 0);
	ft_mutex(data, DESTROY, &data->dead_lock, 0);
	ft_mutex(data, DESTROY, &data->write_lock, 1);
	pthread_join(data->monitor, NULL);
}
