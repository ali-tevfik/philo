/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adoner <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 16:37:59 by adoner        #+#    #+#                 */
/*   Updated: 2022/05/04 14:54:37 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isalnum(int c)
{
	return (c >= 48 && c <= 57);
}


bool    is_digit(char *arg[])
{
	int	i;
	int	x;

	i = 1;
	while (arg[i])
	{
		x = 0;
		while(arg[i][x])
		{
			if(!ft_isalnum(arg[i][x]))
				return (false);
			x++;
		}
		i++;
	}
	return (true);
}