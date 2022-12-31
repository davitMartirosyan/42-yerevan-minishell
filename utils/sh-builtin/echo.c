/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:29:34 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/07 19:02:58 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	with_flag(char **matrix, int i)
{
	int	is_first;

	is_first = 1;
	i++;
	while (matrix[i] != NULL)
	{
		if (matrix[i] && check_flag(matrix[i]) == 0 && is_first == 1)
		{
			if (matrix[i + 1] && check_flag(matrix[i + 1]) == 1)
				is_first = 0;
			i++;
			continue ;
		}
		printf("%s", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
}

void	without_flag(char **matrix, t_table *tab, int i)
{
	while (matrix[i])
	{
		printf("%s", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (1);
	while (str[++i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

void	print_echo(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	matrix = cmd->cmds->arg_pack;
	i = 1;
	if (ft_strcmp(matrix[0], "echo") == 0 && !matrix[1])
		printf("\n");
	else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1]
		&& check_flag(matrix[1]) == 1)
		without_flag(matrix, tab, i);
	else if (ft_strcmp(matrix[0], "echo") == 0
		&& matrix[1] && check_flag(matrix[1]) == 0)
		with_flag(matrix, i);
	tab->status = 0;
}
