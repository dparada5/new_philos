/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:34:12 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:16:05 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long long	ft_fatoi(t_data *data, int i, long long n, const char *str)
{
	while (str[i])
	{
		if (!data->error && (str[i] > '9' || str[i] < '0') && str[i] != '+')
			ft_msj_error(data, "Invalid arguements", 0);
		i++;
	}
	i = 0;
	if (!data->error && str[i] == '+' && \
		(str[i + 1] <= '9' && str[i + 1] >= '0'))
		i++;
	else if (!data->error && str[i] == '+' && (str[i] > '9' || str[i] < '0'))
		ft_msj_error(data, "Invalid arguements", 0);
	while (!data->error && str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (n);
}

long long	ft_atol(t_data *data, const char *str)
{
	int			i;
	long long	n;
	long long	resul;

	i = 0;
	n = 0;
	resul = ft_fatoi(data, i, n, str);
	if ((resul > 2147483647 || resul < 0) && resul != -1)
		ft_msj_error(data, "Invalid arguments", 0);
	return (resul);
}

int	ft_msj_error(t_data *data, char *str, int u)
{
	if (u)
	{
		printf("./philo [NOP] [TTD] [TTE] [TTS] [NTPME]\n");
		printf("NOP: Nº of Philosophers.\n");
		printf("TTD: Time to die.\n");
		printf("TTE: Time to eat.\n");
		printf("TTS: Time to sleep.\n");
		printf("NTPM: Number of meals. [Optional]\n");
	}
	else if (str)
		printf("%s\n", str);
	data->error = 1;
	return (-1);
}

int	get_mutex_int(t_data *data, t_philo *philo, int option)
{
	int	aux;

	if (!option)
	{
		ft_mutex(data, LOCK, &data->dead_lock);
		aux = data->dead_flag;
		ft_mutex(data, UNLOCK, &data->dead_lock);
	}
	else if (option)
	{
		ft_mutex(data, LOCK, &data->meal_lock);
		aux = philo->last_meal;
		ft_mutex(data, UNLOCK, &data->meal_lock);
	}
	return (aux);
}

void	ft_free(t_data *data)
{
	if (data->philo || data->fork_t)
	{
		if (data->philo)
			free(data->philo);
		if (data->fork_t)
			free(data->fork_t);
		free(data);
	}
}
