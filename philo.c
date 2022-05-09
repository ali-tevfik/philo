/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 16:09:58 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/09 17:14:26 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_in_ms(void)
{
	struct timeval	current_time;
	long long		miliseconds;

	gettimeofday(&current_time, NULL);
	miliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (miliseconds);
}



int main(int argc, char *argv[])
{
    t_data *data;
    int x;
    pthread_t start_routine[ft_atoi(argv[1])];
    pthread_t check_dead;
    int i;
    
    i = ft_atoi(argv[1]);
    x = 0;
    if (!(argc == 5 || argc == 6))
    {
        printf("Error!\n");
        exit(1);
    }
    data = (t_data *)malloc(sizeof(t_data));
    fill_data(argv, data);
    while (i > x)
    {
        pthread_create(&start_routine[x], NULL, routine, &data->philo[x]);
        x++;
    } 
    pthread_create(&check_dead, NULL, die_thread, &data);
    pthread_join(check_dead, NULL);
    int j = 0;  
    while(j < x)
    {
        pthread_join(start_routine[j], NULL);
        j++;
    }
}
