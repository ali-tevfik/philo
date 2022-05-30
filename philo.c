/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 16:09:58 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/24 15:52:22 by adoner        ########   odam.nl         */
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
		return (FALSE);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (FALSE);
	if (!fill_data(argv, data))
		return (FALSE);
	if (!create_thread(data))
		return (FALSE);
	free_data(data);
	return (EXIT_SUCCESS);
}
