/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantana <lsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:10:19 by lsantana          #+#    #+#             */
/*   Updated: 2023/03/14 11:10:14 by lsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	void	msg_error_invald_argc(void)
{
	printf(CYAN" ____________________________________________________ \n"RESET);
	printf(CYAN"|                                                    |\n"RESET);
	printf(CYAN"|        Please enter the following arguments        |\n"RESET);
	printf(CYAN"|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |\n"RESET);
	printf(CYAN"|                                                    |\n"RESET);
	printf(CYAN"|             [1][Number of philosophers]            |\n"RESET);
	printf(CYAN"|             [2][Time to die]                       |\n"RESET);
	printf(CYAN"|             [3][Time to eat]                       |\n"RESET);
	printf(CYAN"|             [4][Time to sleep]                     |\n"RESET);
	printf(CYAN"|            *[5][Number of meals]                   |\n"RESET);
	printf(CYAN"|                                                    |\n"RESET);
	printf(CYAN"|                                  Att: * is Optional|\n"RESET);
	printf(CYAN"|____________________________________________________|\n"RESET);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_arguments(char *argv[])
{
	int				i;
	int				j;
	unsigned int	value;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (ft_strlen(argv[i]) > 11)
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] == '+' && j == 0)
				j++;
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		value = (unsigned int)ft_atoi(argv[i]);
		if ((value > 2147483647 || value == 0))
			return (1);
		i++;
	}
	return (0);
}

int	check_errors(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (msg_error_invald_argc(), 1);
	if (is_valid_arguments(argv))
		return (printf(CYAN"The arguments must be positive integers!\n"RESET));
	return (0);
}
