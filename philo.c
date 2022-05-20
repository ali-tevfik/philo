/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 16:09:58 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/19 14:07:30 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(uint64_t ms)
{
	uint64_t	entry;

	entry = get_time_in_ms();
	while ((get_time_in_ms() - entry) < ms)
		usleep(100);
}


void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->philo[i])
	{
		pthread_mutex_destroy(&data->philo[i]->fork);
		pthread_detach(data->philo[i]->thread);
		free(data->philo[i]);
		i++;
	}
	if (data->philo)
		free(data->philo);
	if (data->check_dead)
		pthread_detach(data->check_dead);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!check_argument(argv, argc))
		exit(-1);
	data = protect_data();
	fill_data(argv, data);
	create_thread(data);
	return (EXIT_SUCCESS);
}
