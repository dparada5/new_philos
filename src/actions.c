/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:01:20 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 12:47:42 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_write(t_philo *philo, t_lock action, int write)
{
	int	time;

	time = get_time() - philo->data->start;
	if (get_mutex_int(philo->data, philo, 0))
		return ;
	pthread_mutex_lock(philo->write_lock);
	if (action == L_FORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	else if (action == R_FORK)
		printf("%d %d has taken a fork\n", time, philo->id);
	else if (action == EAT)
		printf("%d %d is eating\n", time, philo->id);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", time, philo->id);
	else if (action == THINK)
		printf("%d %d is thinking\n", time, philo->id);
	else if (action == DIED)
		printf("%d %d died\n", time, philo->id);
	(void) write;
	pthread_mutex_unlock(philo->write_lock);
}
