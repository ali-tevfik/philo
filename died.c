/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/13 17:07:35 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *die_thread(void *s_philo)
{
	t_philo *philo;
	int		died;
	uint64_t	ate_time;
	
	died = 1;
	philo = (t_philo *)s_philo;
	while (died)
	{
		if (philo->data->number_of_philosophers == philo->data->philo_eat_turn)
			return (NULL);
		pthread_mutex_lock(&philo->ate_time_mutex);
		ate_time = philo->ate_time;
		pthread_mutex_unlock(&philo->ate_time_mutex);
		if (get_time_in_ms() - ate_time > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->eat);
			pthread_mutex_lock(&philo->data->died_data);	
			if (!philo->data->dead)
				print_info(philo->data->first_time, philo, "died", RED);
			philo->data->dead = TRUE;
			pthread_mutex_unlock(&philo->data->died_data);
			pthread_mutex_unlock(&philo->eat);
			return (NULL);
		}
		// usleep(100);
		pthread_mutex_lock(&philo->data->died_data);	
		died = !philo->data->dead;
		pthread_mutex_unlock(&philo->data->died_data);	
	}
	return (NULL);
}
