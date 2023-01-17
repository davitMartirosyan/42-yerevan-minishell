/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabazyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:41 by sabazyan          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:52 by sabazyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	print_pwd(t_cmds *cmd, t_table *tab)
{
	char	**matrix;
	char	cwd[256];

	matrix = cmd->arg_pack;
	if (matrix[0] && ft_strcmp(matrix[0], "pwd") == 0)
	{
		if (getcwd(cwd, 256))
			printf("%s\n", getcwd(cwd, 256));
		else
			no_pwd(tab);
	}
	tab->status = 0;
}

void	no_pwd(t_table *tab)
{
	t_env	*temp;

	temp = tab->env;
	if (tab->pwd_status == 0)
	{
		while (temp)
		{
			if (ft_strcmp(temp->key, "PWD") == 0)
				printf("%s\n", temp->val);
			temp = temp->next;
		}
	}
	else if (tab->pwd_status == 1)
		pwd_loop(tab);
}

void	pwd_loop(t_table *tab)
{
	t_env	*temp;
	char	*path;

	temp = tab->env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "OLDPWD") == 0)
		{
			path = ft_strjoin(ft_strdup(temp->val), "/..");
			printf("%s\n", path);
			free(path);
		}
		temp = temp->next;
	}
	tab->pwd_status = 0;
}
