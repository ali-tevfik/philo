/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/24 16:14:24 by adoner        ########   odam.nl         */
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
	data->dead = TRUE;
	result = entry - philo->ate_time;
	if (result > data->time_to_die)
	{
		print_info(philo->data->first_time, philo, "died", RED);
		philo->data->dead = TRUE;
	}
}

int	check_how_many_times_eat(t_data *data)
{
	if (data->must_eat > 0)
	{
		if (data->must_eat
			== data->philo[data->number_of_philosophers - 1]->ate_circle)
			return (TRUE);
	}
	return (FALSE);
}

int	check_must_eat(uint64_t now, t_data *data, int i)
{
	if (now - data->philo[i]->ate_time > data->time_to_die
		&& !data->philo[i]->is_eat)
		return (TRUE);
	return (FALSE);
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
			if (check_must_eat(now, (*data), i))
			{
				die((*data)->philo[i]);
				return (data);
			}					
			else if (check_how_many_times_eat((*data)))
				return (data);
			i++;
		}
		usleep(100);
	}
	return (data);
}
