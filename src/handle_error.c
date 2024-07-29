/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:14:45 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 12:48:56 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_thread_error(t_data *data, int error_code)
{
	if (error_code == EAGAIN)
		ft_msj_error(data, "Insufficient resources " \
		"to create another thread.", 0);
	else if (error_code == EINVAL)
		ft_msj_error(data, "Invalid settings in attr.", 0);
	else if (error_code == EPERM)
		ft_msj_error(data, "No permission to set the scheduling policy \
		and parameters specified in attr.", 0);
	return (data->error);
}

void	error(t_data *data, int error_code, t_code code)
{
	if (error_code == 0)
		return ;
	if (error_code == EINVAL && (code == DESTROY || code == LOCK))
		ft_msj_error(data, "Invalid mutex.", 0);
	if (error_code == EBUSY &&  code == LOCK)
		ft_msj_error(data, "Can't access a busy mutex.", 0);
	if (error_code == EAGAIN)
		ft_msj_error(data, "The system lacked the necessary resources.", 0);
	if (error_code == EDEADLK)
		ft_msj_error(data, "The current thread already owns the mutex.", 0);
}

void	ft_mutex(t_data *data, t_code code, pthread_mutex_t *mutex, int p)
{
	(void) p;
	// if (code == DESTROY && data->number_of_meals == -2 && p)
	// 	error(data, pthread_mutex_unlock(mutex), code);
	if (code == DESTROY)
		error(data, pthread_mutex_destroy(mutex), code);
	if (code == LOCK)
		error(data, pthread_mutex_lock(mutex), LOCK);
	else if (code == UNLOCK)
		error(data, pthread_mutex_unlock(mutex), UNLOCK);
}

// int	ft_handle_mutex(t_philo *philo, pthread_mutex_t *mutex, t_code code)
// {
// 	if (code == LOCK)
// 		ft_mutex_end(philo->data, pthread_mutex_lock(mutex), LOCK, mutex);
// 	if (code == UNLOCK)
// 		ft_mutex_end(philo->data, pthread_mutex_unlock(mutex), UNLOCK, mutex);
// }

// int	ft_mutex_error();