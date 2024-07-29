/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:43:17 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 12:44:28 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_monitor_mutex(t_data *data, t_lock code, t_philo *philo, int option)
{
	if (code == DEATH)
	{
		ft_mutex(data, LOCK, &data->dead_lock, 0);
		data->dead_flag = 1;
		ft_mutex(data, UNLOCK, &data->dead_lock, 0);
	}
	if (code == MEALS && option)
	{
		ft_mutex(data, LOCK, &data->meal_lock, 0);
		if (philo->meals == data->number_of_meals)
		{
			data->full++;
			philo->full = 1;
			philo->meals = 0;
		}
		ft_mutex(data, UNLOCK, &data->meal_lock, 0);
	}
	else if (code == MEALS && !option)
	{
		ft_mutex(data, LOCK, philo->meal_lock, 0);
		philo->last_meal = get_time() - philo->data->start;
		philo->meals++;
		ft_mutex(data, UNLOCK, philo->meal_lock, 0);
	}
}

void	ft_less_line_mutex(t_philo *philo, t_lock code, int option)
{
	if (code == FORKS && option)
	{
		if (philo->id % 2)
		{
			ft_mutex(philo->data, LOCK, &philo->r_fork->fork, 0);
			ft_write(philo, R_FORK, 1);
			ft_mutex(philo->data, LOCK, &philo->l_fork->fork, 0);
			ft_write(philo, L_FORK, 1);
		}
		else
		{
			ft_mutex(philo->data, LOCK, &philo->l_fork->fork, 0);
			ft_write(philo, L_FORK, 1);
			ft_mutex(philo->data, LOCK, &philo->r_fork->fork, 0);
			ft_write(philo, R_FORK, 1);
		}
	}
	else if (code == FORKS && !option)
	{
		ft_mutex(philo->data, UNLOCK, &philo->r_fork->fork, 0);
		ft_mutex(philo->data, UNLOCK, &philo->l_fork->fork, 0);
	}
}
