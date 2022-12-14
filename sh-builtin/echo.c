/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:29:34 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/14 12:19:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	is_keyword(char *str)
{
	char	**keywords;
	int		i;

	keywords = ft_split(RESERVED, ' ');
	i = -1;
	while (keywords[++i])
	{
		if (ft_strcmp(keywords[i], str) == 0)
			return (1);
	}
	return (0);
}

int	is_token(char *str)
{
	char	**tokens;
	int		i;

	tokens = ft_split(TOKENS, ' ');
	i = -1;
	while (tokens[++i])
	{
		if (ft_strcmp(tokens[i], str) == 0)
			return (1);
	}
	return (0);
}

void	with_flag(char **matrix, int i)
{
	i++;
	while (matrix[i] && is_token(matrix[i]) == 0)
	{
		printf("%s", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
}

void	without_flag(char **matrix, t_table *tab, int i)
{
	while (matrix[i] && is_token(matrix[i]) == 0)
	{
		if (ft_strcmp(matrix[i], "$?") == 0)
			printf("tab->status");
		else
			printf("%s", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	print_echo(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	matrix = cmd->cmds->arg_pack;
	i = 1;
	if (matrix[0] && is_keyword(matrix[0]) == 0)
		printf("-minishell: %s: command not found\n", matrix[0]);
	else if (matrix[0] && is_keyword(matrix[0]) == 1)
	{
		if (ft_strcmp(matrix[0], "echo") == 0 && !matrix[1])
			printf("\n");
		else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1]
			&& ft_strcmp(matrix[1], "-n") != 0)
			without_flag(matrix, tab, i);
		else if (ft_strcmp(matrix[0], "echo") == 0
			&& matrix[1] && ft_strcmp(matrix[1], "-n") == 0)
			with_flag(matrix, i);
	}
}
