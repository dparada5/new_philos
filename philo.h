/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dparada <dparada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:29:02 by dparada           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:01 by dparada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <errno.h>

typedef struct s_data		t_data;
typedef struct s_philo		t_philo;
typedef struct s_fork		t_fork;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	DESTROY,
	INIT,
	CREATE,
	JOIN,
}			t_code;

typedef enum e_lock
{
	R_FORK,
	L_FORK,
	FORKS,
	EAT,
	SLEEP,
	THINK,
	DIED,
	MEALS,
	DEATH,
}			t_lock;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}				t_fork;

typedef struct s_philo
{
	pthread_t		thread;//in use
	int				id;//in use
	bool			full;//in use
	int				last_meal;//in use
	int				time_to_sleep;//in use
	int				time_to_eat;//in use
	int				meals;//in use
	int				*dead_flag;//in use
	t_fork			*l_fork;//in use
	t_fork			*r_fork;//in use
	pthread_mutex_t	*write_lock;//in use
	pthread_mutex_t	*dead_lock;//in use
	pthread_mutex_t	*meal_lock;//in use
	t_data			*data;//in use
}			t_philo;

typedef struct s_data
{
	int				error;
	int				number_of_philos;//in use
	int				time_of_death;//in use
	int				time_to_eat;//in use
	int				time_to_sleep;//in use
	int				number_of_meals;//in use
	int				full;//in use
	int				start;//in use
	int				dead_flag;//in use
	pthread_t		monitor;//in use
	pthread_mutex_t	dead_lock;//in use
	pthread_mutex_t	meal_lock;//in use
	pthread_mutex_t	write_lock;//in use
	t_fork			*fork_t;//in use
	t_philo			*philo;//in use
}				t_data;
//philo es un array de philos

// int		main(int argc, char **argv);
//----------------------UTILS----------------------------------------
int			ft_msj_error(t_data *data, char *str, int u);
long long	ft_atol(t_data *data, const char *str);
int			get_time(void);
void		ft_sleep(int time);
void		ft_write(t_philo *philo, t_lock action);
void		ft_free(t_data *data);
int			get_mutex_int(t_data *data, t_philo *philo, int option);
//----------------------PHILOS---------------------------------------
void		*ft_one_dinner(void *aux);
int			ft_check_philos(t_data *data);
void		ft_init_philos(t_data *data);
void		ft_init_thread(t_data *data, int i);
//----------------------DATA-----------------------------------------
void		ft_init_mutex(t_data *data);
void		*ft_monitor(void *aux);
void		ft_monitor_mutex(t_data *data, t_lock code, \
t_philo *philo, int option);
void		ft_thread(t_code code, void *(*func)(void *), \
void *aux, int monitor);
//----------------------MUTEX----------------------------------------
void		ft_less_line_mutex(t_philo *philo, t_lock code, int option);
void		ft_mutex(t_data *data, t_code code, pthread_mutex_t *mutex);
void		ft_clean_mutex(t_data *data);
//----------------------BORRAR---------------------------------------
void		printf_data(t_data *data, char *str);
void		printf_philos(t_data *data, char *str);
// void		*routine(void *aux);
#endif