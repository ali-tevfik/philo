#include "philo.h"

uint64_t	get_time_in_ms(void)
{
	struct timeval	current_time;
	long long		miliseconds;

	gettimeofday(&current_time, NULL);
	miliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (miliseconds);
}

t_data *fill_data(char **argv)
{
    t_data *data;
    
    if (!is_digit(argv))
    {
        printf("no digit!\n");
        exit(1);
    }
    data = malloc(1024);
    data->is_die = false;
    if (!pthread_mutex_init(&data->fork, NULL) && pthread_mutex_init(&data->print, NULL))
    {
        printf("\n mutex init failed\n");
        exit(1);
    }
    data->time_to_die = ft_atoi(argv[4]);
    data->time_to_eat = ft_atoi(argv[2]);
    data->time_to_sleep = ft_atoi(argv[3]);
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->b_number_of_times_each_philosopher_must_eat = true;
    if (argv[5])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else 
        data->b_number_of_times_each_philosopher_must_eat = false;
    return (data);
}
void *to_sleep(t_data *data)
{
    pthread_mutex_lock(&data->fork);
    pthread_mutex_lock(&data->print);
    usleep(data->time_to_sleep * 1000);
    printf("to_sleep %d\n",data->time_to_sleep);
    pthread_mutex_unlock(&data->fork);
    pthread_mutex_unlock(&data->print);
    return (data);
}

void *to_eat(t_data *data)
{
    pthread_mutex_lock(&data->fork);
    pthread_mutex_lock(&data->print);
    usleep(data->time_to_eat * 1000);
    printf("to_eat %d\n",data->time_to_eat);
    pthread_mutex_unlock(&data->fork);
    pthread_mutex_unlock(&data->print);
    return (data);
}

void *die(t_data *data)
{
    pthread_mutex_lock(&data->fork);
    pthread_mutex_lock(&data->print);
    usleep(data->time_to_die * 1000);
    printf("die %d\n",data->time_to_die);
    pthread_mutex_unlock(&data->print);
    pthread_mutex_unlock(&data->fork);
    return (data);
}
void is_dead(t_data *data, uint64_t oude_tijd)
{
   uint64_t	entry;

	entry = get_time_in_ms();
    data->b_number_of_times_each_philosopher_must_eat = true;
    printf("time = %llu\n\n",entry - oude_tijd);
}
void *routine(void *s_data)
{
    t_data **data = (t_data **)s_data;
    uint64_t tijd;

    tijd = get_time_in_ms();
    printf("routine!\n");
    to_eat(*data);
    if ((((int)(get_time_in_ms() - tijd))  > (*data)->time_to_die))
        printf("geberdi!!\n\n");
    to_sleep(*data);
    die(*data);
    is_dead(*data, tijd);
    return (data);
}

int main(int argc, char *argv[])
{
    t_data *data;
    pthread_t start_routine[3];
    if (!(argc == 5 || argc == 6))
    {
        printf("Error!\n");
        exit(1);
    }
  
    data = fill_data(argv);
    printf("\n1\n");
    pthread_create(&start_routine[0], NULL, routine, &data);
    printf("\n2\n");
    pthread_create(&start_routine[1], NULL, routine, &data);
    printf("\n3\n");
    pthread_create(&start_routine[2], NULL, routine, &data);
    // if (pthread_mutex_init(&lock, NULL) != 0)
    // {
    //     printf("\n mutex init failed\n");
    //     return 1;
    // }
    pthread_join(start_routine[0], NULL);
    pthread_join(start_routine[1], NULL);
    pthread_join(start_routine[2], NULL);
}
