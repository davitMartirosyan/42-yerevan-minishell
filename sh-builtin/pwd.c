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

<<<<<<< HEAD
void	print_pwd(t_cmdline *cmd, t_table *tab)
=======
void	print_pwd(t_cmdline *cmd, t_table *table)
>>>>>>> master
{
	(void)table;
	char	**matrix;
	char	cwd[256];

	matrix = cmd->cmds->arg_pack;
	if (matrix[0] && ft_strcmp(matrix[0], "pwd") == 0)
<<<<<<< HEAD
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
	if (tab->status == 0)
	{
		while (temp)
		{
			if (ft_strcmp(temp->key, "PWD") == 0)
				printf("%s\n", temp->val);
			temp = temp->next;
		}
	}
	else if (tab->status == 1)
	{
		while (temp)
		{
			if (ft_strcmp(temp->key, "OLDPWD") == 0)
				printf("%s\n", ft_strjoin(temp->val, "/.."));
			temp = temp->next;
		}
	}
}
=======
		printf("%s\n", getcwd(cwd, 256));
}
>>>>>>> master
