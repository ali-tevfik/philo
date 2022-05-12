/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 16:37:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/12 16:37:47 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// color code
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_t		thread;
	uint64_t		ate_time;
	bool			is_eat;
	int				index;
	int				ate_circlu;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	uint64_t	first_time;
	uint64_t	time_to_die;
	pthread_t	check_dead;
	int			time_to_sleep;
	int			time_to_eat;
	int			number_of_philosophers;
	int			number_of_times_each_philosopher_must_eat;
	bool		is_number_of_times_each_philosopher_must_eat;
	bool		dead;
	t_philo		**philo;
}				t_data;

int			ft_atoi(const char *str);
void		fill_data(char **argv, t_data *data);
void		is_dead(uint64_t oude_tijd, t_philo *philo);
void		*routine(void *s_data);
uint64_t	get_time_in_ms(void);
void		*die_thread(void *s_data);
void		print_info(u_int64_t time, int index, char *txt, char *COLORCODE);
bool		check_argument(char **argv, int argc);
void		create_thread(t_data *data);
t_philo		*protect_t_philo(void);
t_philo		**protect_double_t_philo(t_data *data);
t_data		*protect_data(void);
void		free_data(t_data *data);
#endif