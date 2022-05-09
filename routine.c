/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:25:13 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/09 14:23:01 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void to_sleep(t_philo *philo)
{
   
    t_data *data;

    data = ((t_data *)philo->data);
    usleep(data->time_to_sleep * 1000);
    pthread_mutex_lock(&philo->print);
    printf(BLUE);
    printf("[%d]to_sleep %d\n",philo->index,data->time_to_sleep);
    pthread_mutex_unlock(&philo->print);
}

void to_eat(t_philo *philo)
{
   
    t_data *data;

    data = ((t_data *)philo->data);
    pthread_mutex_lock(&philo->fork); //index l_fork
    printf(PURPLE);
    printf("%d has taken l fork\n", philo->index);
    pthread_mutex_lock(&philo->data->philo[(philo->index) % philo->data->number_of_philosophers]->fork); //r_fork
    printf("%d has taken r fork\n", philo->index);
    die(philo);
    philo->ate_time = get_time_in_ms();
    usleep(data->time_to_eat  * 1000);
    printf(GREEN);
    printf("[%d]to_eat %d\n",philo->index,data->time_to_eat);
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->data->philo[(philo->index) % philo->data->number_of_philosophers]->fork);
}

void die(t_philo *philo)
{
    t_data *data;
    uint64_t	entry;
    uint64_t result;

    data = ((t_data *)philo->data);
	entry = get_time_in_ms();
    result = entry - philo->ate_time;

     if ( result > data->time_to_die)
    {
        printf(RED);
        printf("[%d] die\n",philo->index);
        philo->data->dead = true;
        exit(-1);
    }
}

void *routine(void *s_data)
{
    t_philo **philo = (t_philo **)s_data;
    
    while (!(*philo)->data->dead)
    {
        to_eat(*philo);
        to_sleep(*philo);
        printf(YELLOW);
        printf("[%d]is thinking\n",(*philo)->index);
    }
    return (philo);
}
