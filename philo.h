#ifndef PHILO_H
# define PHILO_H

//color code
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define CYAN  "\033[0;36m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"


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
typedef struct s_philo
{
    pthread_mutex_t fork;
    pthread_mutex_t print;
    int             index;
    struct s_data   *data;
    uint64_t        ate_time;
}               t_philo;

typedef struct s_data
{
    uint64_t		time_to_die;
    int		time_to_sleep;
    int		time_to_eat;
    int		number_of_philosophers;
	int		number_of_times_each_philosopher_must_eat;
    bool    is_number_of_times_each_philosopher_must_eat;
	bool	dead;
	t_philo **philo;
}              t_data;

int			ft_atoi(const char *str);
bool		is_digit(char *arg[]);
void		fill_data(char **argv, t_data *data);
void		to_sleep(t_philo *philo);
void		to_eat(t_philo *philo);
void 		die(t_philo *philo);
void		is_dead(uint64_t oude_tijd, t_philo *philo);
void 		*routine(void *s_data);
uint64_t	get_time_in_ms(void);
# endif