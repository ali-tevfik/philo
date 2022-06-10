/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 16:37:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/06/10 16:54:32 by tevfik        ########   odam.nl         */
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
# define TRUE 1
# define FALSE 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	eat;
	pthread_mutex_t	fork;
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
	uint64_t		first_time;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	uint64_t		time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				number_of_philosophers;
	int				must_eat;
	int				dead;
	int				philo_eat_turn;
	t_philo			**philo;
}					t_data;

int			ft_atoi(const char *str);
int			fill_data(char **argv, t_data *data);
void		is_dead(uint64_t oude_tijd, t_philo *philo);
void		*routine(void *s_data);
uint64_t	get_time_in_ms(void);
void		*die_thread(void *s_data);
void		print_info(u_int64_t time, t_philo *philo,
				char *txt, char *COLORCODE);
int			check_argument(char **argv, int argc);
int			create_thread(t_data *data);
void		free_data(t_data *data);
void		smart_sleep(uint64_t ms);
#endif