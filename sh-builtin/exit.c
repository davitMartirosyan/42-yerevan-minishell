/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:49 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/22 21:20:44 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	ft_isnumeric(char **s)
{
	int	i;
	int	j;

	i = 1;
	while (s && s[i])
	{
		j = 1;
		if (ft_strcmp(s[i], "-") == 0 || ft_strcmp(s[i], "+") == 0)
			return (0);
		if (s[i][0] < 43 || (s[i][0] > 43 && s[i][0] < 45)
		|| (s[i][0] > 45 && s[i][0] < 48) || s[i][0] > 57)
			return (0);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_exit(char *cmd)
{
	int		status;
	char	**matrix;

	status = 0;
	matrix = ft_split(cmd, ' ');
	if (matrix[1] && ft_isnumeric(matrix) == 0)
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", matrix[1]);
		status = ft_atoi(matrix[1]);
		exit(status);
	}
	else if (matrix[1] && matrix[2])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
	}
	else if (matrix[1] && !matrix[2])
	{
		printf("exit\n");
		status = ft_atoi(matrix[1]);
		exit(status);
	}
}
