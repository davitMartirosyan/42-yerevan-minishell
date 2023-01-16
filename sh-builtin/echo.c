/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro		 <dmartiro		@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:12:08 by dmartiro		              #+#    #+#             */
/*   Updated: 2023/01/16 11:34:06 by dmartiro		             ###   ########.fr       */
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
		printf("%s\b", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
}

void	without_flag(char **matrix, int i)
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

void	print_echo(t_cmds *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	matrix = cmd->arg_pack;
	i = 1;
	if (ft_strcmp(matrix[0], "echo") == 0 && !matrix[1])
		printf("\n");
	else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1]
		&& check_flag(matrix[1]) == 1)
		without_flag(matrix, i);
	else if (ft_strcmp(matrix[0], "echo") == 0
		&& matrix[1] && check_flag(matrix[1]) == 0)
		with_flag(matrix, i);
	tab->status = 0;
}
