/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect_malloc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 11:44:49 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/12 16:32:27 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*protect_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit(-1);
	return (data);
}

t_philo	*protect_t_philo(void)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit(-1);
	return (philo);
}

t_philo	**protect_double_t_philo(t_data *data)
{
	data->philo = (t_philo **)malloc(sizeof(t_philo *)
			* (data->number_of_philosophers + 1));
	if (!data->philo)
		exit(-1);
	return (data->philo);
}
