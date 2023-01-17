/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tumolabs <tumolabs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:49 by sabazyan          #+#    #+#             */
/*   Updated: 2023/01/17 01:04:11 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 1;
	if (ft_strcmp(str, "-") == 0 || ft_strcmp(str, "+") == 0)
		return (0);
	if (str[0] < 43 || (str[0] > 43 && str[0] < 45)
		|| (str[0] > 45 && str[0] < 48) || str[0] > 57)
		return (0);
	while (str && str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

long double	ft_atoi_(char *str)
{
	int			i;
	int			syb;
	long double	counter;

	i = 0;
	syb = 1;
	counter = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		syb = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		counter = counter * 10 + str[i] - '0';
		i++;
	}
	return (syb * counter);
}

void	exit_cases(char **matrix, t_table *tab)
{
	if (matrix[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		tab->status = 1;
	}
	else if (!matrix[2])
	{
		printf("exit\n");
		tab->status = (unsigned int)ft_atoi(matrix[1]) % 256;
		exit(tab->status);
	}
}

void	ft_exit(t_cmds *cmd, t_table *tab)
{
	char		**matrix;
	long double	check;

	matrix = cmd->arg_pack;
	check = 9223372036854775807;
	if (!matrix[1])
	{
		printf("exit\n");
		exit(tab->status);
	}
	else if (!ft_isnumeric(matrix[1]) || ft_atoi_(matrix[1]) > check
		|| ft_atoi_(matrix[1]) < -1 * (check + 1))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", matrix[1]);
		tab->status = 255;
		exit(tab->status);
	}
	else
		exit_cases(matrix, tab);
}
