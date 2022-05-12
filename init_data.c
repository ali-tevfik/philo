/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:20:47 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/12 16:30:35 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_mutex(t_data *data)
{
	int	i;

	data->philo = protect_double_t_philo(data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i] = protect_t_philo();
		data->philo[i]->index = i + 1;
		data->philo[i]->data = data;
		data->philo[i]->is_eat = false;
		data->philo[i]->ate_circlu = 0;
		data->philo[i]->ate_time = get_time_in_ms();
		if (pthread_mutex_init(&data->philo[i]->fork, NULL) != 0)
		{
			perror("\n mutex init failed\n");
			exit(1);
		}
		i++;
	}
	data->philo[i] = NULL;
}

void	fill_data(char **argv, t_data *data)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->first_time = get_time_in_ms();
	data->dead = false;
	data->is_number_of_times_each_philosopher_must_eat = true;
	data->number_of_philosophers = ft_atoi(argv[1]);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->is_number_of_times_each_philosopher_must_eat = false;
	init_philo_mutex(data);
}

void	create_thread(t_data *data)
{
	int	i;
	int	x;
	int	j;

	j = 0;
	x = 0;
	i = data->number_of_philosophers;
	while (i > x)
	{
		if (pthread_create(&data->philo[x]->thread, NULL,
				routine, &data->philo[x]) != 0)
			exit(-1);
		x++;
		usleep(100);
	}
	if (pthread_create(&data->check_dead, NULL, die_thread, &data) != 0)
		exit(-1);
	pthread_join(data->check_dead, NULL);
	while (j < x)
	{
		pthread_join(data->philo[j]->thread, NULL);
		j++;
	}
	printf("main\n");
	free_data(data);
}
