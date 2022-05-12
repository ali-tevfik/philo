/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 11:34:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/12 16:23:55 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isalnum(int c)
{
	return (c >= 48 && c <= 57);
}

bool	is_digit(char *arg[])
{
	int	i;
	int	x;

	i = 1;
	while (arg[i])
	{
		x = 0;
		while (arg[i][x])
		{
			if (!ft_isalnum(arg[i][x]))
				return (false);
			x++;
		}
		i++;
	}
	return (true);
}

bool	check_argument(char **argv, int argc)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("Error!\n");
		return (false);
	}
	if (!is_digit(argv))
	{
		printf("Error:No Digit!\n");
		return (false);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Invalid argument!\n");
			return (false);
		}
		i++;
	}
	return (true);
}
