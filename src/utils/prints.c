/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:46:28 by dparada           #+#    #+#             */
/*   Updated: 2024/07/23 15:38:40 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	printf_philos(t_data *data, char *str)
{
	t_philo	*aux;
	int		i;

	i = 0;
	aux = data->philo;
	if (str)
		printf("%s\n", str);
	while (i < data->number_of_philos)
	{
		printf("id %d of philo\n", aux->id);
		i++;
		aux = data->philo + i;
	}
}

void	printf_data(t_data *data, char *str)
{
	if (str)
		printf("En %s\n", str);
	printf("NPS:\t%d\n", data->number_of_philos);
	printf("TOD:\t%d\n", data->time_of_death);
	printf("TTE:\t%d\n", data->time_to_eat);
	printf("TTS:\t%d\n", data->time_to_sleep);
	printf("NMS:\t%d\n", data->number_of_meals);
}
