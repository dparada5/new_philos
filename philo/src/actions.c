/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:01:20 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:12:53 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_write(t_philo *philo, t_lock action)
{
	int	time;

	time = get_time() - philo->data->start;
	if (get_mutex_int(philo->data, philo, 0))
		return ;
	ft_mutex(philo->data, LOCK, philo->write_lock);
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
	ft_mutex(philo->data, UNLOCK, philo->write_lock);
}

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
