/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:20:47 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/30 11:13:00 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_data *data, int i)
{
	if (pthread_mutex_init(&data->philo[i]->fork, NULL) != 0)
	{
		perror("\n mutex init failed\n");
		return (FALSE);
	}
	return (TRUE);
}

int	init_philo_mutex(t_data *data)
{
	int	i;

	data->philo = (t_philo **)malloc(sizeof(t_philo *)
			* (data->number_of_philosophers + 1));
	if (!data->philo)
		return (FALSE);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (FALSE);
		data->philo[i]->index = i + 1;
		data->philo[i]->data = data;
		data->philo[i]->is_eat = FALSE;
		data->philo[i]->ate_circle = 0;
		data->philo[i]->ate_time = get_time_in_ms();
		if (!create_mutex(data, i))
			return (FALSE);
		i++;
	}
	data->philo[i] = NULL;
	return (TRUE);
}

int	fill_data(char **argv, t_data *data)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->philo_eat_turn = 0;
	data->dead = FALSE;
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		perror("\n mutex init failed\n");
		return (FALSE);
	}
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (init_philo_mutex(data));
}

int	create_thread(t_data *data)
{
	int	i;
	int	x;
	int	j;

	j = 0;
	x = 0;
	i = data->number_of_philosophers;
	data->first_time = get_time_in_ms();
	while (i > x)
	{
		if (pthread_create(&data->philo[x]->thread, NULL,
				routine, &data->philo[x]) != 0)
			return (FALSE);
		usleep(100);
		pthread_detach(data->philo[x]->thread);
		x++;
	}
	if (pthread_create(&data->check_dead, NULL, die_thread, &data) != 0)
		return (FALSE);
	pthread_join(data->check_dead, NULL);
	return (TRUE);
}
