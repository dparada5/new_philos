/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:14:45 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:36:25 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_thread_error(t_data *data, int error_code, t_code code)
{
	if (error_code == 0)
		return (0);
	if (error_code == EAGAIN)
		ft_msj_error(data, "Insufficient resources to " \
		"create another thread.", 0);
	else if (error_code == EINVAL)
		ft_msj_error(data, "Invalid settings in attr.", 0);
	else if (error_code == EPERM)
		ft_msj_error(data, "No permission to set the scheduling " \
		"policy and parameters specified in attr.", 0);
	else if (error_code == EDEADLK && code == JOIN)
		ft_msj_error(data, "A deadlock was detected or the value " \
		"of thread specifies the calling thread.", 0);
	else if (error_code == ESRCH && code == JOIN)
		ft_msj_error(data, "No thread could be found corresponding " \
		"to that specified by the given thread ID.", 0);
	return (data->error);
}

void	ft_thread(t_code code, void *(*func)(void *), void *aux, int monitor)
{
	t_data	*data;
	t_philo	*philo;

	if (monitor)
	{
		data = (t_data *)aux;
		if (code == CREATE)
			ft_thread_error(data, \
			pthread_create(&data->monitor, NULL, func, (void *)data), code);
		else if (code == JOIN)
			ft_thread_error(data, pthread_join(data->monitor, NULL), code);
	}
	else
	{
		philo = (t_philo *)aux;
		if (code == CREATE)
			ft_thread_error(philo->data, \
			pthread_create(&philo->thread, NULL, func, (void *)philo), code);
		else if (code == JOIN)
			ft_thread_error(philo->data, \
			pthread_join(philo->thread, NULL), code);
	}
}
