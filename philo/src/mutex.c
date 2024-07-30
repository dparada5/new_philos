/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:43:17 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:45:04 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_monitor_mutex(t_data *data, t_lock code, t_philo *philo, int option)
{
	if (code == DEATH)
	{
		ft_mutex(data, LOCK, &data->dead_lock);
		data->dead_flag = 1;
		ft_mutex(data, UNLOCK, &data->dead_lock);
	}
	if (code == MEALS && option)
	{
		ft_mutex(data, LOCK, &data->meal_lock);
		if (philo->meals == data->number_of_meals)
		{
			data->full++;
			philo->full = 1;
			philo->meals = 0;
		}
		ft_mutex(data, UNLOCK, &data->meal_lock);
	}
	else if (code == MEALS && !option)
	{
		ft_mutex(data, LOCK, philo->meal_lock);
		philo->last_meal = get_time() - philo->data->start;
		philo->meals++;
		ft_mutex(data, UNLOCK, philo->meal_lock);
	}
}

void	ft_less_line_mutex(t_philo *philo, t_lock code, int option)
{
	if (code == FORKS && option)
	{
		if (philo->id % 2)
		{
			ft_mutex(philo->data, LOCK, &philo->r_fork->fork);
			ft_write(philo, R_FORK);
			ft_mutex(philo->data, LOCK, &philo->l_fork->fork);
			ft_write(philo, L_FORK);
		}
		else
		{
			ft_mutex(philo->data, LOCK, &philo->l_fork->fork);
			ft_write(philo, L_FORK);
			ft_mutex(philo->data, LOCK, &philo->r_fork->fork);
			ft_write(philo, R_FORK);
		}
	}
	else if (code == FORKS && !option)
	{
		ft_mutex(philo->data, UNLOCK, &philo->r_fork->fork);
		ft_mutex(philo->data, UNLOCK, &philo->l_fork->fork);
	}
}

void	error(t_data *data, int error_code, t_code code)
{
	if (error_code == 0)
		return ;
	if (error_code == EINVAL && (code == DESTROY || code == LOCK))
		ft_msj_error(data, "Invalid mutex.", 0);
	if (error_code == EBUSY && code == DESTROY)
		ft_msj_error(data, "The implementation has detected an " \
		"attempt to destroy the object referenced by mutex while " \
		"it is locked or referenced (for example, while being used " \
		"by another thread.", 0);
	if (error_code == EAGAIN)
		ft_msj_error(data, "The system lacked the necessary resources.", 0);
	if (error_code == EDEADLK)
		ft_msj_error(data, "The current thread already owns the mutex.", 0);
	if (error_code == EPERM && code == UNLOCK)
		ft_msj_error(data, "The current thread does not own the mutex.", 0);
}

void	ft_mutex(t_data *data, t_code code, pthread_mutex_t *mutex)
{
	if (code == INIT)
		error(data, pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		error(data, pthread_mutex_destroy(mutex), code);
	if (code == LOCK)
		error(data, pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		error(data, pthread_mutex_unlock(mutex), code);
}

void	ft_clean_mutex(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->number_of_philos)
	{
		philo = data->philo + i;
		ft_mutex(data, DESTROY, &philo->r_fork->fork);
		i++;
	}
	ft_mutex(data, DESTROY, &data->meal_lock);
	ft_mutex(data, DESTROY, &data->dead_lock);
	ft_mutex(data, DESTROY, &data->write_lock);
}
