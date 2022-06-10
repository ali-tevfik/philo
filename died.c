/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/10 17:06:12 by tevfik        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*die_thread(void *s_data)
{
	t_philo	**philo;

	philo = (t_philo **)s_data;
	while (!(*philo)->data->dead)
	{
		pthread_mutex_lock(&(*philo)->data->dead_mutex);
		if ((*philo)->data->philo_eat_turn == (*philo)->data->number_of_philosophers)
		{
			(*philo)->data->dead = TRUE;
			return (NULL);
		}
		pthread_mutex_unlock(&(*philo)->data->dead_mutex);
		pthread_mutex_lock(&(*philo)->eat);
		if (get_time_in_ms() - (*philo)->ate_time > (*philo)->data->time_to_die)
		{
			print_info((*philo)->data->first_time, (*philo), "died", RED);
			pthread_mutex_lock(&(*philo)->data->dead_mutex);
			(*philo)->data->dead = TRUE;
			pthread_mutex_unlock(&(*philo)->data->dead_mutex);
			pthread_mutex_unlock(&(*philo)->eat);
			return (NULL);
		}
		pthread_mutex_unlock(&(*philo)->eat);
	}
	return (NULL);
}
// void	*die_thread(void *s_data)
// {
// 	t_data		**data;
// 	int			i;
// 	uint64_t	now;

// 	data = (t_data **)s_data;
// 	while (!(*data)->dead)
// 	{
// 		now = get_time_in_ms();
// 		i = 0;
// 		while ((*data)->philo[i])
// 		{
// 			if ((*data)->philo_eat_turn == (*data)->number_of_philosophers)
// 			{
// 				(*data)->dead = TRUE;
// 				return (NULL);
// 			}
// 			if (now - (*data)->philo[i]->ate_time > (*data)->time_to_die && !(*data)->philo[i]->is_eat)
// 			{
// 				pthread_mutex_lock(&(*data)->philo[i]->eat);
// 				print_info((*data)->first_time, (*data)->philo[i], "died", RED);
// 				(*data)->dead = TRUE;
// 				pthread_mutex_unlock(&(*data)->philo[i]->eat);
// 				return (NULL);
// 			}
// 			i++;
// 			usleep(100);
// 		}
// 	}
// 	return (data);
// }
