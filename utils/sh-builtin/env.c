/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:32:26 by sabazyan          #+#    #+#             */
/*   Updated: 2022/11/07 19:04:03 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

int	check_env(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		if (ft_strcmp(matrix[i], "env") != 0)
			return (0);
	}
	return (1);
}

void	print_env(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	t_env	*temp;

	matrix = cmd->cmds->arg_pack;
	temp = tab->env;
	if (check_env(matrix))
	{
		while (temp)
		{
			if (temp->val && ft_strchr(temp->val, '"'))
				printf("%s=%s\n", temp->key, ft_strtrim(temp->val, "\""));
			else if (temp->val && !ft_strchr(temp->val, '"'))
				printf("%s=%s\n", temp->key, temp->val);
			temp = temp->next;
		}
		tab->status = 0;
	}
	else
	{
		printf("env: %s: No such file or directory\n",
			ft_strtrim(matrix[1], "\""));
		tab->status = 127;
	}
}
