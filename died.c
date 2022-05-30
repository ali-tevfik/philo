/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   died.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 16:31:07 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/30 13:02:23 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*die(t_philo *philo)
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
	return (NULL);
}

//die check func
int	check_must_eat(uint64_t now, t_data *data, int i)
{
	if (now - data->philo[i]->ate_time > data->time_to_die
		&& !data->philo[i]->is_eat)
		return (TRUE);
	return (FALSE);
}

int	is_must_eat(t_data *data)
{
	if (data->must_eat > 0)
	{
		if (data->must_eat
			== data->philo[data->number_of_philosophers - 1]->ate_circle)
			return (TRUE);
	}
	return (FALSE);
}

int	check_all_philo_must_eat(t_data *data)
{
	int	i;

	i = 0;
	while (data->philo[i])
	{
		if (data->must_eat != data->philo[i]->ate_circle)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

//changed if->else{return}
void	*die_thread(void *s_data)
{
	t_data		**data;
	int			i;
	uint64_t	now;

	data = (t_data **)s_data;
	while (!(*data)->dead)
	{
		now = get_time_in_ms();
		i = 0;
		while ((*data)->philo[i])
		{
			if (check_must_eat(now, (*data), i))
			{
				if (is_must_eat(*data))
					continue ;
				else
					return (die((*data)->philo[i]));
			}					
			i++;
			if (check_all_philo_must_eat(*data))
				return (NULL);
		}
		usleep(100);
	}
	return (data);
}
