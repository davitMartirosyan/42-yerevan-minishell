/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:30:20 by sabazyan          #+#    #+#             */
/*   Updated: 2022/12/21 00:23:20 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_header.h"

void	change_path(t_table *tab, char *old_path)
{
	char	cwd[10000];
	char	*new_path;
	t_env	*temp;

	new_path = getcwd(cwd, 10000);
	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "PWD"))
			temp->val = new_path;
		temp = temp->next;
	}
	temp = tab->env;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "OLDPWD"))
			temp->val = old_path;
		temp = temp->next;
	}
}

void	change_path_to_home(t_table *tab, int res, char *old_path)
{
	t_env	*temp;
	int		check;
	char	cwd[10000];

	temp = tab->env;
	check = 1;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "HOME"))
		{
			res = chdir(temp->val);
			if (res == -1)
				printf("%scd: %s: No such file or directory\n",
					SHELLERR, temp->val);
			else if (res == 0)
			{
				if (!getcwd(cwd, 10000))
				{
					printf("yesim inch\n");
					return ;
				}
				change_path(tab, old_path);
			}
			check = 0;
		}
		temp = temp->next;
	}
	if (check)
		printf("%scd: HOME not set\n", SHELLERR);
}

void	print_cd(t_cmdline *cmd, t_table *tab)
{
	char	**matrix;
	t_env	*temp;
	char	cwd[10000];
	char	*old_path;
	int		res;

	(void)temp;
	res = 0;
	matrix = cmd->cmds->arg_pack;
	temp = tab->env;
	old_path = getcwd(cwd, 10000);
	if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0
		&& (!matrix[1] || ft_strcmp(matrix[1], "~") == 0))
	{
		if (!getcwd(cwd, 10000))
		{
			printf("yesim inch\n");
			return ;
		}
		change_path_to_home(tab, res, old_path);
	}
	else if (matrix[0] && ft_strcmp(matrix[0], "cd") == 0 && matrix[1])
	{
		res = chdir(matrix[1]);
		if (res == -1)
			printf("%scd: %s: No such file or directory\n", SHELLERR, matrix[1]);
		else if (res == 0)
		{
			if (!getcwd(cwd, 10000))
			{
				printf("yesim inch\n");
				return ;
			}
			change_path(tab, old_path);
		}
	}
}
