/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <adoner@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 11:34:00 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/24 16:14:24 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isalnum(int c)
{
	return (c >= 48 && c <= 57);
}

int	is_digit(char *arg[])
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
				return (FALSE);
			x++;
		}
		i++;
	}
	return (TRUE);
}

int	check_argument(char **argv, int argc)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("Error!\n");
		return (FALSE);
	}
	if (!is_digit(argv))
	{
		printf("Error:No Digit!\n");
		return (FALSE);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Error: Invalid argument!\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
