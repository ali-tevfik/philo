/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 16:09:58 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/21 17:54:49 by adoner        ########   odam.nl         */
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

	if (!data)
		return ;
	i = 0;
	pthread_mutex_destroy(&data->died_data);
	pthread_mutex_destroy(&data->turn);
	pthread_mutex_destroy(&data->print);
	while (data->number_of_philosophers > i)
	{
		pthread_mutex_destroy(&data->philo[i]->fork);
		pthread_mutex_destroy(&data->philo[i]->eat);
		pthread_mutex_destroy(&data->philo[i]->ate_time_mutex);
		free(data->philo[i]);
		i++;
	}
	free(data);
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
	return (TRUE);
}
