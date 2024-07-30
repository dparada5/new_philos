/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:05:15 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 10:17:30 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_init_mutex(t_data *data)
{
	int		i;
	t_fork	*fork;

	i = 0;
	ft_mutex(data, INIT, &data->dead_lock);
	ft_mutex(data, INIT, &data->meal_lock);
	ft_mutex(data, INIT, &data->write_lock);
	data->fork_t = malloc(sizeof(t_fork) * data->number_of_philos);
	if (!data->fork_t)
		printf("error");
	while (i < data->number_of_philos)
	{
		fork = data->fork_t + i;
		ft_mutex(data, INIT, &fork->fork);
		fork->id = i + 1;
		i++;
	}
}

void	ft_init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (!data->error && i < data->number_of_philos)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->data = data;
		philo->meals = 0;
		philo->full = 0;
		philo->dead_flag = &data->dead_flag;
		philo->dead_lock = &data->dead_lock;
		philo->meal_lock = &data->meal_lock;
		philo->write_lock = &data->write_lock;
		philo->last_meal = 0;
		philo->r_fork = &data->fork_t[i];
		philo->l_fork = &data->fork_t[(i + 1) % data->number_of_philos];
		i++;
	}
}
