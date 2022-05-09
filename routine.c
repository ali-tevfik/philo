/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:25:13 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/09 17:16:11 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_info(u_int64_t time, int index, char *txt, char *COLORCODE)
{
    uint64_t nu;

    nu = get_time_in_ms();
    printf("%s[%llu] [%d] %s\n"WHITE, COLORCODE,nu - time, index, txt);
}

void to_sleep(t_philo *philo)
{
   
    t_data *data;

    data = ((t_data *)philo->data);
    print_info(philo->data->first_time, philo->index, "to_sleep", BLUE);
    usleep(data->time_to_sleep * 1000);
}

void to_eat(t_philo *philo)
{
   
    t_data *data;

    data = ((t_data *)philo->data);
    // printf("[%d]\n",philo->data->philo[(philo->index) % philo->data->number_of_philosophers]->index);
    pthread_mutex_lock(&philo->fork); //index l_fork
    pthread_mutex_lock(&philo->data->philo[(philo->index) % philo->data->number_of_philosophers]->fork); //r_fork
    print_info(philo->data->first_time, philo->index, "has taken l fork", PURPLE);
    print_info(philo->data->first_time, philo->index, "has taken r fork", PURPLE);
    print_info(philo->data->first_time, philo->index, "to_eat", GREEN);
    philo->ate_time = get_time_in_ms();
    usleep(data->time_to_eat  * 1000);
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->data->philo[(philo->index) % philo->data->number_of_philosophers]->fork);
}



void *routine(void *s_data)
{
    t_philo **philo = (t_philo **)s_data;
    int     x;

    x = 0;
    while (!(*philo)->data->dead)
    {
        to_eat(*philo);
        to_sleep(*philo);
        print_info((*philo)->data->first_time, (*philo)->index, "is thinking", YELLOW);
        if ((*philo)->data->is_number_of_times_each_philosopher_must_eat)
        {
            x++;
            if (x == (*philo)->data->number_of_times_each_philosopher_must_eat)
            {
                return (philo);
            }
        }
        (*philo)->ate_circlu++;
    }
    return (philo);
}
