/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:28:23 by dparada           #+#    #+#             */
/*   Updated: 2024/07/29 15:00:32 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_init_data(t_data *data, char **argv)
{
	if (data->error)
		return (-1);
	data->dead_flag = 0;
	data->number_of_philos = ft_atol(data, argv[1]);
	data->time_of_death = ft_atol(data, argv[2]);
	data->time_to_eat = ft_atol(data, argv[3]);
	data->time_to_sleep = ft_atol(data, argv[4]);
	data->full = 0;
	if (argv[5])
		data->number_of_meals = ft_atol(data, argv[5]);
	else
		data->number_of_meals = -2;
	if (!data->error && data->number_of_meals == 0 )
		data->error = 1;
	if (!data->error && !data->number_of_philos)
		ft_msj_error(data, "Can't have 0 philos", 0);
	else if (!data->error && data->number_of_philos > 200)
		ft_msj_error(data, "Can't have more than 200 philos", 0);
	data->philo = malloc(sizeof(t_philo) * (data->number_of_philos + 1));
	if (!data->philo)
		ft_msj_error(data, "MALLOC FAILED", 0);
	ft_init_mutex(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->error = 0;
	if (argc != 5 && argc != 6)
		ft_msj_error(data, NULL, 1);
	ft_init_data(data, argv);
	ft_init_philos(data);
	if (!data->error && !ft_check_philos(data))
	{
		pthread_join(data->philo->thread, NULL);
		ft_mutex(data, DESTROY, &data->philo->r_fork->fork, 0);
		ft_free(data);
		return (0);
	}
	ft_init_thread(data, 0);
	ft_free(data);
}
