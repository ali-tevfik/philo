/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/12 16:38:19 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	t_data		*data;
	uint64_t	entry;
	uint64_t	result;

	data = ((t_data *)philo->data);
	entry = get_time_in_ms();
	data->dead = true;
	result = entry - philo->ate_time;
	if (result > data->time_to_die)
	{
		print_info(philo->data->first_time, philo->index, "die", RED);
		philo->data->dead = true;
		free_data(data);
		exit(0);
	}
}

bool	check_how_many_times_eat(t_data *data)
{
	if (data->is_number_of_times_each_philosopher_must_eat)
	{
		if (data->number_of_times_each_philosopher_must_eat - 1
			== data->philo[data->number_of_philosophers - 1]->ate_circlu)
			return (true);
	}
	return (false);
}

void	*die_thread(void *s_data)
{
	t_data		**data;
	int			i;
	uint64_t	now;
	uint64_t	start_time;

	start_time = get_time_in_ms();
	data = (t_data **)s_data;
	while (!(*data)->dead)
	{
		now = get_time_in_ms();
		i = 0;
		while ((*data)->philo[i])
		{
			if (now - (*data)->philo[i]->ate_time > (*data)->time_to_die
				&& !(*data)->philo[i]->is_eat)
				die((*data)->philo[i]);
			if (check_how_many_times_eat((*data)))
				return (data);
			i++;
		}
		usleep(500);
	}
	return (data);
}
