/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 16:37:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/22 14:19:39 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Color Code
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	ate_time_mutex;
	pthread_t		thread;
	pthread_t		check_dead;
	uint64_t		ate_time;
	int				is_eat;
	int				index;
	int				ate_circle;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	died_data;
	pthread_mutex_t	print;
	pthread_mutex_t	turn;
	uint64_t		first_time;
	uint64_t		time_to_die;
	int				time_to_sleep;
	int				died_print;
	int				time_to_eat;
	int				number_of_philosophers;
	int				must_eat;
	int				dead;
	int				philo_eat_turn;
	t_philo			**philo;
}					t_data;

int			ft_atoi(const char *str);
int			is_dead(t_philo *philo);
int			fill_data(char **argv, t_data *data);
void		*routine(void *s_data);
uint64_t	get_time_in_ms(void);
void		*die_thread(void *s_data);
void		print_info(u_int64_t time, t_philo *philo,
				char *txt, char *COLORCODE);
int			check_argument(char **argv, int argc);
int			create_thread(t_data *data);
void		smart_sleep(uint64_t ms);
#endif