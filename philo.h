#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
typedef struct  s_philo
{
    bool    l_fork;
    bool    r_fork;
    bool    eating;
    bool    sleeping;
    bool    die;
}               t_philo;

typedef struct s_data
{
    int die;
    int sleep;
    int eat;
}               t_data;

int	ft_atoi(const char *str);


# endif