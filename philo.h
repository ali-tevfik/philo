#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
#include <pthread.h>
# include <sys/time.h>
# include <string.h>

// typedef struct  s_philo
// {
//     bool    l_fork;
//     bool    r_fork;
//     bool    eating;
//     bool    sleeping;
//     bool    die;
// }               t_philo;

typedef struct s_data
{
    int		time_to_die;
    int		time_to_sleep;
    int		time_to_eat;
    int		number_of_philosophers;
	int		number_of_times_each_philosopher_must_eat;
	bool	b_number_of_times_each_philosopher_must_eat;
    pthread_mutex_t fork;
    pthread_mutex_t print;
    bool is_die;
	// t_philo	*philo[];
}               t_data;

int	ft_atoi(const char *str);
bool    is_digit(char *arg[]);

# endif