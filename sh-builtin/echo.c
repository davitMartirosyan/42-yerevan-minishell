/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:29:34 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/17 14:32:53 by dmartiro         ###   ########.fr       */
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
<<<<<<< HEAD
	while (matrix[i])
=======
	(void)tab;
	while (matrix[i] && is_token(matrix[i]) == 0)
>>>>>>> master
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

<<<<<<< HEAD
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

=======
>>>>>>> master
void	print_echo(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	int		i;

	matrix = cmd->cmds->arg_pack;
	i = 1;
<<<<<<< HEAD
	if (ft_strcmp(matrix[0], "echo") == 0 && !matrix[1])
		printf("\n");
	else if (ft_strcmp(matrix[0], "echo") == 0 && matrix[1]
		&& check_flag(matrix[1]) == 1)
		without_flag(matrix, tab, i);
	else if (ft_strcmp(matrix[0], "echo") == 0
		&& matrix[1] && check_flag(matrix[1]) == 0)
		with_flag(matrix, i);
	tab->status = 0;
=======
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
>>>>>>> master
}
