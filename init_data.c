/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:20:47 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/09 17:30:44 by adoner        ########   odam.nl         */
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
        data->philo[i]->ate_circlu = 0;
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

bool check_argument(char **argv)
{
   int  i;
   
   i = 1;
   if (!is_digit(argv))
    {
        printf("Error:No Digit!\n");
        return(false);
    }
   while(argv[i])
   {
        if (ft_atoi(argv[i]) <= 0)
        {
            printf("Error: Invalid argument!\n");
            return (false);
        }
        i++;
   }
    return (true);
}

void   fill_data(char **argv, t_data *data)
{
    if (!check_argument(argv))
        exit(-1);
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