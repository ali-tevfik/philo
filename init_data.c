/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:20:47 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/09 14:15:38 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo_mutex(t_data *data)
{
    data->philo = (t_philo **)malloc(sizeof(t_philo *) * (data->number_of_philosophers + 1));
    if (!data->philo)
        exit(-1);
    int i;

    i = 0;
    while(i < data->number_of_philosophers)
    {
        data->philo[i] = (t_philo *)malloc(sizeof(t_philo));
        data->philo[i]->index = i + 1;
        data->philo[i]->data = data;
        data->philo[i]->ate_time = get_time_in_ms();
        if (!data->philo[i])
            exit(-1);
        if (pthread_mutex_init(&data->philo[i]->fork, NULL) != 0 || pthread_mutex_init(&data->philo[i]->print, NULL) != 0)
        {
            perror("\n mutex init failed\n");
            exit(1);
        }
        i++;
    }
    data->philo[i] = NULL;
}

void   fill_data(char **argv, t_data *data)
{
   
    if (!is_digit(argv))
    {
        printf("no digit!\n");
        exit(1);
    }
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->dead = false;
    data->is_number_of_times_each_philosopher_must_eat = true;
    data->number_of_philosophers = ft_atoi(argv[1]);
    if (argv[5])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else 
        data->is_number_of_times_each_philosopher_must_eat = false;
    init_philo_mutex(data);
}