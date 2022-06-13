/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/13 16:01:12 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *die_thread(void *s_philo)
{
	t_philo *philo;

	philo = (t_philo *)s_philo;
	while (!philo->data->dead)
	{
		if (philo->data->number_of_philosophers == philo->data->philo_eat_turn)
			return (NULL);
		if (get_time_in_ms() - philo->ate_time > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->eat);
			if (!philo->data->dead)
				print_info(philo->first_time, philo, "died", RED);
			philo->data->dead = TRUE;
			pthread_mutex_unlock(&philo->eat);
			return (NULL);
		}
	}
	return (NULL);
}
