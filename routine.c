/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 12:25:13 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/13 17:38:28 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(u_int64_t time, t_philo *philo, char *txt, char *COLORCODE)
{
	uint64_t	nu;
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&data->print);
	nu = get_time_in_ms();
	printf("%s[%llu] [%d] %s\n" WHITE, COLORCODE, nu - time, philo->index, txt);
	pthread_mutex_unlock(&data->print);
}

void	to_eat(t_philo *philo)
{
	t_data	*data;

	data = ((t_data *)philo->data);
	if (!is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->fork);
	print_info(philo->data->first_time, philo,
		"has taken l fork", PURPLE);
	pthread_mutex_lock(&philo->data->philo[(philo->index)
		% philo->data->number_of_philosophers]->fork);
	print_info(philo->data->first_time, philo,
		"has taken r fork", PURPLE);
	pthread_mutex_lock(&philo->eat);
	philo->is_eat = TRUE;
	philo->ate_circle++;
	pthread_mutex_lock(&philo->ate_time_mutex);
	philo->ate_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->ate_time_mutex);
	print_info(philo->data->first_time, philo, "is eating", GREEN);
	smart_sleep(data->time_to_eat);
	philo->is_eat = FALSE;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->data->philo[(philo->index)
		% philo->data->number_of_philosophers]->fork);
}

void	*routine(void *s_data)
{
	t_philo	*philo;
	int		x;

	philo = (t_philo *)s_data;
	x = 0;
	while (is_dead(philo))
	{
		to_eat(philo);
		if (philo->ate_circle
			== philo->data->must_eat)
		{
			philo->data->philo_eat_turn++;
			return (NULL);
		}
		if (!is_dead(philo))
			return (NULL);
		print_info(philo->data->first_time, philo, "is sleeping", BLUE);
		smart_sleep(philo->data->time_to_sleep);
		print_info(philo->data->first_time, philo,
			"is thinking", YELLOW);
	}
	return (NULL);
}
