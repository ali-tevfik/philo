/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 10:51:48 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/10 11:33:57 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//atoi
static	int	checkspace(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == '\t' || *(s + i) == '\n' || *(s + i) == '\f'
			|| *(s + i) == '\r' || *(s + i) == '\v' || *(s + i) == ' ')
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	total;
	int	control;

	i = checkspace(str);
	control = 1;
	total = 0;
	if (str[0] == '0')
		return (0);
	if (*(str + i) == '-')
	{
		control = -1;
		i++;
	}
	else if (*(str + i) == '+')
		i++;
	while (*(str + i) != '\0')
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
			total = (*(str + i) - '0') + (total * 10);
		else
			break ;
		i++;
	}
	return (total * control);
}

//end atoi

uint64_t	get_time_in_ms(void)
{
	struct timeval	current_time;
	long long		miliseconds;

	gettimeofday(&current_time, NULL);
	miliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (miliseconds);
}
