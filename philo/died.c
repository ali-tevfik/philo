/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/21 17:57:34 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->data->died_data);
	died = !philo->data->dead;
	pthread_mutex_unlock(&philo->data->died_data);
	return (died);
}

void	*die(t_philo *philo)
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

void	*die_thread(void *s_philo)
{
	t_philo		*philo;
	uint64_t	ate_time;
	int			turn;

	philo = (t_philo *)s_philo;
	while (is_dead(philo))
	{
		pthread_mutex_lock(&philo->data->turn);
		turn = philo->data->philo_eat_turn;
		pthread_mutex_unlock(&philo->data->turn);
		if (philo->data->number_of_philosophers == turn)
			return (NULL);
		pthread_mutex_lock(&philo->ate_time_mutex);
		ate_time = philo->ate_time;
		pthread_mutex_unlock(&philo->ate_time_mutex);
		if (get_time_in_ms() - ate_time > philo->data->time_to_die)
			return (die(philo));
		usleep(100);
	}
	return (NULL);
}
